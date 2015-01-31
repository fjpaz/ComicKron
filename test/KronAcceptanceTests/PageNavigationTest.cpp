/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#include "../common/TestData.h"
#include "test_doubles/AcceptanceAppFactory.h"
#include "test_doubles/SignalSpy.h"

#include <KronApplication/App.h>
#include <KronApplication/viewmodels/ComicReaderVM.h>

#include <gtest/gtest.h>
#include <QCryptographicHash>
#include <QUrl>

#include <functional>
#include <memory>

namespace kron {

// As a comic reader
// I want to navigate through pages
// So that I can read any page of the comic
class PageNavigationTest : public ::testing::Test
{
protected:
    std::unique_ptr<AppFactory> appFactory_;
    std::unique_ptr<App> app_;
    ComicReaderVM* comicReaderVM_ = nullptr;

    virtual void SetUp()
    {
        appFactory_.reset(new AcceptanceAppFactory);
        app_.reset(appFactory_->createApp());
        comicReaderVM_ = static_cast<ComicReaderVM*>(&app_->contexProperty("model"));

        QUrl comicUrl = QUrl::fromLocalFile("TestComic.cbz");
        comicReaderVM_->openComic(comicUrl.toString());
    }

    virtual void TearDown()
    {
        app_.release();
        appFactory_.release();
    }
};

TEST_F(PageNavigationTest,
Given_any_page_being_shown_\
When_user_requests_to_go_to_first_page_\
Then_show_first_page)
{
    SignalSpy spy(comicReaderVM_, SIGNAL(pageUpdated(QByteArray)));

    comicReaderVM_->goToFirstPage();

    ASSERT_TRUE(spy.signalReceived());
    QByteArray currentPage = spy.firstParameter().toByteArray();
    QByteArray currentPageMd5 = QCryptographicHash::hash(currentPage, QCryptographicHash::Md5);
    EXPECT_EQ(testdata::page01Md5, currentPageMd5);
}

TEST_F(PageNavigationTest,
Given_last_page_is_not_being_shown_currently_\
When_user_requests_to_go_forward_\
Then_show_next_page)
{
    SignalSpy spyFirst(comicReaderVM_, SIGNAL(pageUpdated(QByteArray)));
    comicReaderVM_->goToFirstPage();
    ASSERT_TRUE(spyFirst.signalReceived());
    SignalSpy spyForward(comicReaderVM_, SIGNAL(pageUpdated(QByteArray)));

    comicReaderVM_->goForward();

    ASSERT_TRUE(spyForward.signalReceived());
    QByteArray currentPage = spyForward.firstParameter().toByteArray();
    QByteArray currentPageMd5 = QCryptographicHash::hash(currentPage, QCryptographicHash::Md5);
    EXPECT_EQ(testdata::page02Md5, currentPageMd5);
}

/*
TEST_F(PageNavigationTest,
Given_last_page_is_being_shown_currently_\
When_user_requests_to_go_forward_\
Then_keep_showing_current_page)
{
    SignalSpy spy(comicReaderVM_, SIGNAL(pageUpdated(QByteArray)));

    comicReaderVM_->goForward();

    EXPECT_TRUE(spy.signalReceived());
}
*/

}

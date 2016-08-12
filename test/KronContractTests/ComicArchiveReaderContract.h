/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef COMICARCHIVEREADERCONTRACT_H
#define COMICARCHIVEREADERCONTRACT_H

#include "../common/TestData.h"

#include <KronCore/services/ComicArchiveReader.h>

#include <gtest/gtest.h>
#include <QCryptographicHash>
#include <QFile>

#include <memory>

using namespace kron;

typedef ComicArchiveReader* CreateComicArchiveReaderFunc();

class ComicArchiveReaderContract : public ::testing::TestWithParam<CreateComicArchiveReaderFunc*>
{
protected:
    std::unique_ptr<ComicArchiveReader> reader_;

    virtual void SetUp()
    {
        reader_.reset((*GetParam())());
    }

    // Override this method if any dependency must be released
    virtual void TearDown()
    {
        reader_.release();
    }
};

//TEST_P(ComicArchiveReaderContract, shouldFailToReadAnyImageWhenComicIsNotOpen)
//{
//    QByteArray firstImage;

//    EXPECT_THROW(firstImage = reader_->readFirstImage(), std::out_of_range/*"Comic must be opened before any read operation"*/);
//}

TEST_P(ComicArchiveReaderContract, shouldSetCurrentArchiveWhenOpen)
{
    QString archive = "TestComic.cbz";

    reader_->open(archive);

    EXPECT_EQ(archive.toStdString(), reader_->currentArchive().toStdString());
}

TEST_P(ComicArchiveReaderContract, shouldReturnFirstImageBytesWhenReadingFirstImage)
{
    QString archive = "TestComic.cbz";
    reader_->open(archive);

    QByteArray image = reader_->readFirstImage();

    QByteArray imageMd5 = QCryptographicHash::hash(image, QCryptographicHash::Md5);
    EXPECT_EQ(testdata::page01Md5, imageMd5);
}

TEST_P(ComicArchiveReaderContract, shouldReturnNextImageBytesWhenReadingNextImageAndCurrentIsNotLast)
{
    QString archive = "TestComic.cbz";
    reader_->open(archive);
    reader_->readFirstImage();

    QByteArray image = reader_->readNextImage();

    QByteArray imageMd5 = QCryptographicHash::hash(image, QCryptographicHash::Md5);
    EXPECT_EQ(testdata::page02Md5, imageMd5);
}

TEST_P(ComicArchiveReaderContract, shouldReturnPreviousImageBytesWhenReadingPreviousImageAndCurrentIsNotFirst)
{
    QString archive = "TestComic.cbz";
    reader_->open(archive);
    reader_->readFirstImage();
    reader_->readNextImage();

    QByteArray image = reader_->readPreviousImage();

    QByteArray imageMd5 = QCryptographicHash::hash(image, QCryptographicHash::Md5);
    EXPECT_EQ(testdata::page01Md5, imageMd5);
}

TEST_P(ComicArchiveReaderContract, shouldBeAbleToReadPdfArchives)
{
    QString archive = "TestComic.pdf";
    reader_->open(archive);

    QByteArray image01 = reader_->readFirstImage();

    QByteArray image01Md5 = QCryptographicHash::hash(image01, QCryptographicHash::Md5);
    ASSERT_EQ(testdata::pdfPage01Md5, image01Md5);

    QByteArray image02 = reader_->readNextImage();

    QByteArray image02Md5 = QCryptographicHash::hash(image02, QCryptographicHash::Md5);
    ASSERT_EQ(testdata::pdfPage02Md5, image02Md5);

    QByteArray image03 = reader_->readPreviousImage();

    QByteArray image03Md5 = QCryptographicHash::hash(image03, QCryptographicHash::Md5);
    EXPECT_EQ(testdata::pdfPage01Md5, image03Md5);
}

#endif // COMICARCHIVEREADERCONTRACT_H

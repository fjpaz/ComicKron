/*********************************************************************
 * Copyright (C) 2014 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#include "ComicReaderVM.h"

#include "../services/ComicArchiveReader.h"
#include "../services/ImageContainer.h"

#include <QUrl>

#include <stdexcept>

namespace kron {

ComicReaderVM::ComicReaderVM(ComicArchiveReader& archiveReader,
                             ImageContainer& imageContainer)
    : QObject(),
      archiveReader_(archiveReader),
      imageContainer_(imageContainer)
{
}

ComicReaderVM::~ComicReaderVM()
{
}

void ComicReaderVM::goForward()
{
    // TODO: Route and validate action with Domain
    QByteArray page = archiveReader_.readNextImage();
    updateCurrentPage(page);
}

void ComicReaderVM::goBackward()
{
    // TODO: Route and validate action with Domain
    QByteArray page = archiveReader_.readPreviousImage();
    updateCurrentPage(page);
}

void ComicReaderVM::goToFirstPage()
{
    // TODO: Route and validate action with Domain
    QByteArray page = archiveReader_.readFirstImage();
    updateCurrentPage(page);
}

void ComicReaderVM::openComic(QString comicPath)
{
    QUrl url(comicPath);

    if (!url.isValid())
        throw std::runtime_error("Invalid URL:" + url.toString().toStdString());

    if (!url.isLocalFile())
        throw std::runtime_error("File " + url.toString().toStdString() + " is not local");

    QString localComicPath = url.toLocalFile();

    archiveReader_.open(localComicPath);

    // TODO: Save archive info in domain

    goToFirstPage();
}

void ComicReaderVM::updateCurrentPage(QByteArray page)
{
    currentPage_ = page;
    imageContainer_.setImage("current", currentPage_);

    emit pageUpdated(currentPage_);
}

}

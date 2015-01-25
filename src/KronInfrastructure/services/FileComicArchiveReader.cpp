/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#include "FileComicArchiveReader.h"

#include "CompressedComicArchiveReader.h"
#include "PdfComicArchiveReader.h"

#include <KronApplication/exceptions/ArchiveNotFoundException.h>

#include <QFileInfo>

namespace kron {

FileComicArchiveReader::FileComicArchiveReader()
    : reader_()
{
}

FileComicArchiveReader::~FileComicArchiveReader()
{
}

void FileComicArchiveReader::open(QString comicArchive)
{
    if (!QFileInfo::exists(comicArchive))
    {
        throw ArchiveNotFoundException("Archive " + comicArchive.toStdString() + " not found");
    }

    if (QFileInfo(comicArchive).suffix() == "pdf")
    {
        reader_.reset(new PdfComicArchiveReader);

        reader_->open(comicArchive);
    }
    else
    {
        reader_.reset(new CompressedComicArchiveReader);

        reader_->open(comicArchive);
    }
}

QByteArray FileComicArchiveReader::readFirstImage()
{
    return reader_->readFirstImage();
}

QByteArray FileComicArchiveReader::readNextImage()
{
    return reader_->readNextImage();
}

QByteArray FileComicArchiveReader::readPreviousImage()
{
    return reader_->readPreviousImage();
}

QString FileComicArchiveReader::currentArchive() const
{
    return reader_->currentArchive();
}

}

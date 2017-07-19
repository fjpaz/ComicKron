/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#include "CompressedComicArchiveReader.h"

#include <KronCore/exceptions/ArchiveNotFoundException.h>
#include <KronCore/exceptions/ArchiveReadErrorException.h>

#include <QFile>
#include <QFileInfo>
#include <QMap>
#include <QString>

#include <QDebug>

namespace kron {

CompressedComicArchiveReader::CompressedComicArchiveReader()
    : file_(new QFile),
      mappedFile_(nullptr),
      buffer_(new char[10*1024*1024]),
      imageIndex_(0),
      stream_(nullptr),
      archive_(nullptr),
      indexToOffset_()
{
}

CompressedComicArchiveReader::~CompressedComicArchiveReader()
{
    if (archive_)
    {
        ar_close_archive(archive_);
    }

    if (stream_)
    {
        ar_close(stream_);
    }

    delete[] buffer_;
}

void CompressedComicArchiveReader::open(QString comicArchive)
{
    // Open file
    file_->setFileName(comicArchive);

    bool isOpen = file_->open(QIODevice::ReadOnly);

    if (!isOpen)
        throw ArchiveNotFoundException(
                "Archive " + comicArchive.toStdString() + " not found");

    // Free old archive resources
    if (archive_)
        ar_close_archive(archive_);

    if (stream_)
        ar_close(stream_);

    // Get new archive resources
    mappedFile_ = file_->map(0, file_->size());
    stream_ = ar_open_memory(static_cast<void*>(mappedFile_), static_cast<size_t>(file_->size()));

    QFileInfo fileInfo(*file_);
    QString suffix = fileInfo.suffix();

    if (0 == suffix.compare("cbr"))
        archive_ = ar_open_rar_archive(stream_);
    else if (0 == suffix.compare("cbz"))
        archive_ = ar_open_zip_archive(stream_, false);
    else if (0 == suffix.compare("cbt"))
        archive_ = ar_open_tar_archive(stream_);
    else if (0 == suffix.compare("cb7"))
        archive_ = ar_open_7z_archive(stream_);

    // Reset image index
    imageIndex_ = 0;

    // Generate ordered file entry index
    QMap<QString, off64_t> stringToOffset;
    int fileIndex = 0;

    while (ar_parse_entry(archive_))
    {
        qDebug() << "File index:" << fileIndex << "name:" << ar_entry_get_name(archive_);
        off64_t offset = ar_entry_get_offset(archive_);
        QString fileName = ar_entry_get_name(archive_);
        stringToOffset.insert(fileName, offset);
        ++fileIndex;
    }

    // Generate image index to archive offset
    for (auto i = stringToOffset.cbegin(); i != stringToOffset.cend(); ++i)
    {
        indexToOffset_.push_back(i.value());
    }
}

QByteArray CompressedComicArchiveReader::readFirstImage()
{
    return readImage(0);
}

QByteArray CompressedComicArchiveReader::readNextImage()
{
    return readImage(imageIndex_ + 1);
}

QByteArray CompressedComicArchiveReader::readPreviousImage()
{
    return readImage(imageIndex_ - 1);
}

QString CompressedComicArchiveReader::currentArchive() const
{
    return file_->fileName();
}

QByteArray CompressedComicArchiveReader::readImage(int index)
{
    int currentIndex;
    bool backwardAndNotOnFirst = (imageIndex_ > index) && (imageIndex_ > 0);
    bool forwardAndNotOnLast = (imageIndex_ < index) &&
            (imageIndex_ < indexToOffset_.size() - 1);

    if (backwardAndNotOnFirst || forwardAndNotOnLast)
    {
        currentIndex = index;
        imageIndex_ = index;
    }
    else
    {
        currentIndex = imageIndex_;
        qDebug() << "Already on" << QString((imageIndex_ == 0) ?
                    "first" : "last").toLatin1().constData() << "image";
    }

    if (!ar_parse_entry_at(archive_, indexToOffset_.at(currentIndex)))
    {
        throw ArchiveReadErrorException(
                "Could not read header of entry " +
                    QString::number(currentIndex).toStdString() +
                    " of archive " + file_->fileName().toStdString());
    }

    size_t entrySize = ar_entry_get_size(archive_);

    if (!ar_entry_uncompress(archive_, buffer_, entrySize))
    {
        throw ArchiveReadErrorException(
                "Could not uncompress entry " +
                    QString::number(currentIndex).toStdString() +
                    " of archive " + file_->fileName().toStdString());
    }

    QByteArray image;

    if (entrySize > 0)
        image = QByteArray::fromRawData(buffer_ , static_cast<int>(entrySize));

    return image;

}

}

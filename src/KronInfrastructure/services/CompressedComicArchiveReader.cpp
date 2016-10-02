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

#include <archive.h>
#include <archive_entry.h>
#include <QFile>

#include <QDebug>
#include <QMap>

namespace kron {

CompressedComicArchiveReader::CompressedComicArchiveReader()
    : file_(new QFile),
      buffer_(new char[10*1024*1024]),
      fileIndex_(0),
      a_(),
      entry_(),
      imageToIndex_()
{
}

CompressedComicArchiveReader::~CompressedComicArchiveReader()
{
    delete[] buffer_;
}

void CompressedComicArchiveReader::open(QString comicArchive)
{
    file_->setFileName(comicArchive);

    bool isOpen = file_->open(QIODevice::ReadOnly);

    if (!isOpen)
        throw ArchiveNotFoundException("Archive " + comicArchive.toStdString() + " not found");

    uchar* mappedFile = file_->map(0, file_->size());

    int ret = 0;

    if (0 != fileIndex_)
    {
        // Close and open the file to read from beggining (libarchive cannot read backwards)
        ret = archive_read_close(a_);

        if (ret != ARCHIVE_OK)
            throw ArchiveReadErrorException("Could not close archive " + file_->fileName().toStdString());

        ret = archive_read_free(a_);

        if (ret != ARCHIVE_OK)
            throw ArchiveReadErrorException("Could not free memory for archive " + file_->fileName().toStdString());

        fileIndex_ = 0;
    }

    a_ = archive_read_new();
    archive_read_support_filter_all(a_);
    archive_read_support_format_all(a_);

    ret = archive_read_open_memory(a_, mappedFile, file_->size());

    if (ret != ARCHIVE_OK)
        throw ArchiveReadErrorException("Could not open archive " + comicArchive.toStdString());

    // Generate ordered file entry index
    QMap<QString, quint32> stringToIndex;
    quint32 i = 0;
    bool hasMoreEntries = true;

    while (hasMoreEntries)
    {
        int result = archive_read_next_header(a_, &entry_);

        if (ARCHIVE_OK == result)
        {
            QString fileName = archive_entry_pathname(entry_);

            // Only insert entries of file type. Do not insert directories
            if (AE_IFREG == archive_entry_filetype(entry_))
                stringToIndex.insert(fileName, i);
        }
        else if (ARCHIVE_EOF)
        {
            hasMoreEntries = false;
        }
        else
        {
            qDebug() << "Error on archive_read_next_header";
            return;
        }

        ++i;
    }

    for (auto i = stringToIndex.cbegin(); i != stringToIndex.cend(); ++i)
    {
        imageToIndex_.push_back(i.value());
    }

    ret = archive_read_close(a_);

    if (ret != ARCHIVE_OK)
        throw ArchiveReadErrorException("Could not close archive " + file_->fileName().toStdString());

    ret = archive_read_free(a_);

    if (ret != ARCHIVE_OK)
        throw ArchiveReadErrorException("Could not free memory for archive " + file_->fileName().toStdString());

    fileIndex_ = 0;

    a_ = archive_read_new();
    archive_read_support_filter_all(a_);
    archive_read_support_format_all(a_);

    ret = archive_read_open_memory(a_, mappedFile, file_->size());

    if (ret != ARCHIVE_OK)
        throw ArchiveReadErrorException("Could not open archive " + file_->fileName().toStdString());
}

QByteArray CompressedComicArchiveReader::readFirstImage()
{
    fileIndex_ = 0;
    __LA_SSIZE_T bytesRead = 0;

    // Close and open the file to read from beggining (libarchive cannot read backwards)
    int r = archive_read_close(a_);

    if (r != ARCHIVE_OK)
        throw ArchiveReadErrorException("Could not close archive " + file_->fileName().toStdString());

    r = archive_read_free(a_);

    if (r != ARCHIVE_OK)
        throw ArchiveReadErrorException("Could not free memory for archive " + file_->fileName().toStdString());

    a_ = archive_read_new();
    archive_read_support_filter_all(a_);
    archive_read_support_format_all(a_);

    uchar* mappedFile = file_->map(0, file_->size());

    r = archive_read_open_memory(a_, mappedFile, file_->size());

    if (r != ARCHIVE_OK)
        throw ArchiveReadErrorException("Could not open archive " + file_->fileName().toStdString());

    quint64 entrySize = 0;

    quint32 firstImageIndex = imageToIndex_.at(0);

    for (quint32 i = 0; i <= firstImageIndex; ++i)
    {
        if (archive_read_next_header(a_, &entry_) != ARCHIVE_OK)
            throw ArchiveReadErrorException("Could not read from archive " + file_->fileName().toStdString());

        entrySize = archive_entry_size(entry_);
    }

    qDebug() << archive_entry_pathname(entry_);

    qDebug() << "Filter Count: " << archive_filter_count(a_) << ", Name: " << QString(archive_format_name(a_)) << ", Code: " << archive_format(a_) <<
                ", Header Pos: " << archive_read_header_position(a_);

    bytesRead = archive_read_data(a_, buffer_, entrySize);
    qDebug() << "Bytes read: " << bytesRead;

    QByteArray image(buffer_, bytesRead);

    return image;
}

QByteArray CompressedComicArchiveReader::readNextImage()
{
    if (fileIndex_ < static_cast<quint32>(imageToIndex_.size() - 1))
        ++fileIndex_;
    else
        qDebug() << "Already on last image";

    __LA_SSIZE_T bytesRead = 0;
    quint64 entrySize = 0;

    a_ = archive_read_new();
    archive_read_support_filter_all(a_);
    archive_read_support_format_all(a_);

    uchar* mappedFile = file_->map(0, file_->size());

    int r = archive_read_open_memory(a_, mappedFile, file_->size());

    if (r != ARCHIVE_OK)
        throw ArchiveReadErrorException("Could not open archive " + file_->fileName().toStdString());

    quint32 imageIndex = imageToIndex_.at(fileIndex_);

    for (quint32 i = 0; i <= imageIndex; ++i)
    {
        if (archive_read_next_header(a_, &entry_) != ARCHIVE_OK)
            throw ArchiveReadErrorException("Could not read from archive " + file_->fileName().toStdString());

        entrySize = archive_entry_size(entry_);
    }

    qDebug() << archive_entry_pathname(entry_);

    qDebug() << "Filter Count: " << archive_filter_count(a_) << ", Name: " << QString(archive_format_name(a_)) << ", Code: " << archive_format(a_) <<
                ", Header Pos: " << archive_read_header_position(a_);

    bytesRead = archive_read_data(a_, buffer_, entrySize);
    qDebug() << "Bytes read: " << bytesRead;

    QByteArray image(buffer_, bytesRead);

    return image;
}

QByteArray CompressedComicArchiveReader::readPreviousImage()
{
    if (fileIndex_ != 0)
        --fileIndex_;
    else
        qDebug() << "Already on first image";

    __LA_SSIZE_T bytesRead = 0;
    quint64 entrySize = 0;

    a_ = archive_read_new();
    archive_read_support_filter_all(a_);
    archive_read_support_format_all(a_);

    uchar* mappedFile = file_->map(0, file_->size());

    int r = archive_read_open_memory(a_, mappedFile, file_->size());

    if (r != ARCHIVE_OK)
        throw ArchiveReadErrorException("Could not open archive " + file_->fileName().toStdString());

    quint32 imageIndex = imageToIndex_.at(fileIndex_);

    for (quint32 i = 0; i <= imageIndex; ++i)
    {
        if (archive_read_next_header(a_, &entry_) != ARCHIVE_OK)
            throw ArchiveReadErrorException("Could not read from archive " + file_->fileName().toStdString());

        entrySize = archive_entry_size(entry_);
    }

    qDebug() << archive_entry_pathname(entry_);

    qDebug() << "Filter Count: " << archive_filter_count(a_) << ", Name: " << QString(archive_format_name(a_)) << ", Code: " << archive_format(a_) <<
                ", Header Pos: " << archive_read_header_position(a_);

    bytesRead = archive_read_data(a_, buffer_, entrySize);
    qDebug() << "Bytes read: " << bytesRead;

    QByteArray image(buffer_, bytesRead);

    return image;
}

QString CompressedComicArchiveReader::currentArchive() const
{
    return file_->fileName();
}

}

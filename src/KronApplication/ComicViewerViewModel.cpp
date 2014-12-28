/*********************************************************************
 * Copyright (C) 2014 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#include "ComicViewerViewModel.h"

#include "ComicImageProvider.h"

#include <podofo/base/PdfDictionary.h>
#include <podofo/base/PdfMemStream.h>
#include <podofo/base/PdfName.h>
#include <podofo/base/PdfObject.h>
#include <podofo/doc/PdfMemDocument.h>
#include <podofo/doc/PdfPage.h>

#include <QFile>
#include <QFileInfo>
#include <QPixmap>
#include <QStandardPaths>
#include <QUrl>

#include <QDebug>

ComicViewerViewModel::ComicViewerViewModel(ComicImageProvider& provider, QObject* parent) :
    QObject(parent),
    provider_(provider),
    file_(new QFile),
    pixmap_(new QPixmap()),
    fileIndex_(0),
    buffer_(new char[10*1024*1024]),
    isPdfFile_(false)
{
    provider_.setPixmap(*pixmap_);

    qDebug() << "Download dir: " << QStandardPaths::displayName(QStandardPaths::DownloadLocation);
}

ComicViewerViewModel::~ComicViewerViewModel()
{
    if (0 != fileIndex_ && !isPdfFile_)
    {
        int r = archive_read_close(a_);

        if (r != ARCHIVE_OK)
        {
            exit(1);
        }

        r = archive_read_free(a_);

        if (r != ARCHIVE_OK)
        {
            exit(1);
        }
    }

    delete buffer_;
}

void ComicViewerViewModel::nextPage()
{
    qDebug() << "ComicViewerViewModel::nextPage()";

    __LA_SSIZE_T bytesRead = 0;

    if (isPdfFile_)
    {
        if (fileIndex_ < static_cast<quint32>(pdfImages_.size()))
        {
            PoDoFo::PdfObject *pObject = pdfImages_[fileIndex_];
            PoDoFo::PdfMemStream* pStream = dynamic_cast<PoDoFo::PdfMemStream*>(pObject->GetStream());
            buffer_ = const_cast<char*>(pStream->Get());
            bytesRead = pStream->GetLength();
            fileIndex_++;
        }
        else
        {
            return;
        }
    }
    else
    {
        bool is_file = false;

        while (!is_file)
        {
            int r = archive_read_next_header(a_, &entry_);

            qDebug() << "Filter Count: " << archive_filter_count(a_) << ", Name: " << QString(archive_format_name(a_)) << ", Code: " << archive_format(a_) <<
                        ", Header Pos: " << archive_read_header_position(a_);

            if (r == ARCHIVE_EOF)
            {
                // End Of File. No more entries. Do nothing
                qDebug() << "No more entries";
                return;
            }
            else if (r == ARCHIVE_WARN)
            {
                qDebug() << "Warning " << r << " on archive_read_next_header. " << QString(archive_error_string(a_)) << ". Error number: " << archive_errno(a_);
            }
            else if (r != ARCHIVE_OK)
            {
                qDebug() << "Error " << r << " on archive_read_next_header." << QString(archive_error_string(a_)) << ". Error number: " << archive_errno(a_);
                return;
            }

            if (AE_IFREG == archive_entry_filetype(entry_))
            {
                is_file = true;
            }

            fileIndex_++;
        }

        size_t entrySize = archive_entry_size(entry_);
        qDebug() << "Entry: " << archive_entry_pathname(entry_) << ", Size: " << entrySize;
        bytesRead = archive_read_data(a_, buffer_, entrySize);
    }

    bool loadSuccess = pixmap_->loadFromData(reinterpret_cast<uchar*>(buffer_), bytesRead);

    if (!loadSuccess)
    {
        qDebug() << "Error on _pixmap->loadFromData";
    }

    quint16 crc16 = qChecksum(buffer_, bytesRead);
    qDebug() << "Bytes read: " << bytesRead << ", CRC-16:" << crc16;
    qDebug() << "Pixmap width:" << pixmap_->width() << ", height:" << pixmap_->height();

    provider_.setPixmap(*pixmap_);
    emit comicImageChanged();
}

void ComicViewerViewModel::previuosPage()
{
    qDebug() << "ComicViewerViewModel::previuosPage()";

    if (fileIndex_ == 1)
    {
        qDebug() << "First file in archive";
        return;
    }

    __LA_SSIZE_T bytesRead = 0;

    if (isPdfFile_)
    {
        if (fileIndex_ > 1)
        {
            fileIndex_--;

            PoDoFo::PdfObject *pObject = pdfImages_[fileIndex_ - 1];
            PoDoFo::PdfMemStream* pStream = dynamic_cast<PoDoFo::PdfMemStream*>(pObject->GetStream());
            buffer_ = const_cast<char*>(pStream->Get());
            bytesRead = pStream->GetLength();
        }
        else
        {
            return;
        }
    }
    else
    {
        fileIndex_--;

        // Close and open the file to read from beggining (libarchive cannot read backwards)
        int r = archive_read_close(a_);

        if (r != ARCHIVE_OK)
        {
            exit(1);
        }

        r = archive_read_free(a_);

        if (r != ARCHIVE_OK)
        {
            exit(1);
        }

        a_ = archive_read_new();
        archive_read_support_filter_all(a_);
        archive_read_support_format_all(a_);

        uchar *mapped_file = file_->map(0, file_->size());

        r = archive_read_open_memory(a_, mapped_file, file_->size());

        if (r != ARCHIVE_OK)
        {
            exit(1);
        }

        for (quint32 i = 0; i < fileIndex_; ++i)
        {
            if (archive_read_next_header(a_, &entry_) != ARCHIVE_OK)
            {
                qDebug() << "Error on archive_read_next_header";
                return;
            }

            qDebug() << "Filter Count: " << archive_filter_count(a_) << ", Name: " << QString(archive_format_name(a_)) << ", Code: " << archive_format(a_) <<
                        ", Header Pos: " << archive_read_header_position(a_);
        }

        qDebug() << archive_entry_pathname(entry_);
        quint64 entry_size = archive_entry_size(entry_);
        bytesRead = archive_read_data(a_, buffer_, entry_size);
    }

    quint16 crc16 = qChecksum(buffer_, bytesRead);
    qDebug() << "Bytes read: " << bytesRead << ", CRC-16:" << crc16;

    bool load_sucess = pixmap_->loadFromData(reinterpret_cast<uchar*>(buffer_), bytesRead);
    if (!load_sucess)
    {
        qDebug() << "Error on _pixmap->loadFromData";
    }
    qDebug() << "Pixmap width:" << pixmap_->width() << ", height:" << pixmap_->height();

    // TODO: The ViewModel must not use QPixmap because it depends on QtQui. It could use a QByteArray
    provider_.setPixmap(*pixmap_);
    emit comicImageChanged();
}

void ComicViewerViewModel::loadFile(const QString& file)
{
    QUrl url(file);
    file_->setFileName(url.toLocalFile());

    qDebug() << "Load File:" << file_->fileName();

    bool is_open =file_->open(QIODevice::ReadOnly);

    if (!is_open)
    {
        qFatal("Could not open the file");
    }

    uchar* mappedFile = file_->map(0, file_->size());

    if (QFileInfo(file_->fileName()).suffix() == "pdf")
    {
        qDebug() << "Loading PDF file";

        isPdfFile_ = true;

        pdfDoc_.reset(new PoDoFo::PdfMemDocument);

        pdfDoc_->Load(reinterpret_cast<const char*>(mappedFile), file_->size());

        int numPages = pdfDoc_->GetPageCount();

        for( int i = 0; i < numPages; ++i )
        {
            PoDoFo::PdfPage* pdfPage = pdfDoc_->GetPage( i );
            qDebug() << "Page" << pdfPage->GetPageNumber();
            PoDoFo::PdfObject* resources = pdfPage->GetResources();
            PoDoFo::PdfDictionary& dictionary = resources->GetDictionary();

            PoDoFo::TKeyMap& keymap = dictionary.GetKeys();

            for (PoDoFo::TCIKeyMap it = keymap.begin(); it != keymap.end(); ++it)
            {
                PoDoFo::PdfName name = it->first;

                if (name.GetName() == "XObject")
                {
                    // The resource may be an XObject reference
                    PoDoFo::PdfObject* xobject = it->second;

                    if (xobject->IsDictionary())
                    {
                        PoDoFo::TKeyMap keys = xobject->GetDictionary().GetKeys();

                        for (PoDoFo::TCIKeyMap it = keys.begin(); it != keys.end(); ++it)
                        {
                            PoDoFo::PdfObject* mapObj = it->second;

                            if (mapObj->IsReference())
                            {
                                // Get object by reference and add to tracked images if it is an image
                                PoDoFo::PdfObject* imgObject = pdfDoc_->GetObjects().GetObject(mapObj->GetReference());
                                PoDoFo::PdfObject* pObjType = imgObject->GetDictionary().GetKey( PoDoFo::PdfName::KeyType );
                                PoDoFo::PdfObject* pObjSubType = imgObject->GetDictionary().GetKey( PoDoFo::PdfName::KeySubtype );

                                if( (pObjType && pObjType->IsName() && ( pObjType->GetName().GetName() == "XObject" )) ||
                                    (pObjSubType && pObjSubType->IsName() && ( pObjSubType->GetName().GetName() == "Image")))
                                {
                                    pdfImages_.push_back(imgObject);
                                    pdfDoc_->FreeObjectMemory(imgObject);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    else
    {
        isPdfFile_ = false;
    }

    int r = 0;

    if (0 != fileIndex_ && !isPdfFile_)
    {
        // Close and open the file to read from beggining (libarchive cannot read backwards)
        r = archive_read_close(a_);

        if (r != ARCHIVE_OK)
        {
            exit(1);
        }

        r = archive_read_free(a_);

        if (r != ARCHIVE_OK)
        {
            exit(1);
        }

        fileIndex_ = 0;
    }

    if (!isPdfFile_)
    {
        // TODO: Read images alphabetically ordered
        a_ = archive_read_new();
        archive_read_support_filter_all(a_);
        archive_read_support_format_all(a_);

        r = archive_read_open_memory(a_, mappedFile, file_->size());

        if (r != ARCHIVE_OK)
        {
            exit(1);
        }
    }

    nextPage();
}

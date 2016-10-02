/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#include "PdfComicArchiveReader.h"

#include <KronCore/exceptions/ArchiveReadErrorException.h>

#include <podofo/base/PdfDictionary.h>
#include <podofo/base/PdfMemStream.h>
#include <podofo/base/PdfName.h>
#include <podofo/base/PdfObject.h>
#include <podofo/doc/PdfMemDocument.h>
#include <podofo/doc/PdfPage.h>
#include <QDebug>
#include <QFile>
#include <QString>

#include <stdexcept>

namespace kron {

PdfComicArchiveReader::PdfComicArchiveReader()
    : file_(new QFile),
      buffer_(new char[10*1024*1024]),
      fileIndex_(0),
      bytesRead_(0)
{
}

PdfComicArchiveReader::~PdfComicArchiveReader()
{
}

void PdfComicArchiveReader::open(QString comicArchive)
{
    file_->setFileName(comicArchive);

    bool isOpen = file_->open(QIODevice::ReadOnly);

    if (!isOpen)
        throw ArchiveReadErrorException("Could not open file " + comicArchive.toStdString());

    uchar* mappedFile = file_->map(0, file_->size());
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

QByteArray PdfComicArchiveReader::readFirstImage()
{
    fileIndex_ = 0;
    return readNextImage();
}

QByteArray PdfComicArchiveReader::readNextImage()
{
    if (fileIndex_ < static_cast<quint32>(pdfImages_.size()))
    {
        PoDoFo::PdfObject *pObject = pdfImages_[fileIndex_];
        PoDoFo::PdfMemStream* pStream = dynamic_cast<PoDoFo::PdfMemStream*>(pObject->GetStream());
        buffer_ = const_cast<char*>(pStream->Get());
        bytesRead_ = pStream->GetLength();

        fileIndex_++;
    }
    else
        qDebug() << "Already on last image";

    QByteArray image(buffer_, bytesRead_);

    return image;
}

QByteArray PdfComicArchiveReader::readPreviousImage()
{
    if (fileIndex_ > 1)
    {
        fileIndex_--;

        PoDoFo::PdfObject *pObject = pdfImages_[fileIndex_ - 1];
        PoDoFo::PdfMemStream* pStream = dynamic_cast<PoDoFo::PdfMemStream*>(pObject->GetStream());
        buffer_ = const_cast<char*>(pStream->Get());
        bytesRead_ = pStream->GetLength();
    }
    else
        qDebug() << "Already on first image";

    QByteArray image(buffer_, bytesRead_);

    return image;
}

QString PdfComicArchiveReader::currentArchive() const
{
    return file_->fileName();
}

}

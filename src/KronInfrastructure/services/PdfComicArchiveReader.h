/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef KRON_PDFCOMICARCHIVEREADER_H
#define KRON_PDFCOMICARCHIVEREADER_H

#include "../KronInfrastructureExport.h"

#include <KronCore/services/ComicArchiveReader.h>

#include <podofo/base/PdfDefines.h>
#include <QVector>

#include <memory>

class QFile;

namespace PoDoFo {
class PdfMemDocument;
class PdfObject;
}


namespace kron {

class KRONINFRASTRUCTURE_EXPORT PdfComicArchiveReader : public ComicArchiveReader
{
public:
    PdfComicArchiveReader();

    virtual ~PdfComicArchiveReader();

    virtual void open(QString comicArchive);

    virtual QByteArray readFirstImage();

    virtual QByteArray readNextImage();

    virtual QByteArray readPreviousImage();

    virtual QString currentArchive() const;

private:
    std::unique_ptr<QFile> file_;
    char* buffer_;
    quint32 fileIndex_;
    PoDoFo::pdf_long bytesRead_;
    std::unique_ptr<PoDoFo::PdfMemDocument> pdfDoc_;
    QVector<PoDoFo::PdfObject*> pdfImages_;
};

}

#endif // KRON_PDFCOMICARCHIVEREADER_H

/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef COMPRESSEDCOMICARCHIVEREADER_H
#define COMPRESSEDCOMICARCHIVEREADER_H

#include "../KronInfrastructureExport.h"

#include <KronCore/services/ComicArchiveReader.h>

#include <QVarLengthArray>

#include <memory>

struct archive;
struct archive_entry;
class QFile;

namespace kron {

class KRONINFRASTRUCTURE_EXPORT CompressedComicArchiveReader : public ComicArchiveReader
{
public:
    CompressedComicArchiveReader();

    virtual ~CompressedComicArchiveReader();

    virtual void open(QString comicArchive);

    virtual QByteArray readFirstImage();

    virtual QByteArray readNextImage();

    virtual QByteArray readPreviousImage();

    virtual QString currentArchive() const;

private:
    std::unique_ptr<QFile> file_;
    char* buffer_;
    quint32 fileIndex_;
    struct archive* a_;
    struct archive_entry* entry_;
    QVarLengthArray<quint32, 128> imageToIndex_;
};

}

#endif // COMPRESSEDCOMICARCHIVEREADER_H

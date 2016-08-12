/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef FILECOMICARCHIVEREADER_H
#define FILECOMICARCHIVEREADER_H

#include "../KronInfrastructureExport.h"

#include <KronCore/services/ComicArchiveReader.h>

#include <memory>

namespace kron {

class KRONINFRASTRUCTURE_EXPORT FileComicArchiveReader : public ComicArchiveReader
{
public:
    FileComicArchiveReader();

    virtual ~FileComicArchiveReader();

    virtual void open(QString comicArchive);

    virtual QByteArray readFirstImage();

    virtual QByteArray readNextImage();

    virtual QByteArray readPreviousImage();

    virtual QString currentArchive() const;

private:
    std::unique_ptr<ComicArchiveReader> reader_;
};

}

#endif // FILECOMICARCHIVEREADER_H

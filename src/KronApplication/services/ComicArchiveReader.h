/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef COMICARCHIVEREADER
#define COMICARCHIVEREADER

#include "../KronApplicationExport.h"

#include <QByteArray>
#include <QString>

namespace kron {

class KRONAPPLICATION_EXPORT ComicArchiveReader
{
public:
    virtual ~ComicArchiveReader() {}

    // Open comic located in the passed path and close the previous comic if open
    virtual void open(QString comicArchive) = 0;

    virtual QByteArray readFirstImage() = 0;

    virtual QByteArray readNextImage() = 0;

    virtual QByteArray readPreviousImage() = 0;

    // Returns empty string if no archive open
    virtual QString currentArchive() const = 0;

protected:
    ComicArchiveReader() = default;
    ComicArchiveReader(const ComicArchiveReader&) = delete;
    ComicArchiveReader & operator=(const ComicArchiveReader&) = delete;
};

}

#endif // COMICARCHIVEREADER


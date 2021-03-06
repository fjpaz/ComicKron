/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#include "ComicArchiveReaderContract.h"

#include <KronInfrastructure/services/FileComicArchiveReader.h>

namespace kron {

ComicArchiveReader* createFileComicArchiveReader()
{
    return new FileComicArchiveReader;
}

INSTANTIATE_TEST_CASE_P(FileComicArchiveReaderTest,
                        ComicArchiveReaderContract,
                        ::testing::Values(&createFileComicArchiveReader));

}

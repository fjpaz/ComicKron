/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef ARCHIVEREADERROREXCEPTION_H
#define ARCHIVEREADERROREXCEPTION_H

#include "../KronApplicationExport.h"

#include <stdexcept>

namespace kron {

class KRONAPPLICATION_EXPORT ArchiveReadErrorException : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

}

#endif // ARCHIVEREADERROREXCEPTION_H


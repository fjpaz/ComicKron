/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef KRON_ARCHIVEREADERROREXCEPTION_H
#define KRON_ARCHIVEREADERROREXCEPTION_H

#include "../KronCoreExport.h"

#include <stdexcept>

namespace kron {

class KRONCORE_EXPORT ArchiveReadErrorException : public std::runtime_error
{
public:
    explicit ArchiveReadErrorException(const std::string& message);
};

}

#endif // KRON_ARCHIVEREADERROREXCEPTION_H

/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef ARCHIVENOTFOUNDEXCEPTION_H
#define ARCHIVENOTFOUNDEXCEPTION_H

#include "../KronApplicationExport.h"

#include <exception>

namespace kron {

class KRONAPPLICATION_EXPORT ArchiveNotFoundException : public std::exception
{
public:
    explicit ArchiveNotFoundException(const std::string& archive);

    virtual const char* what() const noexcept override;

private:
    std::string archive_;
};

}

#endif // ARCHIVENOTFOUNDEXCEPTION_H
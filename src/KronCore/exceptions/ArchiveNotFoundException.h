/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef KRON_ARCHIVENOTFOUNDEXCEPTION_H
#define KRON_ARCHIVENOTFOUNDEXCEPTION_H

#include "../KronCoreExport.h"

#include <exception>
#include <string>

namespace kron {

class KRONCORE_EXPORT ArchiveNotFoundException : public std::exception
{
public:
    explicit ArchiveNotFoundException(const std::string& archive);

    virtual const char* what() const Q_DECL_NOEXCEPT override;

private:
    std::string archive_;
};

}

#endif // KRON_ARCHIVENOTFOUNDEXCEPTION_H

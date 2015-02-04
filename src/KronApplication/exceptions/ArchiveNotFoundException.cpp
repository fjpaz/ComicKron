/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#include "ArchiveNotFoundException.h"

namespace kron {

ArchiveNotFoundException::ArchiveNotFoundException(const std::string& archive)
    : std::exception(),
      archive_(archive)
{
}

const char* ArchiveNotFoundException::what() const Q_DECL_NOEXCEPT
{
    std::string message = "Archive" + archive_ + " not found";

    return message.c_str();
}

}

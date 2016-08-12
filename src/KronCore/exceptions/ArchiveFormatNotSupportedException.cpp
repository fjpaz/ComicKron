/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#include "ArchiveFormatNotSupportedException.h"

namespace kron {

ArchiveFormatNotSupportedException::ArchiveFormatNotSupportedException(const std::string& archive)
    : std::exception(),
      archive_(archive)
{
}

const char* ArchiveFormatNotSupportedException::what() const Q_DECL_NOEXCEPT
{
    std::string message = "Archive" + archive_ + " format not supported";

    return message.c_str();
}

}

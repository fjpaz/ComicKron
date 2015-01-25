/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef IMAGECONTAINER
#define IMAGECONTAINER

#include "../KronApplicationExport.h"

class QByteArray;
class QString;

namespace kron {

class KRONAPPLICATION_EXPORT ImageContainer
{
public:
    virtual ~ImageContainer() = default;

    virtual void setImage(const QString& id, const QByteArray& raw) = 0;
};

}

#endif // IMAGECONTAINER


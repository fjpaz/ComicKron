/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef KRON_APPCONTEXT_H
#define KRON_APPCONTEXT_H

#include "../KronCoreExport.h"

#include <QObject>
#include <QString>

namespace kron {

class KRONCORE_EXPORT AppContext
{
public:
    virtual ~AppContext() {}

    virtual void setProperty(QString name, QObject& value) = 0;

    virtual QObject& property(QString name) const = 0;

    virtual void start() = 0;
};

}

#endif // KRON_APPCONTEXT_H

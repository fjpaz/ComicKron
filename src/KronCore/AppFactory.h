/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef KRON_APPFACTORY_H
#define KRON_APPFACTORY_H

#include "KronCoreExport.h"

#include <memory>
#include <QObject>

namespace kron {

class App;

class AppFactory : public QObject
{
    Q_OBJECT
public:
    virtual ~AppFactory() {}

    virtual std::unique_ptr<App> createApp() = 0;
};

}

#endif // KRON_APPFACTORY_H


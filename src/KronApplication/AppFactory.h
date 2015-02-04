/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef APPFACTORY_H
#define APPFACTORY_H

#include "KronApplicationExport.h"

#include <memory>

namespace kron {

class App;

class AppFactory
{
public:
    virtual ~AppFactory() {}

    virtual App* createApp() = 0;
};

}

#endif // APPFACTORY_H


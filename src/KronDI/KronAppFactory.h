/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef KRON_KRONAPPFACTORY_H
#define KRON_KRONAPPFACTORY_H

#include "CommonAppFactory.h"
#include "KronDIExport.h"

#include <memory>

class QQmlApplicationEngine;

namespace kron {

class KRONDI_EXPORT KronAppFactory : public CommonAppFactory
{
public:
    KronAppFactory();

    virtual ~KronAppFactory();

protected:
    std::unique_ptr<AppContext> createAppContext() override;

    void addSpecificContextProperties(App &app) override;
};

}

#endif // KRON_KRONAPPFACTORY_H

/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef KRON_KRONAPPFACTORY_H
#define KRON_KRONAPPFACTORY_H

#include "KronDIExport.h"

#include <KronCore/AppFactory.h>

#include <QObject>

class QQmlApplicationEngine;

namespace kron {

class KRONDI_EXPORT KronAppFactory : public QObject, public AppFactory
{
    Q_OBJECT
public:
    KronAppFactory();

    virtual ~KronAppFactory();

    virtual App* createApp() override;
};

}

#endif // KRON_KRONAPPFACTORY_H

/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef KRONAPPFACTORY_H
#define KRONAPPFACTORY_H

#include <KronApplication/AppFactory.h>

#include <QObject>

class QQmlApplicationEngine;

namespace kron {

class KronAppFactory : public QObject, public AppFactory
{
    Q_OBJECT
public:
    KronAppFactory();

    virtual ~KronAppFactory();

    virtual App* createApp() override;
};

}

#endif // KRONAPPFACTORY_H

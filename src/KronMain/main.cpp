/*********************************************************************
 * Copyright (C) 2014 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#include "SignalHandler.h"

#include <KronApplication/App.h>
#include <KronDI/KronAppFactory.h>

#include <QGuiApplication>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    kron::SignalHandler::handleSignals();

    kron::AppFactory* appFactory = new kron::KronAppFactory;

    kron::App* kronApp = appFactory->createApp();

    // TODO: Pass command line input (comic path)
    kronApp->run("");

    return app.exec();
}

/*********************************************************************
 * Copyright (C) 2014 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#include "SignalHandler.h"

#include <KronCore/App.h>
#include <KronDI/KronAppFactory.h>

#include <memory>
#include <QGuiApplication>
#include <QObject>

int main(int argc, char *argv[])
{
    // Instance Qt application object
    QGuiApplication::setApplicationName("ComicKron");
    QGuiApplication::setOrganizationName("ComicKron");
    QGuiApplication app(argc, argv);

    // Handle OS signals
    kron::SignalHandler::handleSignals();

    // Create app object
    std::unique_ptr<kron::AppFactory> appFactory(new kron::KronAppFactory);
    std::unique_ptr<kron::App> kronApp(appFactory->createApp());

    // TODO: Pass command line input (comic path)
    // Run application
    kronApp->run("");

    // Delete main objects on application exit. See QCoreApplication::exec() documentation.
    // As this object is the application root any other object in the hierarchy
    // will be destroyed as well.
    QObject::connect(&app, SIGNAL(aboutToQuit()),
                     kronApp.release(), SLOT(deleteLater()));
    QObject::connect(&app, SIGNAL(aboutToQuit()),
                     appFactory.release(), SLOT(deleteLater()));

    // Main event loop
    return app.exec();
}

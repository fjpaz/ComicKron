/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#include "App.h"

#include "services/AppContext.h"

#include <QCoreApplication>

namespace kron {

App::App(std::unique_ptr<AppContext> context)
    : QObject(),
      context_(std::move(context))
{
    // Clean-up on application exit. See QCoreApplication::exec() documentation.
    // As this object is the application root any other object in the hierarchy
    // will be destroyed as well.
    connect(QCoreApplication::instance(), SIGNAL(aboutToQuit()),
            this, SLOT(deleteLater()));
}

App::~App()
{
}

void App::addContextProperty(QString name, std::unique_ptr<QObject> property)
{
    context_->setProperty(name, *property);

    // Take ownership
    property.release()->setParent(this);
}

QObject& App::contexProperty(QString name) const
{
    return context_->property(name);
}

void App::run(QString input)
{
    Q_UNUSED(input) // TODO: If input is not empty load input comic

    context_->start();
}

}

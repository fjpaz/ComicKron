/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#include "QmlViewModelRegistrar.h"

#include <QQmlApplicationEngine>
#include <QQmlContext>

namespace kron {

QmlViewModelRegistrar::QmlViewModelRegistrar(QQmlApplicationEngine& engine)
    : engine_(engine)
{
}

QmlViewModelRegistrar::~QmlViewModelRegistrar()
{
}

void QmlViewModelRegistrar::registerViewModel(QString name, QObject& viewModel)
{
    engine_.rootContext()->setContextProperty(name, &viewModel);
}

}

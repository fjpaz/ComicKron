/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef QMLVIEWMODELREGISTRAR_H
#define QMLVIEWMODELREGISTRAR_H

#include "../KronUIExport.h"

#include <KronCore/services/ViewModelRegistrar.h>

class QQmlApplicationEngine;

namespace kron {

class KRONUI_EXPORT QmlViewModelRegistrar : public ViewModelRegistrar
{
public:
    QmlViewModelRegistrar(QQmlApplicationEngine& engine);

    virtual ~QmlViewModelRegistrar();

    virtual void registerViewModel(QString name, QObject& viewModel);

private:
    QQmlApplicationEngine& engine_;
};

}

#endif // QMLVIEWMODELREGISTRAR_H

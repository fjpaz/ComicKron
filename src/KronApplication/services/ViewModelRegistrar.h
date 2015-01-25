/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef VIEWMODELREGISTRAR_H
#define VIEWMODELREGISTRAR_H

#include "../KronApplicationExport.h"

#include <QString>

#include <memory>

class QObject;

namespace kron {

class KRONAPPLICATION_EXPORT ViewModelRegistrar
{
public:
    virtual ~ViewModelRegistrar() {}

    virtual void registerViewModel(QString name, QObject& viewModel) = 0;
};

}

#endif // VIEWMODELREGISTRAR_H


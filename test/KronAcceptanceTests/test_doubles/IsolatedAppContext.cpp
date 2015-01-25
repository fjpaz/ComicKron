/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#include "IsolatedAppContext.h"

namespace kron {

void IsolatedAppContext::setProperty(QString name, QObject& value)
{
    properties_.emplace(name.toStdString(), value);
}

QObject& IsolatedAppContext::property(QString name) const
{
    return properties_.at(name.toStdString());
}

void IsolatedAppContext::start()
{
}

}

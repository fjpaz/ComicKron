/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#include "AcceptanceAppFactory.h"

#include "IsolatedAppContext.h"

namespace kron {

AcceptanceAppFactory::AcceptanceAppFactory()
{
}

std::unique_ptr<AppContext> AcceptanceAppFactory::createAppContext()
{
    return std::unique_ptr<AppContext>(new IsolatedAppContext);
}

void AcceptanceAppFactory::addSpecificContextProperties(App &app)
{
    Q_UNUSED(app);
}

}

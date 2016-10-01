/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#include "KronAppFactory.h"

#include <KronCore/App.h>
#include <KronInfrastructure/services/RealDevice.h>
#include <KronUI/services/QmlAppContext.h>

namespace kron {

KronAppFactory::KronAppFactory()
    : CommonAppFactory()
{
}

KronAppFactory::~KronAppFactory()
{
}

std::unique_ptr<AppContext> KronAppFactory::createAppContext()
{
    return std::unique_ptr<AppContext>(new QmlAppContext);
}

void KronAppFactory::addSpecificContextProperties(App &app)
{
    app.addContextProperty("device", std::unique_ptr<QObject>(new RealDevice));
}

}

/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef KRON_ACCEPTANCEAPPFACTORY_H
#define KRON_ACCEPTANCEAPPFACTORY_H

#include <KronDI/CommonAppFactory.h>

namespace kron {

class AcceptanceAppFactory : public CommonAppFactory
{
public:
    AcceptanceAppFactory();

protected:
    std::unique_ptr<AppContext> createAppContext() override;

    void addSpecificContextProperties(App &app) override;
};

}

#endif // KRON_ACCEPTANCEAPPFACTORY_H

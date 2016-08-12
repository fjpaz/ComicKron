/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef ACCEPTANCEAPPFACTORY_H
#define ACCEPTANCEAPPFACTORY_H

#include <KronCore/AppFactory.h>

namespace kron {

class AcceptanceAppFactory : public AppFactory
{
public:
    AcceptanceAppFactory();

    virtual App* createApp() override;
};

}

#endif // ACCEPTANCEAPPFACTORY_H

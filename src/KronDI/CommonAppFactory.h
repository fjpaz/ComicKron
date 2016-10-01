/*********************************************************************
 * Copyright (C) 2016 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef KRON_COMMONAPPFACTORY_H
#define KRON_COMMONAPPFACTORY_H

#include <KronCore/AppFactory.h>

namespace kron {

class AppContext;

class CommonAppFactory : public AppFactory
{
public:
    CommonAppFactory();
    
    virtual std::unique_ptr<App> createApp() override;
    
protected:
    virtual std::unique_ptr<AppContext> createAppContext() = 0;

    virtual void addSpecificContextProperties(App& app) = 0;

private:
    void addCommonContextProperties(App& app);
};

}

#endif // KRON_COMMONAPPFACTORY_H

/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef ISOLATEDAPPCONTEXT_H
#define ISOLATEDAPPCONTEXT_H

#include <KronApplication/services/AppContext.h>

#include <functional>
#include <string>
#include <unordered_map>

class QObject;

namespace kron {

class IsolatedAppContext : public AppContext
{
public:
    virtual void setProperty(QString name, QObject& value) override;

    virtual QObject& property(QString name) const override;

    virtual void start() override;

private:
    std::unordered_map<std::string, std::reference_wrapper<QObject>> properties_;
};

}

#endif // ISOLATEDAPPCONTEXT_H

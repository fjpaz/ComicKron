/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef KRON_QMLAPPCONTEXT_H
#define KRON_QMLAPPCONTEXT_H

#include "../KronUIExport.h"

#include <KronCore/services/AppContext.h>

#include <memory>

class QQmlApplicationEngine;
class QQuickImageProvider;

namespace kron {

class KRONUI_EXPORT QmlAppContext : public AppContext
{
public:
    QmlAppContext(std::unique_ptr<QQuickImageProvider> imageProvider);

    virtual ~QmlAppContext();

    virtual void setProperty(QString name, QObject& value);

    virtual QObject& property(QString name) const;

    virtual void start();

private:
    std::unique_ptr<QQmlApplicationEngine> engine_;
};

}

#endif // KRON_QMLAPPCONTEXT_H

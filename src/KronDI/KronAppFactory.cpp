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
#include <KronUI/services/PixmapImageProvider.h>
#include <KronUI/services/QmlAppContext.h>

#include <QCoreApplication>

namespace kron {

KronAppFactory::KronAppFactory()
    : QObject()
{
    connect(QCoreApplication::instance(), SIGNAL(aboutToQuit()),
            this, SLOT(deleteLater()));
}

KronAppFactory::~KronAppFactory()
{
}

std::unique_ptr<AppContext> KronAppFactory::createAppContext(
        std::unique_ptr<ImageContainer> imageContainer)
{
    std::unique_ptr<QQuickImageProvider> imageProvider(
                reinterpret_cast<QQuickImageProvider*>(
                    imageContainer.release()));
    return std::unique_ptr<AppContext>(new QmlAppContext(
                                           std::move(imageProvider)));
}

std::unique_ptr<ImageContainer> KronAppFactory::createImageContainer()
{
    return std::unique_ptr<ImageContainer>(new PixmapImageProvider);
}

void KronAppFactory::addSpecificContextProperties(App &app)
{
    app.addContextProperty("device", std::unique_ptr<QObject>(new RealDevice));
}

}

/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#include "KronAppFactory.h"

#include "CommonModule.h"

#include <KronApplication/App.h>
#include <KronUI/services/PixmapImageProvider.h>
#include <KronUI/services/QmlAppContext.h>

#include <boost/di.hpp>
#include <QCoreApplication>

#include <memory>

namespace di = boost::di;

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

App* KronAppFactory::createApp()
{
    auto injector = di::make_injector(
                CommonModule(),
                di::object<di::bind<AppContext, QmlAppContext>>(),
                di::object<di::bind<di::any_of<ImageContainer, QQuickImageProvider>, PixmapImageProvider>>());

    injector.call(di::scopes::object_entry());

    App* app = injector.create<App*>();

    addContextProperties<decltype(injector)>(*app, injector);

    injector.call(di::scopes::object_exit());

    return app;
}

}

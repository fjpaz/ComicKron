/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#include "AcceptanceAppFactory.h"

#include "FakeImageContainer.h"
#include "IsolatedAppContext.h"

#include <KronDI/CommonModule.h>

namespace kron {

AcceptanceAppFactory::AcceptanceAppFactory()
{
}

App* AcceptanceAppFactory::createApp()
{
    auto injector = di::make_injector(
                CommonModule(),
                di::object<di::bind<AppContext, IsolatedAppContext>>(),
                di::object<di::bind<ImageContainer, FakeImageContainer>>());

    injector.call(di::scopes::object_entry());

    App* app = injector.create<App*>();
    std::unique_ptr<ComicReaderVM> comicReaderVM = injector.create<std::unique_ptr<ComicReaderVM>>();

    app->addContextProperty("model", std::unique_ptr<QObject>(comicReaderVM.release()));

    injector.call(di::scopes::object_exit());

    return app;
}

}

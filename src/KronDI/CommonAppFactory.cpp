/*********************************************************************
 * Copyright (C) 2016 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#include "CommonAppFactory.h"

#include <KronCore/App.h>
#include <KronCore/services/AppContext.h>
#include <KronCore/viewmodels/ComicReaderVM.h>
#include <KronCore/viewmodels/FileBrowserVM.h>
#include <KronInfrastructure/services/FileComicArchiveReader.h>

namespace kron {

CommonAppFactory::CommonAppFactory()
{
}

std::unique_ptr<App> CommonAppFactory::createApp()
{
    std::unique_ptr<App> app(new App(createAppContext()));

    addCommonContextProperties(*app);
    addSpecificContextProperties(*app);

    return app;
}

void CommonAppFactory::addCommonContextProperties(App& app)
{
    std::unique_ptr<ComicArchiveReader> archiveReader(
                new FileComicArchiveReader);
    app.addContextProperty(
                "readerVM",
                std::unique_ptr<QObject>(new ComicReaderVM(
                        std::move(archiveReader))));
    app.addContextProperty(
                "fileBrowserVM", std::unique_ptr<QObject>(new FileBrowserVM));
}

}

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
#include <KronCore/services/ImageContainer.h>
#include <KronCore/viewmodels/ComicReaderVM.h>
#include <KronCore/viewmodels/FileBrowserVM.h>
#include <KronInfrastructure/services/FileComicArchiveReader.h>

namespace kron {

CommonAppFactory::CommonAppFactory()
{
}

App* CommonAppFactory::createApp()
{
    std::unique_ptr<ImageContainer> imageContainer(createImageContainer());
    ImageContainer& imageContainerRef = *imageContainer;
    std::unique_ptr<AppContext> appContext(createAppContext(std::move(imageContainer)));
    App* app = new App(std::move(appContext));

    addCommonContextProperties(*app, imageContainerRef);
    addSpecificContextProperties(*app);

    return app;
}

void CommonAppFactory::addCommonContextProperties(
        App& app, ImageContainer& imageContainer)
{
    std::unique_ptr<ComicArchiveReader> archiveReader(
                new FileComicArchiveReader);
    app.addContextProperty(
                "readerVM",
                std::unique_ptr<QObject>(new ComicReaderVM(
                        std::move(archiveReader), imageContainer)));
    app.addContextProperty(
                "fileBrowserVM", std::unique_ptr<QObject>(new FileBrowserVM));
}

}

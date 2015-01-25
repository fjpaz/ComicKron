/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef COMMONMODULE_H
#define COMMONMODULE_H

#include "KronDIExport.h"

#include <KronApplication/App.h>
#include <KronApplication/viewmodels/ComicReaderVM.h>
#include <KronInfrastructure/services/FileComicArchiveReader.h>

#include <boost/di.hpp>

namespace di = boost::di;

namespace kron {

class KRONDI_EXPORT CommonModule
{
public:
    auto configure() const -> decltype(di::make_injector(
                                           di::object<di::bind<ComicReaderVM>>(),
                                           di::object<di::bind<ComicArchiveReader, FileComicArchiveReader>>()))
    {
        return di::make_injector(
                    di::object<di::bind<ComicReaderVM>>(),
                    di::object<di::bind<ComicArchiveReader, FileComicArchiveReader>>());
    }
};

template<class T>
KRONDI_EXPORT void addContextProperties(App& app, T& injector)
{
    std::unique_ptr<ComicReaderVM> comicReaderVM = injector.template create<std::unique_ptr<ComicReaderVM>>();

    app.addContextProperty("model", std::unique_ptr<QObject>(comicReaderVM.release()));
}

}

#endif // COMMONMODULE_H


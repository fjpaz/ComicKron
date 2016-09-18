/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef KRON_COMMONMODULE_H
#define KRON_COMMONMODULE_H

#include <KronCore/App.h>
#include <KronCore/viewmodels/ComicReaderVM.h>
#include <KronCore/viewmodels/FileBrowserVM.h>
#include <KronInfrastructure/services/FileComicArchiveReader.h>
#include <KronInfrastructure/services/RealDevice.h>

#include <boost/di.hpp>

namespace di = boost::di;

namespace kron {

class CommonModule
{
public:
    auto configure() const -> decltype(di::make_injector(
                                           di::object<di::bind<ComicReaderVM>>(),
                                           di::object<di::bind<ComicArchiveReader, FileComicArchiveReader>>(),
                                           di::object<di::bind<Device, RealDevice>>()))
    {
        return di::make_injector(
                    di::object<di::bind<ComicReaderVM>>(),
                    di::object<di::bind<ComicArchiveReader, FileComicArchiveReader>>(),
                    di::object<di::bind<Device, RealDevice>>());
    }
};

template<class T>
void addContextProperties(App& app, T& injector)
{
    std::unique_ptr<Device> device = injector.template create<std::unique_ptr<Device>>();
    std::unique_ptr<ComicReaderVM> comicReaderVM = injector.template create<std::unique_ptr<ComicReaderVM>>();

    app.addContextProperty("device", std::unique_ptr<QObject>(device.release()));
    app.addContextProperty("readerVM", std::unique_ptr<QObject>(comicReaderVM.release()));
}

}

#endif // KRON_COMMONMODULE_H


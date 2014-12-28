/*********************************************************************
 * Copyright (C) 2014 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#include <KronApplication/ComicImageProvider.h>
#include <KronApplication/ComicViewerViewModel.h>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    ComicImageProvider* imageProvider = new ComicImageProvider;
    ComicViewerViewModel viewModel(*imageProvider);

    QQmlApplicationEngine engine;
    engine.addImageProvider("comic", imageProvider);
    engine.rootContext()->setContextProperty("model", &viewModel);
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    return app.exec();
}

/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#include "QmlAppContext.h"

#include "../items/Comic.h"
#include "../items/ImageShowcase.h"

#include <KronCore/services/Device.h>
#include <KronCore/viewmodels/FileBrowserVM.h>

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QString>

namespace kron {

QmlAppContext::QmlAppContext()
    : engine_(new QQmlApplicationEngine)
{
    qmlRegisterType<ImageShowcase>("ComicKron", 1, 0, "ImageShowcase");
    qmlRegisterType<Comic>("ComicKron", 1, 0, "Comic");
    qmlRegisterUncreatableType<FsItem>(
                "ComicKron.FsItem", 1, 0, "FsItem",
                "You cannot create an instance of the FsItem item");
    qmlRegisterUncreatableType<Device>(
                "ComicKron.Device", 1, 0, "Device",
                "You cannot create an instance of the Device item");
}

QmlAppContext::~QmlAppContext()
{
}

void QmlAppContext::setProperty(QString name, QObject& value)
{
    engine_->rootContext()->setContextProperty(name, &value);
}

QObject& QmlAppContext::property(QString name) const
{
    return *qvariant_cast<QObject*>(engine_->rootContext()->contextProperty(name));
}

void QmlAppContext::start()
{
    QUrl url = QStringLiteral("qrc:///views/main.qml");
    engine_->load(url);
}

}


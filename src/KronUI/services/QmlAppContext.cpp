/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#include "QmlAppContext.h"

#include "../items/ImageShowcase.h"

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QString>

namespace kron {

QmlAppContext::QmlAppContext()
    : engine_(new QQmlApplicationEngine)
{
    qmlRegisterType<ImageShowcase>("ComicKron", 1, 0, "ImageShowcase");
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


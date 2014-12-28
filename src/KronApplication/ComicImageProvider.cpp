/*********************************************************************
 * Copyright (C) 2014 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#include "ComicImageProvider.h"

#include <QPixmap>

#include <QDebug>

ComicImageProvider::ComicImageProvider() :
    QQuickImageProvider(Pixmap),
    pixmap_(new QPixmap)
{
}

QPixmap ComicImageProvider::requestPixmap(const QString& id, QSize* size, const QSize& requestedSize)
{
    qDebug() << "ComicImageProvider::requestPixmap "<< id;

    if (id == "current")
    {
        if (requestedSize.isValid())
        {
            pixmap_->scaled(requestedSize);
        }

        *size = pixmap_->size();

        return *pixmap_;
    }
    else
    {
        QPixmap emptyPixmap;
        return emptyPixmap;
    }
}

void ComicImageProvider::setPixmap(const QPixmap& pixmap)
{
    *pixmap_ = pixmap;
}

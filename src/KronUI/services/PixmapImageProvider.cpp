/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#include "PixmapImageProvider.h"

namespace kron {

PixmapImageProvider::PixmapImageProvider()
    : QQuickImageProvider(Pixmap),
      pixmaps_()
{
}

PixmapImageProvider::~PixmapImageProvider()
{
}

QPixmap PixmapImageProvider::requestPixmap(const QString& id, QSize* size, const QSize& requestedSize)
{
    QPixmap requestedPixmap = pixmaps_.value(id);

    if (requestedSize.isValid())
    {
        requestedPixmap.scaled(requestedSize);
    }

    *size = requestedPixmap.size();

    return pixmaps_.value(id);
}

void PixmapImageProvider::setImage(const QString& id, const QByteArray& raw)
{
    QPixmap newPixmap;
    newPixmap.loadFromData(raw);

    pixmaps_[id] = newPixmap;
}

}

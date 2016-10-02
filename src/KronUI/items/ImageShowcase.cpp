/*********************************************************************
 * Copyright (C) 2016 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#include "ImageShowcase.h"

#include <QPainter>

namespace kron {

ImageShowcase::ImageShowcase(QQuickItem* parent)
    : QQuickPaintedItem(parent)
{
}

QVariant ImageShowcase::image() const
{
    return imageBytes_;
}

void ImageShowcase::paint(QPainter* painter)
{
    qreal aspectRatio = static_cast<qreal>(image_.width()) / image_.height();
    qreal paintWidth = height() * aspectRatio;

    if (paintWidth <= width())
    {
        painter->drawImage(QRectF(x() + width() / 2.0 - paintWidth / 2.0, y(), paintWidth, height()), image_);
    }
    else
    {
        qreal paintHeight = width() / aspectRatio;

        painter->drawImage(QRectF(x(), y() + height() / 2.0 - paintHeight / 2.0, width(), paintHeight), image_);
    }
}

void ImageShowcase::setImage(QVariant image)
{
    imageBytes_ = image.toByteArray();
    image_.loadFromData(imageBytes_);

    update();
}

}

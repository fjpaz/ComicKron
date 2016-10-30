/*********************************************************************
 * Copyright (C) 2016 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#include "ImageShowcase.h"

#include <QDebug>
#include <QPainter>
#include <QTouchEvent>

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
    painter->drawImage(paintRect_, image_);
}

void ImageShowcase::setImage(QVariant image)
{
    imageBytes_ = image.toByteArray();
    image_.loadFromData(imageBytes_);

    calculatePaintParameters();

    update();
}

void ImageShowcase::touchEvent(QTouchEvent* event)
{
    foreach (const QTouchEvent::TouchPoint& touchPoint, event->touchPoints())
    {
        qDebug() << touchPoint;
    }
}

void ImageShowcase::calculatePaintParameters()
{
    const qreal aspectRatio = static_cast<qreal>(
                image_.width()) / image_.height();
    const qreal itemX = x();
    const qreal itemY = y();
    const qreal itemWidth = width();
    const qreal itemHeight = height();
    const qreal widthAR = itemHeight * aspectRatio;
    qreal paintX, paintY, paintWidth, paintHeight;

    if (widthAR <= itemWidth)
    {
        paintWidth = widthAR;
        paintHeight = itemHeight;
        paintX = itemX + itemWidth / 2.0 - paintWidth / 2.0;
        paintY = itemY;
    }
    else
    {
        paintWidth = itemWidth;
        paintHeight = itemWidth / aspectRatio;
        paintX = itemX;
        paintY = itemY + itemHeight / 2.0 - paintHeight / 2.0;
    }

    paintRect_ = QRectF(paintX, paintY, paintWidth, paintHeight);
}

}

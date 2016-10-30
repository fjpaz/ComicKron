/*********************************************************************
 * Copyright (C) 2016 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef KRON_IMAGESHOWCASE_H
#define KRON_IMAGESHOWCASE_H

#include "../KronUIExport.h"

#include <QByteArray>
#include <QImage>
#include <QQuickPaintedItem>
#include <QRectF>
#include <QVariant>

namespace kron {

class KRONUI_EXPORT ImageShowcase : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QVariant image READ image WRITE setImage)
public:
    ImageShowcase(QQuickItem* parent = nullptr);

    Q_INVOKABLE QVariant image() const;

    virtual void paint(QPainter* painter) override;

public slots:
    void setImage(QVariant image);

protected:
    virtual void touchEvent(QTouchEvent* event) override;

private:
    void calculatePaintParameters();

    QByteArray imageBytes_;
    QImage image_;
    QRectF paintRect_;
};

}

#endif // KRON_IMAGESHOWCASE_H

/*********************************************************************
 * Copyright (C) 2016 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef KRON_COMIC_H
#define KRON_COMIC_H

#include "../KronUIExport.h"

#include <QByteArray>
#include <QContiguousCache>
#include <QParallelAnimationGroup>
#include <QPixmap>
#include <QPointF>
#include <QQuickPaintedItem>
#include <QRectF>
#include <QTime>
#include <QVariant>

class QPropertyAnimation;

namespace kron {

class KRONUI_EXPORT Comic : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QVariant image READ image WRITE setImage)
    Q_PROPERTY(QPointF centerOffset READ centerOffset WRITE setCenterOffset)
    Q_PROPERTY(qreal scaleFactor READ scaleFactor WRITE setScaleFactor)

    struct TouchPosTime
    {
        QPointF posDelta;
        QTime time;
    };

public:
    Comic(QQuickItem* parent = nullptr);

    Q_INVOKABLE QVariant image() const;

    Q_INVOKABLE QPointF centerOffset() const;

    Q_INVOKABLE void setCenterOffset(QPointF centerOffset);

    Q_INVOKABLE qreal scaleFactor() const;

    Q_INVOKABLE void setScaleFactor(qreal scaleFactor);

    virtual void paint(QPainter* painter) override;

public slots:
    void setImage(QVariant image);

signals:
    void nextRequested();

    void previousRequested();

    void moreActionsRequested();

protected:
    virtual void touchEvent(QTouchEvent* event) override;

    virtual void wheelEvent(QWheelEvent* event) override;

    virtual void keyReleaseEvent(QKeyEvent* event) override;

    void geometryChanged(const QRectF& newGeometry, const QRectF& oldGeometry) override;

private:
    bool imageOutOfLimits() const;

    bool swipeNext() const;

    bool swipePrevious() const;

    void moveImageInsideLimits();

    void calculatePaintParameters();

    void calculateMaxOffsets();

    static constexpr qreal SCALE_EXP_BASE = 1.0025;
    static constexpr qreal MAX_SCALE_FACTOR = 8.0;
    static constexpr qreal MAX_SCALE_MARGIN = 2.0;
    static constexpr qreal MIN_SCALE_MARGIN = 0.1666;
    static constexpr int ANIMATION_DURATION = 500;
    static constexpr qreal OUT_FRICTION_FACTOR = 3.0;
    static constexpr qreal PREV_AREA_END = 1.0 / 4.0;
    static constexpr qreal NEXT_AREA_START = 3.0 / 4.0;
    static constexpr qreal TOUCH_MARGIN = 5;
    static constexpr int MAX_INERTIA_INTERVAL = 100;
    static constexpr int INERTIA_LENGTH_MSECS = 250;
    static constexpr qreal MIN_SWIPE_LENGTH = 100.0;
    static constexpr qreal MAX_SWIPE_INTERVAL = 100.0;

    QByteArray imageBytes_;
    QPixmap image_;
    QPropertyAnimation* panAnimation_;
    QPropertyAnimation* zoomAnimation_;
    QParallelAnimationGroup parallelAnimation_;
    QContiguousCache<TouchPosTime> lastPanTouchs_;
    QRectF paintRect_;
    QPointF itemCenter_;
    QPointF centerOffset_;
    qreal scaleFactor_;
    qreal aspectRatio_;
    qreal widthAR_;
    qreal heightAR_;
    qreal maxXOffset_;
    qreal maxYOffset_;
    bool tapInProgress_;
    bool panInProgress_;
    bool pinchInProgress_;
    bool swipeInProgress_;
    bool updatePending_;
};

}

#endif // KRON_COMIC_H

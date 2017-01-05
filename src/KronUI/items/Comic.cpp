/*********************************************************************
 * Copyright (C) 2016 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#include "Comic.h"

#include <QDebug>
#include <QElapsedTimer>
#include <QPainter>
#include <QPropertyAnimation>
#include <QTouchEvent>
#include <QtGlobal>
#include <QtMath>

namespace kron {

Comic::Comic(QQuickItem* parent)
    : QQuickPaintedItem(parent),
      panAnimation_(new QPropertyAnimation(this, "centerOffset")),
      zoomAnimation_(new QPropertyAnimation(this, "scaleFactor")),
      parallelAnimation_(),
      lastPanTouchs_(4),
      scaleFactor_(1.0),
      aspectRatio_(1.0),
      tapInProgress_(false),
      panInProgress_(false),
      pinchInProgress_(false),
      swipeInProgress_(false)
{
    parallelAnimation_.addAnimation(panAnimation_);
    parallelAnimation_.addAnimation(zoomAnimation_);

    setRenderTarget(QQuickPaintedItem::FramebufferObject);
    setAcceptedMouseButtons(Qt::AllButtons);
}

QVariant Comic::image() const
{
    return imageBytes_;
}

QPointF Comic::centerOffset() const
{
    return centerOffset_;
}

void Comic::setCenterOffset(QPointF centerOffset)
{
    centerOffset_ = centerOffset;

    if (imageOutOfLimits())
        moveImageInsideLimits();

    update();
}

qreal Comic::scaleFactor() const
{
    return scaleFactor_;
}

void Comic::setScaleFactor(qreal scaleFactor)
{
    scaleFactor_ = scaleFactor;

    calculateMaxOffsets();

    update();
}

void Comic::paint(QPainter* painter)
{
    QElapsedTimer timer;
    timer.start();

    qDebug() << "Comic paint start. centerOffset:" << centerOffset_ <<
                "scaleFactor:" << scaleFactor_;

    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->translate(itemCenter_);
    painter->scale(scaleFactor_, scaleFactor_);
    painter->translate(centerOffset_ - itemCenter_);

    painter->drawPixmap(paintRect_, image_, image_.rect());

    qDebug() << "Comic paint elapsed" << timer.elapsed() << "ms";
}

void Comic::setImage(QVariant image)
{
    imageBytes_ = image.toByteArray();
    image_.loadFromData(imageBytes_);
    aspectRatio_ = static_cast<qreal>(image_.width()) / image_.height();
    centerOffset_ = QPointF(0.0, 0.0);
    scaleFactor_ = 1.0;

    calculatePaintParameters();
    calculateMaxOffsets();

    update();
}

void Comic::touchEvent(QTouchEvent* event)
{
    processTouchs(event->touchPoints(), event->touchPointStates());
}

void Comic::wheelEvent(QWheelEvent *event)
{
    qreal scaleFactor = scaleFactor_ * qPow(1.0025, event->delta());
    bool maxScaleReached = false;
    bool minScaleReached = false;

    if (scaleFactor < 1.0)
    {
        minScaleReached = true;
        scaleFactor = 1.0;
        centerOffset_ = QPointF(0.0, 0.0);
    }
    else if (scaleFactor > MAX_SCALE_FACTOR)
    {
        maxScaleReached = true;
        scaleFactor = MAX_SCALE_FACTOR;
    }

    zoomAnimation_->stop();
    zoomAnimation_->setStartValue(scaleFactor_);
    zoomAnimation_->setEndValue(scaleFactor);
    zoomAnimation_->setDuration(ANIMATION_DURATION);
    zoomAnimation_->setEasingCurve(QEasingCurve::OutCirc);

    if (maxScaleReached)
        // Go beyond maximum scale and bounce back
        zoomAnimation_->setKeyValueAt(0.5, scaleFactor + MAX_SCALE_MARGIN);
    else if (minScaleReached)
        // Go beyong minimum scale and bounce back
        zoomAnimation_->setKeyValueAt(0.5, scaleFactor - MIN_SCALE_MARGIN);
    else
    {
        // Follow easing curve using its middle value
        QEasingCurve easingCurve = zoomAnimation_->easingCurve();
        qreal midCurveValue = easingCurve.valueForProgress(0.5);
        QVariant midValue;

        if (scaleFactor > scaleFactor_)
            midValue = scaleFactor_ +
                    midCurveValue * (scaleFactor - scaleFactor_);
        else
            midValue = scaleFactor_ -
                    midCurveValue * (scaleFactor_ - scaleFactor);

        zoomAnimation_->setKeyValueAt(0.5, midValue);
    }

    zoomAnimation_->start();

    qDebug() << "On Wheel event scaleFactor:" << scaleFactor;
}

void Comic::keyReleaseEvent(QKeyEvent* event)
{
    qDebug() << "Key release event";

    switch (event->key())
    {
    case Qt::Key_Left:
        event->accept();
        emit previousRequested();
        break;
    case Qt::Key_Right:
        event->accept();
        emit nextRequested();
        break;
    default:
        break;
    }
}

void Comic::mousePressEvent(QMouseEvent* event)
{
    if (!event->buttons().testFlag(Qt::LeftButton))
        return;

    qDebug() << "width:" << width() << "localPos:" << event->localPos();

    const QPointF& pos = event->localPos();
    startPosMouse_ = pos;
    lastPosMouse_ = pos;

    QTouchEvent::TouchPoint touchPoint;
    touchPoint.setId(1);
    touchPoint.setPos(pos);
    touchPoint.setRect(QRectF(pos.x() - 2, pos.y() - 2, 4, 4));
    touchPoint.setStartPos(pos);
    touchPoint.setLastPos(pos);

    QList<QTouchEvent::TouchPoint> touchPoints = {touchPoint};
    Qt::TouchPointStates touchPointStates;
    touchPointStates.setFlag(Qt::TouchPointPressed);

    processTouchs(touchPoints, touchPointStates);
}

void Comic::mouseMoveEvent(QMouseEvent* event)
{
    if (!event->buttons().testFlag(Qt::LeftButton))
        return;

    const QPointF& pos = event->localPos();

    QTouchEvent::TouchPoint touchPoint;
    touchPoint.setId(1);
    touchPoint.setPos(pos);
    touchPoint.setRect(QRectF(pos.x() - 2, pos.y() - 2, 4, 4));
    touchPoint.setStartPos(startPosMouse_);
    touchPoint.setLastPos(lastPosMouse_);

    QList<QTouchEvent::TouchPoint> touchPoints = {touchPoint};
    Qt::TouchPointStates touchPointStates;
    touchPointStates.setFlag(Qt::TouchPointMoved);
    lastPosMouse_ = pos;

    processTouchs(touchPoints, touchPointStates);
}

void Comic::mouseReleaseEvent(QMouseEvent* event)
{
    if (startPosMouse_ == QPointF(-1, -1))
        return;

    const QPointF& pos = event->localPos();

    QTouchEvent::TouchPoint touchPoint;
    touchPoint.setId(1);
    touchPoint.setPos(pos);
    touchPoint.setRect(QRectF(pos.x() - 2, pos.y() - 2, 4, 4));
    touchPoint.setStartPos(startPosMouse_);
    touchPoint.setLastPos(lastPosMouse_);

    QList<QTouchEvent::TouchPoint> touchPoints = {touchPoint};
    Qt::TouchPointStates touchPointStates;
    touchPointStates.setFlag(Qt::TouchPointReleased);
    startPosMouse_ = {-1, -1};

    processTouchs(touchPoints, touchPointStates);
}

void Comic::geometryChanged(const QRectF& newGeometry, const QRectF& oldGeometry)
{
    QQuickItem::geometryChanged(newGeometry, oldGeometry);

    calculatePaintParameters();
    calculateMaxOffsets();
}

bool Comic::imageOutOfLimits() const
{
    bool outOfLimits = false;

    if (centerOffset_.x() > maxXOffset_ ||
        centerOffset_.x() < -maxXOffset_ ||
        centerOffset_.y() > maxYOffset_ ||
        centerOffset_.y() < -maxYOffset_)
    {
        outOfLimits = true;
    }

    return outOfLimits;
}

bool Comic::swipeNext() const
{
    if (swipeInProgress_ &&
        centerOffset_.x() < (-maxXOffset_ - MIN_SWIPE_LENGTH) / scaleFactor_ &&
        lastPanTouchs_.isFull() &&
        lastPanTouchs_.first().time.msecsTo(lastPanTouchs_.last().time) <
            MAX_SWIPE_INTERVAL)
        return true;
    else return false;
}

bool Comic::swipePrevious() const
{
    if (swipeInProgress_ &&
        centerOffset_.x() > (maxXOffset_ + MIN_SWIPE_LENGTH) / scaleFactor_ &&
        lastPanTouchs_.isFull() &&
        lastPanTouchs_.first().time.msecsTo(lastPanTouchs_.last().time) <
            MAX_SWIPE_INTERVAL)
        return true;
    else return false;
}

void Comic::moveImageInsideLimits()
{
    QPointF destinationOffset = centerOffset_;

    if (centerOffset_.x() > maxXOffset_)
        destinationOffset.setX(maxXOffset_);
    else if (centerOffset_.x() < -maxXOffset_)
        destinationOffset.setX(-maxXOffset_);

    if (centerOffset_.y() > maxYOffset_)
        destinationOffset.setY(maxYOffset_);
    else if (centerOffset_.y() < -maxYOffset_)
        destinationOffset.setY(-maxYOffset_);

    if (panAnimation_->state() == QAbstractAnimation::Stopped)
    {
        panAnimation_->setStartValue(centerOffset_);
        panAnimation_->setEndValue(destinationOffset);
        panAnimation_->setDuration(ANIMATION_DURATION);
        panAnimation_->setEasingCurve(QEasingCurve::OutCirc);
        panAnimation_->start();
    }
}

void Comic::calculatePaintParameters()
{
    const qreal itemX = x();
    const qreal itemY = y();
    const qreal itemWidth = width();
    const qreal itemHeight = height();
    itemCenter_ = QPointF(
                itemX + itemWidth / 2.0, itemY + itemHeight / 2.0);
    widthAR_ = itemHeight * aspectRatio_;
    heightAR_ = itemWidth / aspectRatio_;
    qreal paintX, paintY, paintWidth, paintHeight;

    if (widthAR_ <= itemWidth)
    {
        paintWidth = widthAR_;
        paintHeight = itemHeight;
        paintX = itemCenter_.x() - paintWidth / 2.0;
        paintY = itemCenter_.y() - paintHeight / 2.0;
    }
    else
    {
        paintWidth = itemWidth;
        paintHeight = heightAR_;
        paintX = itemCenter_.x() - paintWidth / 2.0;
        paintY = itemCenter_.y() - paintHeight / 2.0;
    }

    paintRect_ = QRectF(paintX, paintY, paintWidth, paintHeight);

    qDebug() << "itemCenter:" << itemCenter_ << "paintRect:" << paintRect_;
}

void Comic::calculateMaxOffsets()
{
    if (widthAR_ <= width())
    {
        maxXOffset_ = widthAR_ / 2.0 - width() / (scaleFactor_ * 2.0);
        maxYOffset_ = height() / 2.0 - height() / (scaleFactor_ * 2.0);

        maxXOffset_ = qMax(maxXOffset_, 0.0);
    }
    else
    {
        maxXOffset_ = width() / 2.0 - width() / (scaleFactor_ * 2.0);
        maxYOffset_ = heightAR_ / 2.0 - height() / (scaleFactor_ * 2.0);

        maxYOffset_ = qMax(maxYOffset_, 0.0);
    }
}

void Comic::processTouchs(
        const QList<QTouchEvent::TouchPoint>& touchPoints,
        Qt::TouchPointStates touchPointStates)
{
    foreach (const QTouchEvent::TouchPoint& touchPoint, touchPoints)
    {
        qDebug() << touchPoint;
    }

    static const QPointF margin = QPointF(TOUCH_MARGIN, TOUCH_MARGIN);
    const int numTouchPoints = touchPoints.size();
    const auto firstTouchPoint = touchPoints.at(0);
    const QPointF firstStartPos = firstTouchPoint.startPos();
    const QPointF firstPos = firstTouchPoint.pos();
    const qreal firstPosX = firstPos.x();
    const qreal itemWidth = width();

    if (touchPointStates == Qt::TouchPointPressed)
    {
        panAnimation_->stop();

        bool inLeftLimit = qFuzzyCompare(centerOffset_.x(), maxXOffset_);
        bool inRightLimit = qFuzzyCompare(centerOffset_.x(), -maxXOffset_);

        if (inLeftLimit || inRightLimit)
            swipeInProgress_ = true;
    }

    if (numTouchPoints == 1)
    {
        qDebug() << "One touch point gesture in progress";

        QRectF tapRect = QRectF(firstStartPos - margin, firstStartPos + margin);

        if (tapRect.contains(firstPos))
        {
            if (touchPointStates == Qt::TouchPointPressed)
            {
                qDebug() << "Tap in progress";

                tapInProgress_ = true;
            }
        }
        else
        {
            panInProgress_ = true;
            tapInProgress_ = false;
        }

        pinchInProgress_ = false;
    }
    else
    {
        qDebug() << "Two touch points gesture in progress";

        pinchInProgress_ = true;
    }

    if (tapInProgress_ && (touchPointStates == Qt::TouchPointReleased))
    {
        qDebug() << "Single tap";

        if (firstPosX >= itemWidth * NEXT_AREA_START)
        {
            qDebug() << "Next requested";

            emit nextRequested();
        }
        else if (firstPosX <= itemWidth * PREV_AREA_END)
        {
            qDebug() << "Previous requested";

            emit previousRequested();
        }
        else
        {
            qDebug() << "More Actions requested";

            emit moreActionsRequested();
        }
    }
    else if (panInProgress_)
    {
        qDebug() << "Pan in progress";

        const qreal frictionFactor = imageOutOfLimits() ?
                    OUT_FRICTION_FACTOR : 1.0;
        const QPointF panDelta = firstPos - firstTouchPoint.lastPos();

        if (Qt::TouchPointMoved == touchPointStates)
        {
            TouchPosTime touchPosTime;
            touchPosTime.posDelta = panDelta;
            touchPosTime.time = QTime::currentTime();
            lastPanTouchs_.append(touchPosTime);
        }

        centerOffset_ += panDelta / (scaleFactor_ * frictionFactor);

        qDebug() << "centerOffset:" << centerOffset_ <<
                    "currentPos:" << firstPos <<
                    "lastPos:" << firstTouchPoint.lastPos() <<
                    "panDelta:" << panDelta;

        update();
    }
    else if (pinchInProgress_)
    {
        qDebug() << "Pinch in progrees";

        const auto secondTouchPoint = touchPoints.at(1);
        const QPointF firstLastPos = firstTouchPoint.lastPos();
        const QPointF secondLastPos = secondTouchPoint.lastPos();
        const QPointF secondPos = secondTouchPoint.pos();
        const qreal lastDistance = QLineF(firstLastPos, secondLastPos).length();
        const qreal distance = QLineF(firstPos, secondPos).length();
        const qreal delta = distance - lastDistance;

        scaleFactor_ *= qPow(SCALE_EXP_BASE, delta);

            if (scaleFactor_ > MAX_SCALE_FACTOR + MAX_SCALE_MARGIN)
            scaleFactor_ = MAX_SCALE_FACTOR + MAX_SCALE_MARGIN;
        else if (scaleFactor_ < 1.0 - MIN_SCALE_MARGIN)
            scaleFactor_ = 1.0 - MIN_SCALE_MARGIN;

        calculateMaxOffsets();

        qDebug() << "scaleFactor:" << scaleFactor_ <<
                    "delta:" << delta <<
                    "startDistance:" << lastDistance <<
                    "distance:" << distance;

        update();
    }

    if (Qt::TouchPointReleased == touchPointStates)
    {
        if (scaleFactor_ < 1.0)
        {
            // Scale to fit item and center on gesture end
            panAnimation_->setStartValue(centerOffset_);
            panAnimation_->setEndValue(QPointF(0.0, 0.0));
            panAnimation_->setDuration(ANIMATION_DURATION);
            panAnimation_->setEasingCurve(QEasingCurve::OutCirc);

            zoomAnimation_->setStartValue(scaleFactor_);
            zoomAnimation_->setEndValue(1.0);
            zoomAnimation_->setDuration(ANIMATION_DURATION);
            zoomAnimation_->setEasingCurve(QEasingCurve::OutCirc);

            parallelAnimation_.start();
        }
        else if (scaleFactor_ > MAX_SCALE_FACTOR)
        {
            zoomAnimation_->setStartValue(scaleFactor_);
            zoomAnimation_->setEndValue(MAX_SCALE_FACTOR);
            zoomAnimation_->setDuration(ANIMATION_DURATION);
            zoomAnimation_->setEasingCurve(QEasingCurve::OutCirc);
            zoomAnimation_->start();
        }
        else if (swipeNext())
            emit nextRequested();
        else if (swipePrevious())
            emit previousRequested();
        else if (imageOutOfLimits())
        {
            moveImageInsideLimits();
        }
        else if (lastPanTouchs_.isFull())
        {
            // Pan inertia
            int msecsFromLast = lastPanTouchs_.last().time.msecsTo(
                        QTime::currentTime());

            if (msecsFromLast < MAX_INERTIA_INTERVAL)
            {
                QPointF sumPanDelta =
                        lastPanTouchs_.first().posDelta +
                        lastPanTouchs_.at(
                            lastPanTouchs_.firstIndex() + 1).posDelta +
                        lastPanTouchs_.at(
                            lastPanTouchs_.firstIndex() + 2).posDelta +
                        lastPanTouchs_.last().posDelta;
                QPointF averagePanDelta(sumPanDelta / 4.0);
                int elapsedMsecs = lastPanTouchs_.first().time.msecsTo(
                            QTime::currentTime());
                QPointF panInertia(averagePanDelta /
                                   (scaleFactor_ * elapsedMsecs));

                panAnimation_->setStartValue(centerOffset_);
                panAnimation_->setEndValue(centerOffset_ +
                                           panInertia * INERTIA_LENGTH_MSECS);
                panAnimation_->setDuration(ANIMATION_DURATION);
                panAnimation_->setEasingCurve(QEasingCurve::OutCirc);
                panAnimation_->start();

                qDebug() << "panInertia:" << panInertia << "inertia length:" <<
                            panInertia * INERTIA_LENGTH_MSECS;
            }
        }

        lastPanTouchs_.clear();
        tapInProgress_ = false;
        panInProgress_ = false;
        pinchInProgress_ = false;
        swipeInProgress_ = false;
    }

}

}

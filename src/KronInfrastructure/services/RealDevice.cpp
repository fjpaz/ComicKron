/*********************************************************************
 * Copyright (C) 2016 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/
#include "RealDevice.h"

#include <QDebug>
#include <QGuiApplication>
#include <QScreen>
#include <QtGlobal>
#include <QtGui/private/qhighdpiscaling_p.h>
#include <QtMath>
#include <QWindow>

#if defined(Q_OS_ANDROID)
#include <QAndroidJniObject>
#include <QtAndroid>
#endif

namespace kron {

RealDevice::RealDevice()
    : window_(nullptr),
      dpi_(qRound(qApp->primaryScreen()->physicalDotsPerInch() *
                  qApp->primaryScreen()->devicePixelRatio())),
      buckets_({{DensityBucket::LDPI, static_cast<int>(DensityBucket::LDPI)},
                {DensityBucket::MDPI, static_cast<int>(DensityBucket::MDPI)},
                {DensityBucket::TVDPI, static_cast<int>(DensityBucket::TVDPI)},
                {DensityBucket::HDPI, static_cast<int>(DensityBucket::HDPI)},
                {DensityBucket::XHDPI, static_cast<int>(DensityBucket::XHDPI)},
                {DensityBucket::XXHDPI, static_cast<int>(DensityBucket::XXHDPI)},
                {DensityBucket::XXXHDPI, static_cast<int>(DensityBucket::XXXHDPI)}})
{
#if defined(Q_OS_ANDROID)
    // Use DPI reported by Android
    QAndroidJniObject qtActivity =
            QAndroidJniObject::callStaticObjectMethod(
                "org/qtproject/qt5/android/QtNative",
                "activity", "()Landroid/app/Activity;");
    QAndroidJniObject resources =
            qtActivity.callObjectMethod("getResources",
                                        "()Landroid/content/res/Resources;");
    QAndroidJniObject displayMetrics =
            resources.callObjectMethod("getDisplayMetrics",
                                       "()Landroid/util/DisplayMetrics;");
    dpi_ = displayMetrics.getField<int>("densityDpi");
#elif defined(Q_OS_WIN) || defined(Q_OS_OSX)
    dpi_ = qRound(qApp->primaryScreen()->logicalDotsPerInch() *
                  qApp->primaryScreen()->devicePixelRatio());
#endif

    // Initialize distance to a value much greater than any expected
    int nearestDistance = 100000;

    foreach (int bucket, buckets_.values())
    {
        int distanceToBucket = qAbs(dpi_ - bucket);

        if (distanceToBucket < nearestDistance)
        {
            nearestDistance = distanceToBucket;
            bucket_ = buckets_.key(bucket);
        }
    }

    scaleFactor_ = buckets_.value(bucket_) /
            buckets_.value(DensityBucket::MDPI);

    qDebug() << "DPI:" << dpi_ <<
                "Density bucket:" << bucket_ <<
                "Scale factor:" << scaleFactor_;
}

RealDevice::~RealDevice()
{
}

qreal RealDevice::scaleFactor() const
{
    return QHighDpiScaling::factor(window_);
}

void RealDevice::setScaleFactor(qreal scaleFactor)
{
    qDebug() << "Set scale factor:" << scaleFactor;

    QHighDpiScaling::setScreenFactor(window_->screen(), scaleFactor);
    QHighDpiScaling::updateHighDpiScaling();

    emit scaleFactorChanged(scaleFactor);
}

int RealDevice::dp(int dp) const
{
    return qRound(dp * scaleFactor_);
}

int RealDevice::sp(int sp) const
{
    // TODO: Multiply by system font scale factor
    return qRound(sp * scaleFactor_);
}

void RealDevice::onWindowSizeChanged()
{
    if (LAYOUT_AUTO == layoutMode())
    {
        Layout oldLayout = layout_;

        calculateLayout();

        if (oldLayout != layout_)
        {
            emit layoutChanged(layout_);
        }
    }
}

void RealDevice::setWindow(QWindow* window)
{
    window_ = window;

    calculateLayout();

    connect(window_, SIGNAL(widthChanged(int)),
            this, SLOT(onWindowSizeChanged()));
    connect(window_, SIGNAL(heightChanged(int)),
            this, SLOT(onWindowSizeChanged()));
}

qreal RealDevice::calculateDiagonal()
{
    qreal diagonal = 0;
    qreal width = 0;
    qreal height = 0;
    QSizeF screenSize = window_->screen()->physicalSize();

    qDebug() << "Device Pixel Ratio:" << window_->screen()->devicePixelRatio() <<
                "Logical / Physical DPI:" << qApp->primaryScreen()->logicalDotsPerInch() <<
                "/" << qApp->primaryScreen()->physicalDotsPerInch();

    if (window_->visibility() == QWindow::FullScreen)
    {
        width = screenSize.width();
        height = screenSize.height();

        qDebug() << "Screen size:" << window_->screen()->size().width() <<
                    "x" << window_->screen()->size().height() << "pixels";
    }
    else
    {
        qreal screenWidth = window_->screen()->size().width() *
                qRound(window_->screen()->devicePixelRatio());
        qreal screenHeight = window_->screen()->size().height() *
                qRound(window_->screen()->devicePixelRatio());
        width = window_->width() * screenSize.width() / screenWidth;
        height = window_->height() * screenSize.height() / screenHeight;

        qDebug() << "Window size:" << window_->width() <<
                    "x" << window_->height() << "pixels";
    }


    diagonal = sqrt(qPow((width), 2) +
                    qPow((height), 2)) * mmToInches();

    return diagonal;
}

void RealDevice::calculateLayout()
{
    qreal diagonal = calculateDiagonal();
    int widthDP = pixelsToDp(window_->width());
    int heightDP = pixelsToDp(window_->height());

    if (diagonal >= 32)
    {
        layout_ = TV;
    }
    else if (widthDP < 600)
    {
        layout_ = SMALL;
    }
    else if (widthDP >= 600 && widthDP < 1280)
    {
        layout_ = MEDIUM;
    }
    else if (widthDP >= 1280)
    {
        layout_ = LARGE;
    }

    qDebug() << "Layout:" << layout_ <<
                "window size:" << widthDP << "x" << heightDP << "dp" <<
                "diagonal:" << diagonal << "inches";
}

qreal RealDevice::mmToInches() const
{
    return 0.0393701;
}

int RealDevice::pixelsToDp(int pixels) const
{
    return qRound(pixels / scaleFactor_);
}

}

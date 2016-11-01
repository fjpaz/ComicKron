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

int RealDevice::dp(int dp) const
{
    return qRound(dp * scaleFactor_);
}

int RealDevice::sp(int sp) const
{
    // TODO: Multiply by system font scale factor
    return qRound(sp * scaleFactor_);
}

Device::FormFactor RealDevice::formFactor() const
{
    return formFactor_;
}

void RealDevice::windowSizeChanged()
{
    FormFactor oldFormFactor = formFactor_;

    calculateFormFactor();

    if (oldFormFactor != formFactor_)
    {
        emit formFactorChanged(formFactor_);
    }
}

void RealDevice::setWindow(QWindow* window)
{
    window_ = window;

    calculateFormFactor();

    connect(window_, SIGNAL(widthChanged(int)),
            this, SLOT(windowSizeChanged()));
    connect(window_, SIGNAL(heightChanged(int)),
            this, SLOT(windowSizeChanged()));
}

qreal RealDevice::calculateDiagonal()
{
    qreal diagonal = 0;
    qreal width = 0;
    qreal height = 0;
    QSizeF screenSize = window_->screen()->physicalSize();

    if (window_->visibility() == QWindow::FullScreen)
    {
        width = screenSize.width();
        height = screenSize.height();

        qDebug() << "Screen size:" << window_->screen()->size().width() <<
                    "x" << window_->screen()->size().height();
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
                    "x" << window_->height();
    }


    diagonal = sqrt(qPow((width), 2) +
                    qPow((height), 2)) * mmToInches();

    return diagonal;
}

void RealDevice::calculateFormFactor()
{
    qreal diagonal = calculateDiagonal();

    if (diagonal < 6.5)
    {
        formFactor_ = FormFactor::Smartphone;
    }
    else if (diagonal >= 6.5 && diagonal < 10.1)
    {
        formFactor_ = FormFactor::Tablet;
    }
    else if (diagonal >= 10.1 && diagonal < 29)
    {
        formFactor_ = FormFactor::Desktop;
    }
    else if (diagonal >= 29)
    {
        formFactor_ = FormFactor::TV;
    }

    qDebug() << "Form factor:" << formFactor_;
}

qreal RealDevice::mmToInches() const
{
    return 0.0393701;
}

}

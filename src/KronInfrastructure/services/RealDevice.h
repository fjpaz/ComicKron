/*********************************************************************
 * Copyright (C) 2016 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/
#ifndef KRON_REALDEVICE_H
#define KRON_REALDEVICE_H

#include "../KronInfrastructureExport.h"

#include <KronCore/services/Device.h>

#include <QMap>

class QWindow;

namespace kron {

class KRONINFRASTRUCTURE_EXPORT RealDevice : public Device
{
    Q_OBJECT
public:
    enum class DensityBucket
    {
        LDPI = 120,
        MDPI = 160,
        TVDPI = 213,
        HDPI = 240,
        XHDPI = 320,
        XXHDPI = 480,
        XXXHDPI = 640
    };
    Q_ENUM(DensityBucket)

    RealDevice();

    virtual ~RealDevice();

    virtual qreal scaleFactor() const override;

    virtual void setScaleFactor(qreal scaleFactor) override;

    virtual int dp(int dp) const override;

    virtual int sp(int sp) const override;

public slots:
    void onWindowSizeChanged();

    virtual void setWindow(QWindow* window) override;

private:
    qreal calculateDiagonal();

    void calculateLayout();

    qreal mmToInches() const;

    int pixelsToDp(int pixels) const;

    QWindow* window_;
    int dpi_;
    DensityBucket bucket_;
    QMap<DensityBucket, int> buckets_;
    qreal scaleFactor_;
};

}

#endif // KRON_REALDEVICE_H

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

    virtual int dp(int dp) const override;

    virtual int sp(int sp) const override;

    virtual FormFactor formFactor() const override;

public slots:
    void windowSizeChanged();

    virtual void setWindow(QWindow* window) override;

private:
    qreal calculateDiagonal();

    void calculateFormFactor();

    qreal mmToInches() const;

    QWindow* window_;
    int dpi_;
    DensityBucket bucket_;
    qreal scaleFactor_;
    FormFactor formFactor_;
};

}

#endif // KRON_REALDEVICE_H

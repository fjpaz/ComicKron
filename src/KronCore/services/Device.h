/*********************************************************************
 * Copyright (C) 2016 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/
#ifndef KRON_DEVICE_H
#define KRON_DEVICE_H

#include "../KronCoreExport.h"

#include <QObject>

class QWindow;

namespace kron {

class KRONCORE_EXPORT Device : public QObject
{
    Q_OBJECT

public:
    enum class FormFactor
    {
        Smartphone,
        Tablet,
        Desktop,
        TV
    };
    Q_ENUM(FormFactor)

    virtual ~Device() = default;

    Q_INVOKABLE virtual int dp(int dp) const = 0;

    Q_INVOKABLE virtual int sp(int sp) const = 0;

    Q_INVOKABLE virtual FormFactor formFactor() const = 0;

    Q_INVOKABLE virtual void setWindow(QWindow* window) = 0;

signals:
    void formFactorChanged(FormFactor formFactor);
};

}

#endif // KRON_DEVICE_H

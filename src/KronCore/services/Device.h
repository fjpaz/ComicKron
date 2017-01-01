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
    enum Layout
    {
        SMALL,
        MEDIUM,
        LARGE,
        TV
    };
    Q_ENUM(Layout)

    enum LayoutMode
    {
        LAYOUT_AUTO,
        LAYOUT_MANUAL
    };
    Q_ENUM(LayoutMode)

    Q_PROPERTY(Layout layout READ layout WRITE setLayout NOTIFY layoutChanged)
    Q_PROPERTY(LayoutMode layoutMode READ layoutMode NOTIFY layoutModeChanged)

    Device() : layout_(SMALL), layoutMode_(LAYOUT_AUTO) {}

    virtual ~Device() = default;

    Q_INVOKABLE Layout layout()
    {
        return layout_;
    }

    Q_INVOKABLE void setLayout(Layout layout)
    {
        if (layout != layout_)
        {
            layout_ = layout;

            emit layoutChanged(layout);

            if (layoutMode_ != LAYOUT_MANUAL)
            {
                layoutMode_ = LAYOUT_MANUAL;

                emit layoutModeChanged(LAYOUT_MANUAL);
            }
        }
    }

    Q_INVOKABLE LayoutMode layoutMode() const
    {
        return layoutMode_;
    }

    Q_INVOKABLE void setAutoLayout()
    {
        if (layoutMode_ != LAYOUT_AUTO)
        {
            layoutMode_ = LAYOUT_AUTO;

            emit layoutModeChanged(LAYOUT_AUTO);
        }
    }

    Q_INVOKABLE virtual int dp(int dp) const = 0;

    Q_INVOKABLE virtual int sp(int sp) const = 0;

    Q_INVOKABLE virtual void setWindow(QWindow* window) = 0;

signals:
    void layoutChanged(Layout layout);

    void layoutModeChanged(LayoutMode layoutMode);

protected:
    Layout layout_;
    LayoutMode layoutMode_;
};

}

#endif // KRON_DEVICE_H

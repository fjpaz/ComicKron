/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#include "SignalSpy.h"

#include <QList>

#include <stdexcept>

namespace kron {

bool SignalSpy::signalReceived(int timeout)
{
    return !empty() || wait(timeout);
}

QVariant SignalSpy::firstParameter() const
{
    if (empty())
        throw std::out_of_range("No signal received");

    QList<QVariant> firstSignal = first();

    if (firstSignal.empty())
        throw std::out_of_range("Signal has no parameter");

    return firstSignal.first();
}

QVariant SignalSpy::secondParameter() const
{
    if (empty())
        throw std::out_of_range("No signal received");

    QList<QVariant> firstSignal = first();

    if (firstSignal.count() < 2)
        throw std::out_of_range("Signal doesn't have second parameter");

    return firstSignal.at(1);
}

QVariant SignalSpy::parameter(int position) const
{
    if (empty())
        throw std::out_of_range("No signal received");

    QList<QVariant> firstSignal = first();

    if (firstSignal.count() <= position)
        throw std::out_of_range("Signal doesn't have parameter " + std::to_string(position));

    return firstSignal.at(position - 1);
}

}
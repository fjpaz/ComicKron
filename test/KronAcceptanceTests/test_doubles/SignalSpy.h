/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef SIGNALSPY_H
#define SIGNALSPY_H

#include <QSignalSpy>
#include <QVariant>

namespace kron {

/**
 * @brief Spy for signals emitted synchronously or asynchronously.
 *
 * This class it's an extension of QSignalSpy class with useful methods
 * for testing.
 */
class SignalSpy : public QSignalSpy
{
public:
    using QSignalSpy::QSignalSpy;

    /**
     * @brief Wait for a signal if one has not been emitted previously.
     * @param timeout Maximum number of milliseconds to wait for a signal.
     * @return True if a signal has been emitted.
     */
    bool signalReceived(int timeout = 5000);

    /**
     * @brief Returns first parameter of first signal received.
     * @return First parameter of first signal received.
     */
    QVariant firstParameter() const;

    /**
     * @brief Returns second parameter of first signal received.
     * @return Second parameter of first signal received.
     */
    QVariant secondParameter() const;

    /**
     * @brief Returns parameter n of first signal received.
     * @param position Position of parameter. First parameter is 1.
     * @return Parameter n of first signal received.
     */
    QVariant parameter(int position) const;
};

}

#endif // SIGNALSPY_H

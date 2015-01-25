/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#include "SignalHandler.h"

#include <QCoreApplication>
#include <QDebug>
#include <QtGlobal>

#ifdef Q_OS_UNIX
#include <csignal>
#endif

namespace kron {

void SignalHandler::handleSignals()
{
#ifdef Q_OS_UNIX
    signal(SIGHUP, cleanExitSignalHandler);
    signal(SIGINT, cleanExitSignalHandler);
    signal(SIGPIPE, cleanExitSignalHandler);
    signal(SIGTERM, cleanExitSignalHandler);
    signal(SIGSTOP, cleanExitSignalHandler);

    signal(SIGQUIT, resendSignalHandler);
    signal(SIGILL, resendSignalHandler);
    signal(SIGABRT, resendSignalHandler);
    signal(SIGFPE, resendSignalHandler);
    signal(SIGSEGV, resendSignalHandler);
    signal(SIGBUS, resendSignalHandler);
#endif
}

void SignalHandler::cleanExitSignalHandler(int signum)
{
#ifdef Q_OS_UNIX
    qDebug() << "Signal" << signum << "captured. Exiting...";

    signal(signum, SIG_DFL);

    QCoreApplication::exit(signum);
#else
    Q_UNUSED(signum)
#endif
}

void SignalHandler::resendSignalHandler(int signum)
{
#ifdef Q_OS_UNIX
    qDebug() << "Signal" << signum << "captured. Resending signal...";

    signal(signum, SIG_DFL);

    raise(signum);
#else
    Q_UNUSED(signum)
#endif
}

}

/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef KRONUIEXPORT_H
#define KRONUIEXPORT_H

#include <QtCore/qglobal.h>

#if defined(KRONUI_LIBRARY)
#  define KRONUI_EXPORT Q_DECL_EXPORT
#else
#  define KRONUI_EXPORT Q_DECL_IMPORT
#endif

#endif // KRONUIEXPORT_H

/*********************************************************************
 * Copyright (C) 2014 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef kronapplication_global_H
#define kronapplication_global_H

#include <QtCore/qglobal.h>

#if defined(KRONAPPLICATION_LIBRARY)
#  define KRONAPPLICATIONSHARED_EXPORT Q_DECL_EXPORT
#else
#  define KRONAPPLICATIONSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // kronapplication_global_H

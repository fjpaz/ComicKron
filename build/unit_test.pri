#********************************************************************
# Copyright (C) 2014 Francisco Javier Paz Menendez
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#********************************************************************

# This file must be included only in Unit Test projects. A Unit Test must be:
# - Automatic
# - Repeatable
# - Independent
# - Fast (not dependant on slow infraestructure services like DB, network or files)

include(test.pri)

CONFIG += console

unit_test.commands = $$DESTDIR/$$TARGET

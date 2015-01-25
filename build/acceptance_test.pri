#********************************************************************
# Copyright (C) 2014 Francisco Javier Paz Menendez
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#********************************************************************

# This file must be included only in Acceptance Test projects.
# An Acceptance Test must test use cases at ViewModel level. It shouldn't use UI.

include(test.pri)

CONFIG += console

acceptance_test.commands = $$DESTDIR/$$TARGET

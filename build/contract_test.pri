#********************************************************************
# Copyright (C) 2015 Francisco Javier Paz Menendez
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#********************************************************************

# This file must be included only in Contract Test projects.
# A Contract Test must be a parametrized test that tests an interface and must be
# instantiated with each implementation of that interface as paremeter.

include(test.pri)

CONFIG += console

contract_test.commands = $$DESTDIR/$$TARGET

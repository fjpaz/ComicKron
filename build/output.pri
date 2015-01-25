#********************************************************************
# Copyright (C) 2015 Francisco Javier Paz Menendez
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#********************************************************************

# Custom targets. Targets for specific subprojects have command defined in specific .pri file
output.depends = all
output.commands = $$QMAKE_COPY_FILE $$shell_path($$PWD/../test/data/*) $$shell_path($$TESTDIR)

QMAKE_EXTRA_TARGETS += output

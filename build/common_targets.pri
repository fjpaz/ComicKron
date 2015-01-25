#********************************************************************
# Copyright (C) 2015 Francisco Javier Paz Menendez
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#********************************************************************

# Custom targets. Targets for specific subprojects have command defined in specific .pri file
unit_test.CONFIG = recursive
unit_test.depends = all

acceptance_test.CONFIG = recursive
acceptance_test.depends = all

contract_test.CONFIG = recursive
contract_test.depends = all

QMAKE_EXTRA_TARGETS += \
    unit_test \
    acceptance_test \
    contract_test

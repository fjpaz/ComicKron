#********************************************************************
# Copyright (C) 2014 Francisco Javier Paz Menendez
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#********************************************************************

# Get list of library subprojects
for(SUBPROJECT, SUBDIRS) {
    # Subproject .pro file path
    SUBPROJECT_SUBDIR = $$find($${SUBPROJECT}.subdir, .*)
    SUBPROJECT_PRO = $$SUBPROJECT_SUBDIR/$${SUBPROJECT}.pro

    # Subproject type
    SUBPROJECT_TEMPLATE = $$fromfile($$SUBPROJECT_PRO, TEMPLATE)

    contains(SUBPROJECT_TEMPLATE, lib) {
        # Library subproject. Insert target in targets list and target:subproject list
        SUBPROJECT_TARGET = $$fromfile($$SUBPROJECT_PRO, TARGET)

        LIB_TARGETS += $$SUBPROJECT_TARGET
        TARGET_TO_SUBPROJECT += $$SUBPROJECT_TARGET:$$SUBPROJECT
    }
}

# Generate dependencies by matching linked libraries with targets list
for(SUBPROJECT, SUBDIRS) {
    # Skip subprojects with manually generated dependencies
    !isEmpty($${SUBPROJECT}.depends): next()

    # Subproject .pro file path
    SUBPROJECT_SUBDIR = $$find($${SUBPROJECT}.subdir, .*)
    SUBPROJECT_PRO = $$SUBPROJECT_SUBDIR/$${SUBPROJECT}.pro

    # Linked libraries list
    SUBPROJECT_LIBS_RAW = $$fromfile($$SUBPROJECT_PRO, LIBS)
    SUBPROJECT_LIBS_LINK = $$find(SUBPROJECT_LIBS_RAW, ^-l)
    SUBPROJECT_LIBS_TARGET = $$replace(SUBPROJECT_LIBS_LINK, '-l', '')
    SUBPROJECT_LIBS = $$unique(SUBPROJECT_LIBS_TARGET)

    # Clear dependencies list
    SUBPROJECT_DEPENDS =

    # Insert linked libraries found in targets list into dependencies list
    for(LIB_TO_LINK, SUBPROJECT_LIBS) {
        contains(LIB_TARGETS, $$LIB_TO_LINK) {
            TARGET_AND_SUBPROJECT = $$find(TARGET_TO_SUBPROJECT, $$LIB_TO_LINK)
            SUBPROJECT_DEPEND = $$replace(TARGET_AND_SUBPROJECT, $$LIB_TO_LINK:, '')
            SUBPROJECT_DEPENDS += $$SUBPROJECT_DEPEND
        }
    }

    # Declare subproject dependencies
    SUBPROJECT_DEPENDS_VAR = $$join(SUBPROJECT,,,'.depends')
    $$SUBPROJECT_DEPENDS_VAR = $$SUBPROJECT_DEPENDS
}

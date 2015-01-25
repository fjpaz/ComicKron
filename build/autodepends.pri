#********************************************************************
# Copyright (C) 2014 Francisco Javier Paz Menendez
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#********************************************************************

# Get subproject .pro file path
defineReplace(subprojectPro) {
    subproject = $$1
    subproject_subdir = $$find($${subproject}.subdir, .*)
    subproject_pro_path = $$subproject_subdir/$${subproject}.pro

    return($$subproject_pro_path)
}

# Test if subproject is a library
defineTest(isLibrary) {
    subproject = $$1
    subproject_pro_path = $$subprojectPro($$subproject)
    subproject_template = $$fromfile(../$$subproject_pro_path, TEMPLATE)

    contains(subproject_template, lib) {
        return(true)
    } else {
        return(false)
    }
}

# Get linked libraries list
defineReplace(linkedLibraries) {
    subproject = $$1
    subproject_pro_path = $$subprojectPro($$subproject)
    subproject_libs_raw = $$fromfile(../$$subproject_pro_path, LIBS)
    subproject_libs_link = $$find(subproject_libs_raw, ^-l)
    subproject_libs_target = $$replace(subproject_libs_link, '-l', '')
    subproject_libs = $$unique(subproject_libs_target)

    return($$subproject_libs)
}

# Get subproject dependencies
defineReplace(subprojectDepends) {
    subproject = $$1
    linked_libraries = $$linkedLibraries($$subproject)

    # Insert linked libraries found in targets list into dependencies list
    for(lib_to_link, linked_libraries) {
        contains(LIB_TARGETS, $$lib_to_link) {
            target_and_subproject = $$find(TARGET_TO_SUBPROJECT, $$lib_to_link)
            subproject_depend = $$replace(target_and_subproject, $$lib_to_link:, '')
            subproject_depends += $$subproject_depend
        }
    }

    return($$subproject_depends)
}

# Test if a project has manually defined dependencies
defineTest(hasDefinedDepends) {
    subproject = $$1

    isEmpty($${subproject}.depends) {
        return(false)
    } else {
        return(true)
    }
}

# GENERATE DEPENDENCIES
# ---------------------

# Get list of library subprojects
for(SUBPROJECT, SUBDIRS) {
    isLibrary($$SUBPROJECT) {
        # Insert target in targets list and target:subproject list
        subproject_pro_path = $$subprojectPro($$SUBPROJECT)
        SUBPROJECT_TARGET = $$fromfile(../$$subproject_pro_path, TARGET)
        LIB_TARGETS += $$SUBPROJECT_TARGET
        TARGET_TO_SUBPROJECT += $$SUBPROJECT_TARGET:$$SUBPROJECT
    }
}

# Generate dependencies by matching linked libraries with targets list
for(SUBPROJECT, SUBDIRS) {
    # Skip subprojects with manually defined dependencies
    hasDefinedDepends($$SUBPROJECT): next()

    SUBPROJECT_DEPENDS = $$subprojectDepends($$SUBPROJECT)

    # Define subproject dependencies
    SUBPROJECT_DEPENDS_VAR = $$join(SUBPROJECT,,,'.depends')
    $$SUBPROJECT_DEPENDS_VAR = $$SUBPROJECT_DEPENDS
}

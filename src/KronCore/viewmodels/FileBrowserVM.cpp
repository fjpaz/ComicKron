/*********************************************************************
 * Copyright (C) 2016 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#include "FileBrowserVM.h"

#include <QDir>
#include <QStandardPaths>

namespace kron {

FileBrowserVM::FileBrowserVM(QObject *parent)
    : QObject(parent),
      dir_(new QDir(QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation)))
{
    qRegisterMetaType<Item>("FileBrowserItem");
}

FileBrowserVM::~FileBrowserVM()
{
    qDeleteAll(items_);
}

void FileBrowserVM::navigateToFolder(QString folder)
{
    Q_UNUSED(folder)
    // TODO: Replace current items by folder items
}

QList<FileBrowserVM::Item *> FileBrowserVM::currentItems() const
{
    return items_;
}

}

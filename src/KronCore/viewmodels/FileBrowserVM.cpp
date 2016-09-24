/*********************************************************************
 * Copyright (C) 2016 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#include "FileBrowserVM.h"

#include <QDebug>
#include <QDir>
#include <QtQml/QQmlEngine>
#include <QStandardPaths>
#include <QUrl>

namespace kron {

FileBrowserVM::FileBrowserVM(QObject *parent)
    : QObject(parent),
      dir_(new QDir(QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation)))
{
    qmlRegisterUncreatableType<FsItem>(
                "ComicKron.FsItem", 1, 0, "FsItem",
                "You cannot create an instance of the FsItem");
    fillItems();
}

FileBrowserVM::~FileBrowserVM()
{
    qDeleteAll(items_);
}

void FileBrowserVM::navigateToFolder(QString folder)
{
    dir_->cd(folder);

    fillItems();
}

void FileBrowserVM::openFile(QString file)
{
    QUrl fileUrl = QUrl::fromLocalFile(dir_->absoluteFilePath(file));
    QString urlString = fileUrl.url();

    qDebug() << "Opening file with URL" << urlString;

    emit fileOpened(urlString);
}

void FileBrowserVM::fillItems()
{
    // Clear old items
    qDeleteAll(items_);
    items_.clear();

    // Fill with items of current directory
    foreach (const QFileInfo& fileInfo, dir_->entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDot, QDir::DirsFirst))
    {
        FsItem* item = new FsItem;
        item->type = fileInfo.isFile() ? FsItem::Type::FILE : FsItem::Type::FOLDER;
        item->name = fileInfo.fileName();
        items_.append(item);

        qDebug() << "Item type:" << item->type << "| name:" << item->name;
    }

    emit itemsChanged(items_);
}

}

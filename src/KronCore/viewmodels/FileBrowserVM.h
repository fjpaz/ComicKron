/*********************************************************************
 * Copyright (C) 2016 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef KRON_FILEBROWSERVM_H
#define KRON_FILEBROWSERVM_H

#include "../KronCoreExport.h"

#include <memory>
#include <QList>
#include <QObject>
#include <QString>

class QDir;

namespace kron {

class KRONCORE_EXPORT FsItem : public QObject
{
    Q_OBJECT
public:
    enum Type
    {
        FILE,
        FOLDER
    };
    Q_ENUM(Type)

    Q_PROPERTY(Type type MEMBER type NOTIFY typeChanged)
    Q_PROPERTY(QString name MEMBER name NOTIFY nameChanged)

    Type type;
    QString name;

signals:
    void typeChanged(Type type);
    void nameChanged(QString name);
};

class KRONCORE_EXPORT FileBrowserVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QObject*> items MEMBER items_ NOTIFY itemsChanged)
public:
    explicit FileBrowserVM(QObject *parent = 0);

    virtual ~FileBrowserVM();

signals:
    void itemsChanged(QList<QObject*> items);

    void fileOpened(QString fileUrl);

public slots:
    void navigateToFolder(QString folder);

    void openFile(QString file);

private:
    void fillItems();

    std::unique_ptr<QDir> dir_;
    QList<QObject*> items_;
};

}

#endif // KRON_FILEBROWSERVM_H

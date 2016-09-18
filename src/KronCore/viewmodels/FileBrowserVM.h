/*********************************************************************
 * Copyright (C) 2016 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef KRON_FILEBROWSERVM_H
#define KRON_FILEBROWSERVM_H

#include <memory>
#include <QList>
#include <QObject>

class QDir;

namespace kron {

class FileBrowserVM : public QObject
{
    Q_OBJECT
public:
    enum class Type
    {
        FILE,
        FOLDER
    };
    Q_ENUM(Type)

    struct Item
    {
        Type type;
        QString name;
    };

    explicit FileBrowserVM(QObject *parent = 0);

    virtual ~FileBrowserVM();

signals:
    void itemsChanged(QList<Item*> items);

public slots:
    void navigateToFolder(QString folder);

    QList<Item*> currentItems() const;

private:
    std::unique_ptr<QDir> dir_;
    QList<Item*> items_;
};

}

#endif // KRON_FILEBROWSERVM_H

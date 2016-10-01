/*********************************************************************
 * Copyright (C) 2014 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef KRON_COMICREADERVM_H
#define KRON_COMICREADERVM_H

#include "../KronCoreExport.h"

#include <memory>
#include <QByteArray>
#include <QObject>
#include <QVariant>

namespace kron {

class ComicArchiveReader;

class KRONCORE_EXPORT ComicReaderVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariant page READ page NOTIFY pageChanged)
public:
    ComicReaderVM(std::unique_ptr<ComicArchiveReader> archiveReader);

    virtual ~ComicReaderVM();

    Q_INVOKABLE QVariant page() const;

signals:
    void pageChanged(QVariant currentPage);

public slots:
    void goForward();

    void goBackward();

    void goToFirstPage();

    void openComic(QString comicPath);

private:
    void updateCurrentPage(QByteArray page);

    std::unique_ptr<ComicArchiveReader> archiveReader_;
    QByteArray currentPage_;
};

}

#endif // KRON_COMICREADERVM_H

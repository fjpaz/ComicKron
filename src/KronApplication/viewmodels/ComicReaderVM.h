/*********************************************************************
 * Copyright (C) 2014 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef COMICREADERVM_H
#define COMICREADERVM_H

#include "../KronApplicationExport.h"

#include <QByteArray>
#include <QObject>

namespace kron {

class ComicArchiveReader;
class ImageContainer;

class KRONAPPLICATION_EXPORT ComicReaderVM : public QObject
{
    Q_OBJECT
public:
    ComicReaderVM(ComicArchiveReader& archiveReader,
                  ImageContainer& imageContainer);

    virtual ~ComicReaderVM();

signals:
    void pageUpdated(QByteArray currentPage);

public slots:
    void goForward();

    void goBackward();

    void goToFirstPage();

    void openComic(QString comicPath);

private:
    void updateCurrentPage(QByteArray page);

    ComicArchiveReader& archiveReader_;
    ImageContainer& imageContainer_;
    QByteArray currentPage_;
};

}

#endif // COMICREADERVM_H

/*********************************************************************
 * Copyright (C) 2014 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef COMICVIEWERVIEWMODEL_H
#define COMICVIEWERVIEWMODEL_H

#include "kronapplication_global.h"

#include <archive.h>
#include <archive_entry.h>
#include <QObject>
#include <QPixmap>
#include <QVector>

#include <memory>

class ComicImageProvider;
class QFile;
class QPixmap;
class QString;

namespace PoDoFo {
class PdfMemDocument;
class PdfObject;
}

class KRONAPPLICATIONSHARED_EXPORT ComicViewerViewModel : public QObject
{
    Q_OBJECT
public:
    explicit ComicViewerViewModel(ComicImageProvider& provider, QObject* parent = 0);

    virtual ~ComicViewerViewModel();

signals:
    void comicImageChanged();

public slots:
    void nextPage();

    void previuosPage();

    void loadFile(const QString& file);

private:
    ComicImageProvider& provider_;
    std::unique_ptr<QFile> file_;
    std::unique_ptr<QPixmap> pixmap_;
    quint32 fileIndex_;
    char* buffer_;
    struct archive *a_;
    struct archive_entry* entry_;
    std::unique_ptr<PoDoFo::PdfMemDocument> pdfDoc_;
    QVector<PoDoFo::PdfObject*> pdfImages_;
    bool isPdfFile_;
};

#endif // COMICVIEWERVIEWMODEL_H

/*********************************************************************
 * Copyright (C) 2014 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef COMICIMAGEPROVIDER_H
#define COMICIMAGEPROVIDER_H

#include "kronapplication_global.h"

#include <QQuickImageProvider>

#include <memory>

class QPixmap;

class KRONAPPLICATIONSHARED_EXPORT ComicImageProvider : public QQuickImageProvider
{
public:
    ComicImageProvider();

    virtual QPixmap requestPixmap(const QString& id, QSize* size, const QSize& requestedSize);

    void setPixmap(const QPixmap& pixmap);

private:
    std::unique_ptr<QPixmap> pixmap_;
};

#endif // COMICIMAGEPROVIDER_H

/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef PIXMAPIMAGEPROVIDER_H
#define PIXMAPIMAGEPROVIDER_H

#include "../KronUIExport.h"

#include <KronApplication/services/ImageContainer.h>

#include <QHash>
#include <QPixmap>
#include <QQuickImageProvider>

namespace kron {

class KRONUI_EXPORT PixmapImageProvider : public QQuickImageProvider, public ImageContainer
{
public:
    PixmapImageProvider();

    virtual ~PixmapImageProvider();

    virtual QPixmap requestPixmap(const QString& id, QSize* size, const QSize& requestedSize) override;

    void setImage(const QString& id, const QByteArray& raw) override;

private:
    QHash<QString, QPixmap> pixmaps_;
};

}
#endif // PIXMAPIMAGEPROVIDER_H

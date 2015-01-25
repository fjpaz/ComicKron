/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef FAKEIMAGECONTAINER_H
#define FAKEIMAGECONTAINER_H

#include <KronApplication/services/ImageContainer.h>

#include <QtGlobal>

namespace kron {

class FakeImageContainer : public ImageContainer
{
public:
    virtual void setImage(const QString& id, const QByteArray& raw)
    {
        Q_UNUSED(id)
        Q_UNUSED(raw)
    }
};

}

#endif // FAKEIMAGECONTAINER_H


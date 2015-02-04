/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef APPPAGENAVIGATOR_H
#define APPPAGENAVIGATOR_H

#include "../KronApplicationExport.h"
#include "../PageId.h"

#include <QObject>

namespace kron {

class KRONAPPLICATION_EXPORT AppPageNavigator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(PageId page_ READ currentPage WRITE navigateTo NOTIFY currentPageChanged)
    Q_ENUMS(PageId)
public:
    virtual ~AppPageNavigator();

    PageId currentPage() const;

signals:
    void currentPageChanged(PageId page);

public slots:
    void navigateTo(PageId page);

private:
    PageId page_;
};

}

#endif // APPPAGENAVIGATOR_H

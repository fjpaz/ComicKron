/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef APP_H
#define APP_H

#include <QObject>

#include <memory>

namespace kron {

class AppContext;
class AppPageNavigator;

class App : public QObject
{
    Q_OBJECT
public:
    explicit App(std::unique_ptr<AppContext> context);

    virtual ~App();

    void addContextProperty(QString name, std::unique_ptr<QObject> property);

    QObject& contexProperty(QString name) const;

    void run(QString input);

private:
    std::unique_ptr<AppContext> context_;
    std::unique_ptr<AppPageNavigator> navigator_;
};

}

#endif // APP_H

/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#ifndef KRON_TESTDATA_H
#define KRON_TESTDATA_H

#include <QByteArray>

namespace kron {
namespace testdata {

// MD5 hash of test comic pages (Compressed archives)
qulonglong page01Md5Low = 0x936f05c21e494264;
qulonglong page01Md5High = 0xbfa3b24dcf7d07a1;
qulonglong page02Md5Low = 0xe6cc6a42a2cfbd4b;
qulonglong page02Md5High = 0x85d0ba79b0feeb92;
qulonglong page03Md5Low = 0xb9d21763569298dc;
qulonglong page03Md5High = 0x0f2aaffb765cf2fe;
const QByteArray page01Md5 = QByteArray(reinterpret_cast<char*>(&page01Md5Low), 8) +
        QByteArray(reinterpret_cast<char*>(&page01Md5High), 8);
const QByteArray page02Md5 = QByteArray(reinterpret_cast<char*>(&page02Md5Low), 8) +
        QByteArray(reinterpret_cast<char*>(&page02Md5High), 8);
const QByteArray page03Md5 = QByteArray(reinterpret_cast<char*>(&page03Md5Low), 8) +
        QByteArray(reinterpret_cast<char*>(&page03Md5High), 8);

// MD5 hash of test comic pages (Compressed archives)
qulonglong pdfPage01Md5Low = 0x8141ace0e4e07214;
qulonglong pdfPage01Md5High = 0x5b849a2fd80b5e7a;
qulonglong pdfPage02Md5Low = 0x48ebd47934c65726;
qulonglong pdfPage02Md5High = 0x28d54f451956a3f6;
qulonglong pdfPage03Md5Low = 0x6533b9e2ca163c4e;
qulonglong pdfPage03Md5High = 0x0e528af9435ca550;
const QByteArray pdfPage01Md5 = QByteArray(reinterpret_cast<char*>(&pdfPage01Md5Low), 8) +
        QByteArray(reinterpret_cast<char*>(&pdfPage01Md5High), 8);
const QByteArray pdfPage02Md5 = QByteArray(reinterpret_cast<char*>(&pdfPage02Md5Low), 8) +
        QByteArray(reinterpret_cast<char*>(&pdfPage02Md5High), 8);
const QByteArray pdfPage03Md5 = QByteArray(reinterpret_cast<char*>(&pdfPage03Md5Low), 8) +
        QByteArray(reinterpret_cast<char*>(&pdfPage03Md5High), 8);

}
}

#endif // KRON_TESTDATA_H

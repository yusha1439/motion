// Copyright (c) 2009-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "uritests.h"

#include "guiutil.h"
#include "walletmodel.h"

#include <QUrl>

void URITests::uriTests()
{
    SendCoinsRecipient rv;
    QUrl uri;
    uri.setUrl(QString("motion:MTDieJT19g3XeLD7Ek5XwuhEoTJuaLKrGM?req-dontexist="));
    QVERIFY(!GUIUtil::parseMotionURI(uri, &rv));

    uri.setUrl(QString("motion:MTDieJT19g3XeLD7Ek5XwuhEoTJuaLKrGM?dontexist="));
    QVERIFY(GUIUtil::parseMotionURI(uri, &rv));
    QVERIFY(rv.address == QString("MTDieJT19g3XeLD7Ek5XwuhEoTJuaLKrGM"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("motion:MTDieJT19g3XeLD7Ek5XwuhEoTJuaLKrGM?label=Some Example Address"));
    QVERIFY(GUIUtil::parseMotionURI(uri, &rv));
    QVERIFY(rv.address == QString("MTDieJT19g3XeLD7Ek5XwuhEoTJuaLKrGM"));
    QVERIFY(rv.label == QString("Some Example Address"));
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("motion:MTDieJT19g3XeLD7Ek5XwuhEoTJuaLKrGM?amount=0.001"));
    QVERIFY(GUIUtil::parseMotionURI(uri, &rv));
    QVERIFY(rv.address == QString("MTDieJT19g3XeLD7Ek5XwuhEoTJuaLKrGM"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100000);

    uri.setUrl(QString("motion:MTDieJT19g3XeLD7Ek5XwuhEoTJuaLKrGM?amount=1.001"));
    QVERIFY(GUIUtil::parseMotionURI(uri, &rv));
    QVERIFY(rv.address == QString("MTDieJT19g3XeLD7Ek5XwuhEoTJuaLKrGM"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100100000);

    uri.setUrl(QString("motion:MTDieJT19g3XeLD7Ek5XwuhEoTJuaLKrGM?amount=100&label=Some Example"));
    QVERIFY(GUIUtil::parseMotionURI(uri, &rv));
    QVERIFY(rv.address == QString("MTDieJT19g3XeLD7Ek5XwuhEoTJuaLKrGM"));
    QVERIFY(rv.amount == 10000000000LL);
    QVERIFY(rv.label == QString("Some Example"));

    uri.setUrl(QString("motion:MTDieJT19g3XeLD7Ek5XwuhEoTJuaLKrGM?message=Some Example Address"));
    QVERIFY(GUIUtil::parseMotionURI(uri, &rv));
    QVERIFY(rv.address == QString("MTDieJT19g3XeLD7Ek5XwuhEoTJuaLKrGM"));
    QVERIFY(rv.label == QString());

    QVERIFY(GUIUtil::parseMotionURI("motion://MTDieJT19g3XeLD7Ek5XwuhEoTJuaLKrGM?message=Some Example Address", &rv));
    QVERIFY(rv.address == QString("MTDieJT19g3XeLD7Ek5XwuhEoTJuaLKrGM"));
    QVERIFY(rv.label == QString());

    uri.setUrl(QString("motion:MTDieJT19g3XeLD7Ek5XwuhEoTJuaLKrGM?req-message=Some Example Address"));
    QVERIFY(GUIUtil::parseMotionURI(uri, &rv));

    uri.setUrl(QString("motion:MTDieJT19g3XeLD7Ek5XwuhEoTJuaLKrGM?amount=1,000&label=Some Example"));
    QVERIFY(!GUIUtil::parseMotionURI(uri, &rv));

    uri.setUrl(QString("motion:MTDieJT19g3XeLD7Ek5XwuhEoTJuaLKrGM?amount=1,000.0&label=Some Example"));
    QVERIFY(!GUIUtil::parseMotionURI(uri, &rv));

    uri.setUrl(QString("motion:MTDieJT19g3XeLD7Ek5XwuhEoTJuaLKrGM?amount=100&label=Some Example&message=Some Example Message&IS=1"));
    QVERIFY(GUIUtil::parseMotionURI(uri, &rv));
    QVERIFY(rv.address == QString("MTDieJT19g3XeLD7Ek5XwuhEoTJuaLKrGM"));
    QVERIFY(rv.amount == 10000000000LL);
    QVERIFY(rv.label == QString("Some Example"));
    QVERIFY(rv.message == QString("Some Example Message"));
    QVERIFY(rv.fUseInstantSend == 1);

    uri.setUrl(QString("motion:MTDieJT19g3XeLD7Ek5XwuhEoTJuaLKrGM?amount=100&label=Some Example&message=Some Example Message&IS=Something Invalid"));
    QVERIFY(GUIUtil::parseMotionURI(uri, &rv));
    QVERIFY(rv.address == QString("MTDieJT19g3XeLD7Ek5XwuhEoTJuaLKrGM"));
    QVERIFY(rv.amount == 10000000000LL);
    QVERIFY(rv.label == QString("Some Example"));
    QVERIFY(rv.message == QString("Some Example Message"));
    QVERIFY(rv.fUseInstantSend != 1);

    uri.setUrl(QString("motion:MTDieJT19g3XeLD7Ek5XwuhEoTJuaLKrGM?IS=1"));
    QVERIFY(GUIUtil::parseMotionURI(uri, &rv));
    QVERIFY(rv.fUseInstantSend == 1);

    uri.setUrl(QString("motion:MTDieJT19g3XeLD7Ek5XwuhEoTJuaLKrGM?IS=0"));
    QVERIFY(GUIUtil::parseMotionURI(uri, &rv));
    QVERIFY(rv.fUseInstantSend != 1);

    uri.setUrl(QString("motion:MTDieJT19g3XeLD7Ek5XwuhEoTJuaLKrGM"));
    QVERIFY(GUIUtil::parseMotionURI(uri, &rv));
    QVERIFY(rv.fUseInstantSend != 1);
}

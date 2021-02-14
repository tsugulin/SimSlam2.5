//　信号が青になるまで信号待ちの先頭車両を待たせる
#include "AwaitGate.h"
Define_Module(AwaitGate);
#include "GateKeeper.h"

void AwaitGate::initialize()
{
    // 待ち行列の平均長さを計算するクラスを初期化
    queuelen[1].init(simTime(), 100);
    queuelen[2].init(simTime(), 100);

    // Gateリソースのポインタを取得
    cModule *mod1 = gate("res")->getNextGate()->getOwnerModule();
    gkp = check_and_cast<GateKeeper *>(mod1);
}

// 先頭の車を信号待ちにする
void AwaitGate::handleMessage(cMessage *msg)
{
    int k = msg->getKind();     // メッセージの属性から車線の情報を取得
    queuelen[k].set(simTime(), queue[k].getLength());       // 待ち行列平均長さを計算
    queue[k].insert(msg);       // 先頭の車を信号待ちにする
    goForward(k);               // 信号待ちを処理する
}

// 信号待ちをしている車があり，信号が青ならば進める
void AwaitGate::goForward(long k)
{
    Enter_Method("goForward");
    if ( queue[k].getLength() > 0 ) {       // 信号待ちをしている車があるか？
        if (gkp->check(k)) {                // 信号は青か？
            queuelen[k].set(simTime(), queue[k].getLength());               // 待ち行列平均長さを計算
            cMessage *msg = check_and_cast<cMessage *>(queue[k].pop());     // 待ち行列からメッセージを取り出す
            send(msg, "out");                                               // 後工程に送る
        }
    }
}

//　信号の待ち行列の平均長さを表示する
void AwaitGate::finish()
{
    EV << "SIGNAL1 Queue AVG Length: " << queuelen[1].get(simTime()) << endl;
    EV << "SIGNAL2 Queue AVG Length: " << queuelen[2].get(simTime()) << endl;
}


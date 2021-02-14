#include "AwaitResource.h"
Define_Module(AwaitResource);
#include "Resource.h"

void AwaitResource::initialize()
{
    // 待ち行列の平均長さを計算するクラスを初期化
    queuelen[1].init(simTime(), 100);
    queuelen[2].init(simTime(), 100);

    // リソースのポインタを取得
    cModule *mod = gate("res")->getNextGate()->getOwnerModule();
    rsc = check_and_cast<Resource *>(mod);
}

void AwaitResource::handleMessage(cMessage *msg)
{
    int k = msg->getKind();
    queuelen[k].set(simTime(), queue[k].getLength());   // 待ち行列平均長さを計算
    queue[k].insert(msg);       // 待ち行列の最後尾にめメッセージを追加
    goForward(k);               // 待ち行列に溜まっているメッセージを処理する
}

// 待ち行列にメッセージがあれば処理する
void AwaitResource::goForward(long k)
{
    Enter_Method("goForward");
    if (queue[k].getLength() > 0) {
        cMessage *msg = check_and_cast<cMessage *>(queue[k].front());   // 待ち行列の先頭メッセージを取り出す
        if ( rsc->request(k, msg->getId()) ) {                          // リソースを要求
            queuelen[k].set(simTime(), queue[k].getLength());           // 待ち行列平均長さを計算
            queue[k].pop();                                             // 待ち行列からメッセージを取り出す
            send(msg, "out");                                           // 後工程に送る
        }
    }
}

//　ノードの統計情報を表示
void AwaitResource::finish()
{
    EV << "START1 Queue AVG Length: " << queuelen[1].get(simTime()) << endl;
    EV << "START2 Queue AVG Length: " << queuelen[2].get(simTime()) << endl;
}


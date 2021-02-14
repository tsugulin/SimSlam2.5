#include "Assign.h"
Define_Module(Assign);

void Assign::initialize()
{
    kind = par("datakind");   // 1または2
}

void Assign::handleMessage(cMessage *msg)
{
    msg->setKind(kind); // 1または2をセット
    send(msg, "out");
    stats.collect(0);   // 件数をカウント
}

//　処理件数を表示
void Assign::finish()
{
    EV << "Assign" << kind << " jobs Count: " << stats.getCount() << endl;
}


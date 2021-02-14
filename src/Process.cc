// 一度待ち行列に入っていれば２秒かけて信号を通過する
// もし待ち行列に入っていなければ素通りする

#include "Process.h"
Define_Module(Process);

void Process::handleMessage(cMessage *msg)
{
    if ( msg->isSelfMessage() ) {
        simtime_t_cref d = simTime() - msg->getCreationTime();
        EV << "Received " << msg->getName() << ", leadtime: " << d << "sec" << endl;
        stats.collect( d );
        times.record( d );
        send(msg, "out");       // 後工程に送る
    }
    else {
        // 前工程から届いたメッセージの場合
        if (simTime() == msg->getCreationTime())
            scheduleAt(simTime() + 0.0, msg);       // 待ち行列に入っていなければ直ぐに送る
        else
            scheduleAt(simTime() + 2.0, msg);       // 一度STOPしていれば信号通過までに2秒かかる
    }
}

void Process::finish()
{
    EV << "Total jobs Count:              " << stats.getCount() << endl;
    EV << "Total jobs Min leadtime:       " << stats.getMin() << endl;
    EV << "Total jobs Avg leadtime:       " << stats.getMean() << endl;
    EV << "Total jobs Max leadtime:       " << stats.getMax() << endl;
    EV << "Total jobs Standard deviation: " << stats.getStddev() << endl;
}

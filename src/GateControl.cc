#include "GateControl.h"
Define_Module(GateControl);
#include "GateKeeper.h"

void GateControl::initialize()
{
    // 変数の初期化
    std::string param1 = par("action");         // openまたはclose
    std::string param2 = par("gatename");       // signal1またはsignal2
    mode = (param1 == "open") ? true: false;    // 当該ノードが信号を開けるのか閉めるのかをmodeに保管
    kind = (param2 == "signal1") ? 1: 2;        // 当該ノードがどの信号を操作するのかをkindに保管

    // Gateリソースのポインタを取得
    cModule *mod = gate("res")->getNextGate()->getOwnerModule();
    gkp = check_and_cast<GateKeeper *>(mod);
}

// メッセージが届いたら，omnetpp.iniにて指定されたゲート操作（信号の色の変更）を行う
void GateControl::handleMessage(cMessage *msg)
{
    if ( msg->isSelfMessage() ) {
        // アクティビティの処理完了時
        proctime.collect(simTime() - msg->getTimestamp());      // アクティビティの時間を記録
        send(msg, "out");                                       //後工程にメッセージを送る
    }
    else {
        // 前工程から届いたメッセージの場合
        if (mode) gkp->open(kind);  else  gkp->close(kind);     // 指定された信号の色を変更する
        msg->setTimestamp(simTime());                           // アクティビティの開始時間をセット
        scheduleAt(simTime() + par("productionTime"), msg);     // 生産開始
    }
}

//　ノードの統計情報を表示
void GateControl::finish()
{
    EV << "Gate Jobs Count:   " << proctime.getCount() << endl;
    EV << "Gate Utilization:  " << proctime.getSum() / simTime() << endl;
    EV << "Gate AVG ProcTime: " << proctime.getMean() << endl;

    proctime.recordAs("Gate ProcTime");
}


#include "GateKeeper.h"
Define_Module(GateKeeper);
#include "AwaitGate.h"

void GateKeeper::initialize()
{
    // 信号を初期化
    signal[1] = false;  // 信号1は赤
    signal[2] = false;  // 信号2も赤

    // AwaitGateノードのポインタをセット
    cModule *mod = gate("from_await")->getPreviousGate()->getOwnerModule();
    awaitNode = check_and_cast<AwaitGate *>(mod);
}

// ゲートを開ける．信号を青に変える
void GateKeeper::open(long kind)
{
    Enter_Method("open");
    checkpoint[kind] = simTime();   // ゲートが空いた時刻を記録
    signal[kind] = true;            // 信号を青に変える
    awaitNode->goForward(kind);     // 信号待ちの車に知らせる
}

// ゲートを閉める．信号を赤に変える
void GateKeeper::close(long kind)
{
    Enter_Method("close");
    stats[kind].collect( simTime() - checkpoint[kind] );    // ゲートが開いた時間を記録
    signal[kind] = false;           // 信号を赤に変える
}

// ゲートの開閉を確認する．Trueならば青
bool GateKeeper::check(long kind)
{
    Enter_Method("check");
    return signal[kind];
}

// リソース使用状況の表示
void GateKeeper::finish()
{
    EV << "LIGHT1 Utilization: " << stats[1].getSum() / simTime() << endl;
    EV << "LIGHT2 Utilization: " << stats[2].getSum() / simTime() << endl;
}


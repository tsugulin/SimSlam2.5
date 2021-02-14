#ifndef GATEKEEPER_H_
#define GATEKEEPER_H_

#include <omnetpp.h>
using namespace omnetpp;

class AwaitGate;

class GateKeeper : public cSimpleModule {
private:
    bool signal[3];             // 信号の状態を表す
    AwaitGate *awaitNode;       // AwaitGateノードへのポインタ
    simtime_t checkpoint[3];    // ゲートが開いたた時間を記録
    cStdDev stats[3];           // 信号の使用状況を記録

protected:
    virtual void initialize();  // 変数を初期化
    virtual void finish();      //　リソース使用業況を表示

public:
    virtual void open(long kind);   // 信号を青にする
    virtual void close(long kind);  // 信号を赤にする
    virtual bool check(long kind);  // 信号の色を確認する
};

#endif /* GATEKEEPER_H_ */

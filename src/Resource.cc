#include "Resource.h"
Define_Module(Resource);
#include "AwaitResource.h"

void Resource::initialize()
{
    // 変数を初期化
    owner[1] = 0;   // START1を初期化
    owner[2] = 0;   // START2を初期化

    // AwaitノードとGoonノードのポインタを取得
    cModule *mod = gate("from_await")->getPreviousGate()->getOwnerModule();
    awaitNode = check_and_cast<AwaitResource *>(mod);
}

// リソースの獲得を行う
bool Resource::request(long kind, long id)
{
    Enter_Method("request");
    bool ret_code = false;          // 戻り値を初期化
    if ( owner[kind] == 0 ) {
        owner[kind] = id;           // もしリソースが未使用であれば要求者が利用可能とする
        checkpoint[kind] = simTime();     // リソース獲得時刻を記録
        ret_code = true;            // リソース獲得に成功
    }
    return ret_code;    // リソース獲得できればtrueを戻す
}

// リソースの解放を行う
bool Resource::release(long kind, long id)
{
    Enter_Method("release");
    bool ret_code = false;          // 戻り値を初期化
    if ( owner[kind] == id ) {
        owner[kind] = 0;            // リソースを解放
        stats[kind].collect( simTime() - checkpoint[kind] );    // リソース使用時間を記録
        awaitNode->goForward(kind); // 次のメッセージのリソースを確保する
        ret_code = true;            // リソース解放に成功
    }
    return ret_code;    // リソース解放できればtrueを戻す
}

void Resource::finish()
{
    EV << "START1 jobs Count:  " << stats[1].getCount() << endl;
    EV << "START1 Utilization: " << stats[1].getSum() / simTime() << endl;
    EV << "START2 jobs Count:  " << stats[2].getCount() << endl;
    EV << "START2 Utilization: " << stats[2].getSum() / simTime() << endl;
}

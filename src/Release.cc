#include "Release.h"
Define_Module(Release);
#include "Resource.h"

void Release::initialize()
{
    // リソースのポインタを取得
    cModule *mod = gate("res")->getNextGate()->getOwnerModule();
    rsc = check_and_cast<Resource *>(mod);
}

void Release::handleMessage(cMessage *msg)
{
    rsc->release( msg->getKind(), msg->getId() );       // リソースの開放
    delete msg;
}

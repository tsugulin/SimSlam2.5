#ifndef GATECONTROL_H_
#define GATECONTROL_H_

#include <omnetpp.h>
using namespace omnetpp;

class GateKeeper;

class GateControl : public cSimpleModule {
private:
    bool mode;  // ゲートを開ける場合はture
    long kind;  //　ゲートの種類．1または2
    GateKeeper *gkp;
    cStdDev proctime;

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
};

#endif /* GATECONTROL_H_ */

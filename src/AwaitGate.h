#ifndef AWAITGATE_H_
#define AWAITGATE_H_

#include <omnetpp.h>
using namespace omnetpp;
#include "Wavg.h"

class GateKeeper;

class AwaitGate : public cSimpleModule {
private:
  cQueue queue[3];
  Wavg queuelen[3];
  GateKeeper *gkp;

protected:
  virtual void initialize();
  virtual void handleMessage(cMessage *msg);
  virtual void finish();

public:
  virtual void goForward(long k);
};

#endif /* AWAITGATE_H_ */

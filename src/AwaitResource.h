#ifndef AWAITRESOURCE_H_
#define AWAITRESOURCE_H_

#include <omnetpp.h>
using namespace omnetpp;
#include "Wavg.h"

class Resource;

class AwaitResource : public cSimpleModule {
private:
  cQueue queue[3];
  Wavg queuelen[3];
  Resource *rsc;

protected:
  virtual void initialize();
  virtual void handleMessage(cMessage *msg);
  virtual void finish();

public:
  virtual void goForward(long k);
};

#endif /* AWAITRESOURCE_H_ */

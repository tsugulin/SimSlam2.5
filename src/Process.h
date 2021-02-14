#ifndef PROCESS_H_
#define PROCESS_H_

#include <omnetpp.h>
using namespace omnetpp;

class Process : public cSimpleModule {
private:
    cStdDev stats;
    cOutVector times;

protected:
  virtual void handleMessage(cMessage *msg);
  virtual void finish();
};

#endif /* PROCESS_H_ */

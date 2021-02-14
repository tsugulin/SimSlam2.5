#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <omnetpp.h>
using namespace omnetpp;

class AwaitResource;
class AwaitGate;

class Resource : public cSimpleModule {
private:
    long owner[3];
    AwaitResource *awaitNode;
    simtime_t checkpoint[3];
    cStdDev stats[3];

protected:
    virtual void initialize();
    virtual void finish();

public:
    virtual bool request(long kind, long id);
    virtual bool release(long kind, long id);
};

#endif /* RESOURCE_H_ */

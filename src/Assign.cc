#include "Assign.h"
Define_Module(Assign);

void Assign::initialize()
{
    kind = par("datakind");   // 1�܂���2
}

void Assign::handleMessage(cMessage *msg)
{
    msg->setKind(kind); // 1�܂���2���Z�b�g
    send(msg, "out");
    stats.collect(0);   // �������J�E���g
}

//�@����������\��
void Assign::finish()
{
    EV << "Assign" << kind << " jobs Count: " << stats.getCount() << endl;
}


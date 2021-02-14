#include "Create.h"
Define_Module(Create);

void Create::initialize()
{
    beatMsg = new cMessage("beat");
    scheduleAt(simTime() + par("initialTime"), beatMsg);     // �ŏ��̃��b�Z�[�W�𑗐M
}

void Create::handleMessage(cMessage *msg)
{
    // CREATE�m�[�h�ɓ͂����b�Z�[�W�͑S��beatMsg
    ASSERT(msg == beatMsg);

    // ���̃��W���[���Ƀ��b�Z�[�W�𑗐M
    send(new cMessage(par("datatype")), "out");     // product�܂���accident

    //�@intervalTime�̊��Ԗ���"heartbeat"���b�Z�[�W�����g�ɑ��M����
    double d = par("intervalTime");
    leadtime.collect(d);
    scheduleAt(simTime() + d, beatMsg);
}

//�@�m�[�h�̓��v����\��
void Create::finish()
{
    EV << "Create Jobs Count:   " << leadtime.getCount() << endl;
    EV << "Create Min Leadtime: " << leadtime.getMin() << endl;
    EV << "Create Avg Leadtime: " << leadtime.getMean() << endl;
    EV << "Create Max Leadtime: " << leadtime.getMax() << endl;
    EV << "Standard deviation:  " << leadtime.getStddev() << endl;

    leadtime.recordAs("Create LeadTime");
}

// ��x�҂��s��ɓ����Ă���΂Q�b�����ĐM����ʉ߂���
// �����҂��s��ɓ����Ă��Ȃ���Αf�ʂ肷��

#include "Process.h"
Define_Module(Process);

void Process::handleMessage(cMessage *msg)
{
    if ( msg->isSelfMessage() ) {
        simtime_t_cref d = simTime() - msg->getCreationTime();
        EV << "Received " << msg->getName() << ", leadtime: " << d << "sec" << endl;
        stats.collect( d );
        times.record( d );
        send(msg, "out");       // ��H���ɑ���
    }
    else {
        // �O�H������͂������b�Z�[�W�̏ꍇ
        if (simTime() == msg->getCreationTime())
            scheduleAt(simTime() + 0.0, msg);       // �҂��s��ɓ����Ă��Ȃ���Β����ɑ���
        else
            scheduleAt(simTime() + 2.0, msg);       // ��xSTOP���Ă���ΐM���ʉ߂܂ł�2�b������
    }
}

void Process::finish()
{
    EV << "Total jobs Count:              " << stats.getCount() << endl;
    EV << "Total jobs Min leadtime:       " << stats.getMin() << endl;
    EV << "Total jobs Avg leadtime:       " << stats.getMean() << endl;
    EV << "Total jobs Max leadtime:       " << stats.getMax() << endl;
    EV << "Total jobs Standard deviation: " << stats.getStddev() << endl;
}

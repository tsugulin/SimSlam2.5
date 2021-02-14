#include "GateControl.h"
Define_Module(GateControl);
#include "GateKeeper.h"

void GateControl::initialize()
{
    // �ϐ��̏�����
    std::string param1 = par("action");         // open�܂���close
    std::string param2 = par("gatename");       // signal1�܂���signal2
    mode = (param1 == "open") ? true: false;    // ���Y�m�[�h���M�����J����̂��߂�̂���mode�ɕۊ�
    kind = (param2 == "signal1") ? 1: 2;        // ���Y�m�[�h���ǂ̐M���𑀍삷��̂���kind�ɕۊ�

    // Gate���\�[�X�̃|�C���^���擾
    cModule *mod = gate("res")->getNextGate()->getOwnerModule();
    gkp = check_and_cast<GateKeeper *>(mod);
}

// ���b�Z�[�W���͂�����Comnetpp.ini�ɂĎw�肳�ꂽ�Q�[�g����i�M���̐F�̕ύX�j���s��
void GateControl::handleMessage(cMessage *msg)
{
    if ( msg->isSelfMessage() ) {
        // �A�N�e�B�r�e�B�̏���������
        proctime.collect(simTime() - msg->getTimestamp());      // �A�N�e�B�r�e�B�̎��Ԃ��L�^
        send(msg, "out");                                       //��H���Ƀ��b�Z�[�W�𑗂�
    }
    else {
        // �O�H������͂������b�Z�[�W�̏ꍇ
        if (mode) gkp->open(kind);  else  gkp->close(kind);     // �w�肳�ꂽ�M���̐F��ύX����
        msg->setTimestamp(simTime());                           // �A�N�e�B�r�e�B�̊J�n���Ԃ��Z�b�g
        scheduleAt(simTime() + par("productionTime"), msg);     // ���Y�J�n
    }
}

//�@�m�[�h�̓��v����\��
void GateControl::finish()
{
    EV << "Gate Jobs Count:   " << proctime.getCount() << endl;
    EV << "Gate Utilization:  " << proctime.getSum() / simTime() << endl;
    EV << "Gate AVG ProcTime: " << proctime.getMean() << endl;

    proctime.recordAs("Gate ProcTime");
}


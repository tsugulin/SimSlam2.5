//�@�M�����ɂȂ�܂ŐM���҂��̐擪�ԗ���҂�����
#include "AwaitGate.h"
Define_Module(AwaitGate);
#include "GateKeeper.h"

void AwaitGate::initialize()
{
    // �҂��s��̕��ϒ������v�Z����N���X��������
    queuelen[1].init(simTime(), 100);
    queuelen[2].init(simTime(), 100);

    // Gate���\�[�X�̃|�C���^���擾
    cModule *mod1 = gate("res")->getNextGate()->getOwnerModule();
    gkp = check_and_cast<GateKeeper *>(mod1);
}

// �擪�̎Ԃ�M���҂��ɂ���
void AwaitGate::handleMessage(cMessage *msg)
{
    int k = msg->getKind();     // ���b�Z�[�W�̑�������Ԑ��̏����擾
    queuelen[k].set(simTime(), queue[k].getLength());       // �҂��s�񕽋ϒ������v�Z
    queue[k].insert(msg);       // �擪�̎Ԃ�M���҂��ɂ���
    goForward(k);               // �M���҂�����������
}

// �M���҂������Ă���Ԃ�����C�M�����Ȃ�ΐi�߂�
void AwaitGate::goForward(long k)
{
    Enter_Method("goForward");
    if ( queue[k].getLength() > 0 ) {       // �M���҂������Ă���Ԃ����邩�H
        if (gkp->check(k)) {                // �M���͐��H
            queuelen[k].set(simTime(), queue[k].getLength());               // �҂��s�񕽋ϒ������v�Z
            cMessage *msg = check_and_cast<cMessage *>(queue[k].pop());     // �҂��s�񂩂烁�b�Z�[�W�����o��
            send(msg, "out");                                               // ��H���ɑ���
        }
    }
}

//�@�M���̑҂��s��̕��ϒ�����\������
void AwaitGate::finish()
{
    EV << "SIGNAL1 Queue AVG Length: " << queuelen[1].get(simTime()) << endl;
    EV << "SIGNAL2 Queue AVG Length: " << queuelen[2].get(simTime()) << endl;
}


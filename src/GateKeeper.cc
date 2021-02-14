#include "GateKeeper.h"
Define_Module(GateKeeper);
#include "AwaitGate.h"

void GateKeeper::initialize()
{
    // �M����������
    signal[1] = false;  // �M��1�͐�
    signal[2] = false;  // �M��2����

    // AwaitGate�m�[�h�̃|�C���^���Z�b�g
    cModule *mod = gate("from_await")->getPreviousGate()->getOwnerModule();
    awaitNode = check_and_cast<AwaitGate *>(mod);
}

// �Q�[�g���J����D�M����ɕς���
void GateKeeper::open(long kind)
{
    Enter_Method("open");
    checkpoint[kind] = simTime();   // �Q�[�g���󂢂��������L�^
    signal[kind] = true;            // �M����ɕς���
    awaitNode->goForward(kind);     // �M���҂��̎Ԃɒm�点��
}

// �Q�[�g��߂�D�M����Ԃɕς���
void GateKeeper::close(long kind)
{
    Enter_Method("close");
    stats[kind].collect( simTime() - checkpoint[kind] );    // �Q�[�g���J�������Ԃ��L�^
    signal[kind] = false;           // �M����Ԃɕς���
}

// �Q�[�g�̊J���m�F����DTrue�Ȃ�ΐ�
bool GateKeeper::check(long kind)
{
    Enter_Method("check");
    return signal[kind];
}

// ���\�[�X�g�p�󋵂̕\��
void GateKeeper::finish()
{
    EV << "LIGHT1 Utilization: " << stats[1].getSum() / simTime() << endl;
    EV << "LIGHT2 Utilization: " << stats[2].getSum() / simTime() << endl;
}


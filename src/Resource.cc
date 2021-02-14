#include "Resource.h"
Define_Module(Resource);
#include "AwaitResource.h"

void Resource::initialize()
{
    // �ϐ���������
    owner[1] = 0;   // START1��������
    owner[2] = 0;   // START2��������

    // Await�m�[�h��Goon�m�[�h�̃|�C���^���擾
    cModule *mod = gate("from_await")->getPreviousGate()->getOwnerModule();
    awaitNode = check_and_cast<AwaitResource *>(mod);
}

// ���\�[�X�̊l�����s��
bool Resource::request(long kind, long id)
{
    Enter_Method("request");
    bool ret_code = false;          // �߂�l��������
    if ( owner[kind] == 0 ) {
        owner[kind] = id;           // �������\�[�X�����g�p�ł���Ηv���҂����p�\�Ƃ���
        checkpoint[kind] = simTime();     // ���\�[�X�l���������L�^
        ret_code = true;            // ���\�[�X�l���ɐ���
    }
    return ret_code;    // ���\�[�X�l���ł����true��߂�
}

// ���\�[�X�̉�����s��
bool Resource::release(long kind, long id)
{
    Enter_Method("release");
    bool ret_code = false;          // �߂�l��������
    if ( owner[kind] == id ) {
        owner[kind] = 0;            // ���\�[�X�����
        stats[kind].collect( simTime() - checkpoint[kind] );    // ���\�[�X�g�p���Ԃ��L�^
        awaitNode->goForward(kind); // ���̃��b�Z�[�W�̃��\�[�X���m�ۂ���
        ret_code = true;            // ���\�[�X����ɐ���
    }
    return ret_code;    // ���\�[�X����ł����true��߂�
}

void Resource::finish()
{
    EV << "START1 jobs Count:  " << stats[1].getCount() << endl;
    EV << "START1 Utilization: " << stats[1].getSum() / simTime() << endl;
    EV << "START2 jobs Count:  " << stats[2].getCount() << endl;
    EV << "START2 Utilization: " << stats[2].getSum() / simTime() << endl;
}

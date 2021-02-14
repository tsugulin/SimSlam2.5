#include "AwaitResource.h"
Define_Module(AwaitResource);
#include "Resource.h"

void AwaitResource::initialize()
{
    // �҂��s��̕��ϒ������v�Z����N���X��������
    queuelen[1].init(simTime(), 100);
    queuelen[2].init(simTime(), 100);

    // ���\�[�X�̃|�C���^���擾
    cModule *mod = gate("res")->getNextGate()->getOwnerModule();
    rsc = check_and_cast<Resource *>(mod);
}

void AwaitResource::handleMessage(cMessage *msg)
{
    int k = msg->getKind();
    queuelen[k].set(simTime(), queue[k].getLength());   // �҂��s�񕽋ϒ������v�Z
    queue[k].insert(msg);       // �҂��s��̍Ō���ɂ߃��b�Z�[�W��ǉ�
    goForward(k);               // �҂��s��ɗ��܂��Ă��郁�b�Z�[�W����������
}

// �҂��s��Ƀ��b�Z�[�W������Ώ�������
void AwaitResource::goForward(long k)
{
    Enter_Method("goForward");
    if (queue[k].getLength() > 0) {
        cMessage *msg = check_and_cast<cMessage *>(queue[k].front());   // �҂��s��̐擪���b�Z�[�W�����o��
        if ( rsc->request(k, msg->getId()) ) {                          // ���\�[�X��v��
            queuelen[k].set(simTime(), queue[k].getLength());           // �҂��s�񕽋ϒ������v�Z
            queue[k].pop();                                             // �҂��s�񂩂烁�b�Z�[�W�����o��
            send(msg, "out");                                           // ��H���ɑ���
        }
    }
}

//�@�m�[�h�̓��v����\��
void AwaitResource::finish()
{
    EV << "START1 Queue AVG Length: " << queuelen[1].get(simTime()) << endl;
    EV << "START2 Queue AVG Length: " << queuelen[2].get(simTime()) << endl;
}


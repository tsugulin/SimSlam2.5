#ifndef GATEKEEPER_H_
#define GATEKEEPER_H_

#include <omnetpp.h>
using namespace omnetpp;

class AwaitGate;

class GateKeeper : public cSimpleModule {
private:
    bool signal[3];             // �M���̏�Ԃ�\��
    AwaitGate *awaitNode;       // AwaitGate�m�[�h�ւ̃|�C���^
    simtime_t checkpoint[3];    // �Q�[�g���J���������Ԃ��L�^
    cStdDev stats[3];           // �M���̎g�p�󋵂��L�^

protected:
    virtual void initialize();  // �ϐ���������
    virtual void finish();      //�@���\�[�X�g�p�Ƌ���\��

public:
    virtual void open(long kind);   // �M����ɂ���
    virtual void close(long kind);  // �M����Ԃɂ���
    virtual bool check(long kind);  // �M���̐F���m�F����
};

#endif /* GATEKEEPER_H_ */

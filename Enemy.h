#pragma once
#include "Engine/GameObject.h"

class Enemy :public GameObject
{
    int hModel_;    //���f���ԍ�
    
    float movement_;//�ړ���
   
    XMVECTOR front_;
    
    XMFLOAT3 playerPos;//�v���C���[�̃|�W�V������T���Ȃ��Ƃ����Ȃ��̂ł�����i�[����ϐ�
    struct EnemyFan
    {
        float EnemyDegree;//����p�͈̔́i�p�x�j
        float EnemyLength;//���S�����܂ł̒���
    } enemyfan;

    
public:
    //�R���X�g���N�^
    Enemy(GameObject* parent);
    //�f�X�g���N�^
    ~Enemy();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

private:
    //�����Ă��邩
    bool IsFindPlayer(const XMFLOAT3& PlayerPos);

    //�v���C���[����������ǐ�
    void ChasePlayer();

    //�����Ă��Ȃ��ꍇ�̉�]�ړ�(5�`10�b�̊ԂɌ������ς��悤�ɂ���)
    void EnemySearch();

};


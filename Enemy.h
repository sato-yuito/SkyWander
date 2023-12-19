#pragma once
#include "Engine/GameObject.h"

class Enemy :public GameObject
{
    int hModel_;    //���f���ԍ�
    float movement_;
    float angle_;
    XMVECTOR front_;//�����Ă��������\���֐�
    XMVECTOR EnemyMove_;//�ړ���

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
    void ChasePlayer(XMFLOAT3 playerPos);

    //�ړ�����
    void EnemyMove();

};


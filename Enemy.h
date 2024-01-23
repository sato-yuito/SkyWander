#pragma once
#include "Engine/GameObject.h"
#include "Player.h"
class Enemy :public GameObject
{
    int hModel_;    //���f���ԍ�
    
    float movement_;//�ړ���
   
    XMVECTOR front_;
    
    Player* pPlayer;
    float elaspsedTime_;//�o�ߎ��Ԃ�ǐՂ��邽�߂̕ϐ�
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
    bool IsFindPlayer();

    //�v���C���[����������ǐ�
    void ChasePlayer();

    //�����Ă��Ȃ��ꍇ�̉�]�ړ�(5�`10�b�̊ԂɌ������ς��悤�ɂ���)
    void EnemySearch();

};


#pragma once
#include "Engine/GameObject.h"
#include"Player.h"
class Enemy :public GameObject
{
    int hModel_;    //���f���ԍ�
    float movement_;
    float angle_;
    int time_;
    int timing_;
   

    struct Position
    {
        XMVECTOR Enemypotion;//�G�̍��W
        XMVECTOR PlayerPositon;//�v���C���[�̍��W
    };

    struct EnemyFan
    {
        XMVECTOR EnemyPosition;//���S���W
        float EnemyDegree;//����p�͈̔́i�p�x�j
        float EnemyLength;//���S�����܂ł̒���
        float DirectionDegree;//��̕��������߂邽�߂ɕK�v�Ȃ���

    };

    EnemyFan  enemyfan;

    
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


    //����p�̐ݒ�
    bool EnemyPOV(const XMFLOAT3& PlayerVec);

    

    //�v���C���[����������ǐ�
    void ShowPlayer(Player&player,float speed);
};


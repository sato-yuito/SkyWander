#pragma once
#include "Engine/GameObject.h"
#include"json.hpp"
#include<fstream>

using json = nlohmann::json;

class Player:public GameObject
{ 

    enum class Playeraction
    {
        wait,//�������Ă��Ȃ����
        walk,//����
        jump,//�W�����v
        attack,//�U��
        fall//����
    }playerstate_;

    int playerModel;    //���f���ԍ�

    

    //�������Ă��Ȃ����
    void PlayerWait();

    //����
    void PlayerWalk();
    
    //�W�����v
    void PlayerJump();
    
    //�X�e�[�W�ɒ��n���Ă��邩�ǂ���
    bool stageDatahit();

    //�U��
    void PlayerAttack();
    
    //�v���C���[�̌�����ɒǔ����Ă����悤�ɂ���
    void PlayerCamTarget();

    //�v���C���[�̗�������
    void PlayerFall();

public:
    //�R���X�g���N�^
    Player(GameObject* parent);

    //�f�X�g���N�^
    ~Player();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
    
    //�����ɓ�������
    //�����FpTarget ������������
    void OnCollision(GameObject* pTarget) override;

    int GetModelHandle() { return playerModel; }
};


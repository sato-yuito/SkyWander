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
        useitem,//�A�C�e�����g��
        walkjump
    }playerstate_;

    int playerModel;    //���f���ԍ�

    int HP = 0;//�̗�

    int Attack = 0;//�U����

    //�������Ă��Ȃ����
    void PlayerWait();

    //����
    void PlayerWalk();
    
    //�W�����v
    void PlayerJump();
    
    //�U��
    void PlayerAttack();
    
    //�A�C�e�����g��
    void Useitem();

    //�v���C���[�̌�����ɒǔ����Ă����悤�ɂ���
    void PlayerCamTarget();

    //json�t�@�C����Load
    void Load();

    //json�t�@�C�����Z�[�u
    void Save();
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


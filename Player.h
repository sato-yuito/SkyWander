#pragma once
#include "Engine/GameObject.h"

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
    
    int GetModelHandle() { return hModel_; }
};


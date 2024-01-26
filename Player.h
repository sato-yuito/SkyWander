#pragma once
#include "Engine/GameObject.h"
#include"Map.h"
class Player:public GameObject
{
    int hModel_;    //���f���ԍ�
    Map* map;
   
    enum class Playeraction
    {
        wait,//�������Ă��Ȃ����
        Walk,//����
        run,//����
        jump,//�W�����v
        attack,//�U��
        useitem//�A�C�e�����g��
    }playerstate_;
    
    //�������Ă��Ȃ����
    void PlayerWait();
    //����
    void PlayerWalk();
    //����
    void PlayerRun();
    //�W�����v
    void PlayerJump();
    //�U��
    void PlayerAttack();
    //�A�C�e�����g��
    void UseAitem();

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


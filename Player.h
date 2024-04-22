#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include"Engine/Camera.h"
#include "Engine/BoxCollider.h"
#include"Engine/ImGui/imgui.h"
#include"Sword.h"
#include"Map.h"
#include"Floor.h"
#include"Treasure.h"
#include"json.hpp"

using json = nlohmann::json;

class Player:public GameObject
{ 
    enum class Playeraction
    {
        wait,//�������Ă��Ȃ����
        walk,//����
        jump,//�W�����v
        attack,//�U��
    }playerstate_;

    float PlayerSpeed;//�v���C���[�̑���
    float gravity//�d��
    float PlayerUP;//�W�����v�̏㏸��
    XMFLOAT3 PlayerVelocity ;//�ړ���
    XMFLOAT3 JumpVelocity ;//�W�����v�̈ړ���
    int HP;//�̗�
    int Attack;//�U����
    int playerModelhandle_;    //���f���ԍ�

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

    int GetModelHandle() { return playerModelhandle_; }

    int GetHP() { return HP; }

    int GetAttack() { return Attack; }
};


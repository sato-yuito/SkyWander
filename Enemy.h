#pragma once
#include"EnemyBase.h"
#include"Engine/GameObject.h"
class Enemy :public EnemyBase
{
private:
    int hModel_;


    std::string EnemyName ;
public:
    Enemy(GameObject* parent);

    ~Enemy();

   void Initialize()override;
    
   void Update()override;

   void Draw() override;

   void Release() override;

   bool IsFindPlayer() override;

   void ChasePlayer() override;
    
   
   void EnemyAttack() override;
};


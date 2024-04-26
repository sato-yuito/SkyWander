#pragma once
#include"EnemyBase.h"
#include"Engine/GameObject.h"
class Enemy :public EnemyBase
{
private:
    int hModel_;
    
    float movement_;//ˆÚ“®—Ê

    std::string EnemyName ;
public:
    Enemy(GameObject* parent);

    ~Enemy();

   void Initialize()override;
    
   void Update()override;

   void Draw() override;

   void Release() override;

   void ChasePlayer() override;
    
   void EnemySearch() override;
   
   void EnemyAttack() override;
};


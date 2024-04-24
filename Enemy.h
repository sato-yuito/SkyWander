#pragma once
#include "Engine/Model.h"
#include"EnemyBase.h"
#include"Map.h"

class Enemy :public EnemyBase
{
private:
    int hModel_;
    std::string EnemyName = "Enemy";
public:
    Enemy(GameObject* parent);

    ~Enemy();

   void Initialize()override;
    
   void Update()override;

   void Draw() override;

   void Release() override;

   bool IsFindPlayer() override;

   void ChasePlayer() override;
    
   void EnemySearch() override;
   
};


#include "TittleScene.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
TittleScene::TittleScene(GameObject* parent):GameObject(parent, "TittleScene"),titlePict_(-1){

}

void TittleScene::Initialize(){
	titlePict_ = Image::Load("StartScreen.png");
	assert(titlePict_ >= 0);
}

void TittleScene::Update(){
	if (Input::IsKey(DIK_SPACE) || Input::IsMouseButtonDown(0)){
		SceneManager* pTitleScene = (SceneManager*)FindObject("SceneManager");
		pTitleScene->ChangeScene(SCENE_ID_TEST);
     }
}

void TittleScene::Draw(){
	Image::SetTransform(titlePict_, transform_);
	Image::Draw(titlePict_);
}

void TittleScene::Release(){

}

#include "MainMenuScene.h"
#include "TiledMapScene.h"
#include "MainMenuBackgroundLayer.h"
#include "MainMenuMenuLayer.h"

USING_NS_CC;


MainMenuScene::MainMenuScene() {
	init();
}

CCScene* MainMenuScene::create() 
{
	CCScene* pScene = new MainMenuScene();
	return pScene;
}

bool MainMenuScene::init() 
{
	if (CCScene::init()) 
	{
		CCLayer *pBackgroundLayer = new MainMenuBackgroundLayer();
		this->addChild(pBackgroundLayer);

		CCLayer *pMenuLayer = new MainMenuMenuLayer();
		this->addChild(pMenuLayer);

		return true;
	}
	
	return false;
}

void MainMenuScene::ChangeScene()
{
	CCScene * pNewScene = new TiledMapScene();

	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5,pNewScene));
}

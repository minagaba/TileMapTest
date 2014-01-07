#include "TiledMapScene.h"
#include "MainMenuScene.h"
#include "TiledMapLayer.h"
#include "TiledMapAnimationLayer.h"

TiledMapScene::TiledMapScene()
{
	init();
}

CCScene* TiledMapScene::create() 
{
	CCScene* pScene = new TiledMapScene();
	return pScene;
}

bool TiledMapScene::init() 
{
	if (CCScene::init()) 
	{
		CCLayer *pMapLayer = new TiledMapLayer();
		this->addChild(pMapLayer);

		//CCLayer *pMapAnimationLayer = new TiledMapAnimationLayer();
		//this->addChild(pMapAnimationLayer);

		return true;
	}
	
	return false;
}

void TiledMapScene::ChangeScene()
{
	CCScene * pNewScene = new MainMenuScene();

	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5,pNewScene));
}


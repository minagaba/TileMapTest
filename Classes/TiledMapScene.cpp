#include "TiledMapScene.h"
#include "MainMenuScene.h"
#include "TiledMapLayer.h"
#include "TiledMapAnimationLayer.h"
#include "TiledMapButtonsLayer.h"

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
		m_pMapLayer = pMapLayer;

		//CCLayer *pMapAnimationLayer = new TiledMapAnimationLayer();
		//this->addChild(pMapAnimationLayer);

		CCLayer *pButtonsLayer = new TiledMapButtonsLayer();
		this->addChild(pButtonsLayer);

		return true;
	}
	
	return false;
}

void TiledMapScene::ChangeScene()
{
	CCScene * pNewScene = new MainMenuScene();

	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5,pNewScene));
}

void TiledMapScene::zoomMapInOut(bool bZoomIn)
{
	float fScale = (bZoomIn) ? 1.1f : 0.9f;
	m_pMapLayer->runAction( CCScaleBy::create(0.5f, fScale));
}

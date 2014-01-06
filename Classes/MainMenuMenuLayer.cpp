#include "MainMenuMenuLayer.h"
#include "MainMenuScene.h"

#define PLAY_BUTTON_NORMAL   "buttons/btn-play-normal.png"
#define PLAY_BUTTON_SELECTED "buttons/btn-play-selected.png"

MainMenuMenuLayer::MainMenuMenuLayer()
{
	setTouchEnabled(true);
	setTouchMode(kCCTouchesOneByOne);

	CCSprite *pPlayNormal = CCSprite::create(PLAY_BUTTON_NORMAL);
	CCSprite *pPlaySelected = CCSprite::create(PLAY_BUTTON_SELECTED);

	CCMenuItemSprite *pPlayButton = CCMenuItemSprite::create(pPlayNormal, pPlaySelected, NULL, this, menu_selector(MainMenuMenuLayer::PlayButtonCallback));

	CCMenu *pMenu = CCMenu::create(pPlayButton, NULL);
	addChild(pMenu);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	pMenu->setPosition(ccp(winSize.width/2, winSize.height/2));

}

void MainMenuMenuLayer::PlayButtonCallback(CCObject *sender)
{
	MainMenuScene *pMainMenuScene = (MainMenuScene*)(this->getParent());
	pMainMenuScene->ChangeScene();
}

bool MainMenuMenuLayer::ccTouchBegan(CCTouch *touch, CCEvent * pEvent)
{
	return true;
}

void MainMenuMenuLayer::ccTouchEnded(CCTouch *touch, CCEvent * pEvent)
{
}

void MainMenuMenuLayer::ccTouchCancelled(CCTouch *touch, CCEvent * pEvent)
{
}

void MainMenuMenuLayer::ccTouchMoved(CCTouch *touch, CCEvent * pEvent)
{
}

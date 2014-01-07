#include "MainMenuBackgroundLayer.h"

USING_NS_CC;

MainMenuBackgroundLayer::MainMenuBackgroundLayer()
{
    float x,y;

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    x = winSize.width;
    y = winSize.height;

	CCSprite* bg1 = CCSprite::create(BACKGROUND_IMAGE_FILE);
	CCSize bgSize = bg1->getContentSize();
    bg1->setPosition( ccp(winSize.width / 2, winSize.height / 2) );
	bg1->setScale(winSize.height / bgSize.height);
    addChild(bg1, -1);

	CCAnimation * animation = CCAnimation::create();
	int nNumberofFrames = 25;
	for (int i = 0; i < nNumberofFrames; i++) 
	{
		char szFilename[256] = {0};
		sprintf(szFilename, "Fire/%02d.png", i);
		animation->addSpriteFrameWithFileName(szFilename);
	}

	animation->setDelayPerUnit(3.0f / nNumberofFrames);
	animation->setRestoreOriginalFrame(true);

	CCAnimate *action = CCAnimate::create(animation);
	CCRepeatForever *loopAction = CCRepeatForever::create(action);

	CCSprite *fire = CCSprite::create("Fire/00.png");
	fire->setPosition(ccp(100, 100));
	addChild(fire);
	fire->runAction(loopAction);

}


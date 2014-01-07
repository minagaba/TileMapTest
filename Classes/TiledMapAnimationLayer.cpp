#include "TiledMapAnimationLayer.h"

#define DUDE_SPRITESHEET_FILENAME "dude2.png"

TiledMapAnimationLayer::TiledMapAnimationLayer()
{
	init();
}

bool TiledMapAnimationLayer::init()
{
	addDudeWithCoordinates(ccp(200,50));

	return true;
}

void TiledMapAnimationLayer::onEnter()
{
	CCLayer::onEnter();
	this->setTouchEnabled(true);
	this->setTouchPriority(2);
}

void TiledMapAnimationLayer::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    CCSetIterator it;
    CCTouch* touch;

    for (it = touches->begin(); it != touches->end(); it++)
    {
        touch = (CCTouch*)(*it);

        if(!touch)
            break;

        CCPoint location = touch->getLocation();

        addDudeWithCoordinates(location);
    }
}

bool TiledMapAnimationLayer::ccTouchBegan(CCTouch *touch, CCEvent * pEvent)
{
	return true;
}

void TiledMapAnimationLayer::ccTouchEnded(CCTouch *touch, CCEvent * pEvent)
{
}

void TiledMapAnimationLayer::ccTouchCancelled(CCTouch *touch, CCEvent * pEvent)
{
}

void TiledMapAnimationLayer::ccTouchMoved(CCTouch *touch, CCEvent * pEvent)
{
}

void TiledMapAnimationLayer::addDudeWithCoordinates(CCPoint p)
{
	CCSprite *pDude = NULL;

	CCSpriteBatchNode* pSpriteBatch = CCSpriteBatchNode::create("Dude/dude.png");
	
	CCSpriteFrameCache* pCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	pCache->addSpriteFramesWithFile("Dude/dude.plist");	

	pDude = CCSprite::createWithSpriteFrameName("00");
	pSpriteBatch->addChild(pDude);
	pSpriteBatch->setPosition(p);
	this->addChild(pSpriteBatch);
	
	int nNumberOfFrames = 16;
	float fFrameDelay = 0.05f;
	CCArray* animFramesArray = CCArray::createWithCapacity(nNumberOfFrames);
	char szFrameName[16] = {0};

	for (int i = 0; i < nNumberOfFrames; i++) 
	{
		sprintf(szFrameName, "%02d", i);
		CCSpriteFrame *pSpriteFrame = pCache->spriteFrameByName(szFrameName);
		animFramesArray->addObject(pSpriteFrame);
	}
 
	CCAnimation *pAnimation = CCAnimation::createWithSpriteFrames(animFramesArray, fFrameDelay);

	// combine move with animation
	// the duration of the move is the number of frames in the animation * delay for each frame
	float fMoveDuration = nNumberOfFrames * fFrameDelay;
	CCActionInterval *pSpawnActions = CCSpawn::create(CCAnimate::create(pAnimation), CCMoveBy::create(fMoveDuration, ccp(0,10)), NULL);
	pDude->runAction( CCRepeatForever::create( pSpawnActions ) );
}

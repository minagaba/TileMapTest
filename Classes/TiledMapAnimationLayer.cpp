#include "TiledMapAnimationLayer.h"

#define DUDE_SPRITESHEET_FILENAME "dude2.png"

TiledMapAnimationLayer::TiledMapAnimationLayer()
{
	init();
}

bool TiledMapAnimationLayer::init()
{
	this->setTouchEnabled(true);
	//setTouchMode(kCCTouchesOneByOne);
	//this->setTouchPriority(2);

	addDudeWithCoordinates(ccp(200,50));

	return true;
}

void TiledMapAnimationLayer::onEnter()
{
	CCLayer::onEnter();
}

bool TiledMapAnimationLayer::ccTouchBegan(CCTouch *touch, CCEvent * pEvent)
{
	CCLOG("TiledMapAnimationLayer::ccTouchBegan");

	return true;
}

void TiledMapAnimationLayer::ccTouchEnded(CCTouch *touch, CCEvent * pEvent)
{
	CCLOG("TiledMapAnimationLayer::ccTouchEnded");
}

void TiledMapAnimationLayer::ccTouchCancelled(CCTouch *touch, CCEvent * pEvent)
{
	CCLOG("TiledMapAnimationLayer::ccTouchCancelled");
}

void TiledMapAnimationLayer::ccTouchMoved(CCTouch *touch, CCEvent * pEvent)
{
	CCLOG("TiledMapAnimationLayer::ccTouchMoved");
}

void TiledMapAnimationLayer::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
	CCLOG("TiledMapAnimationLayer::ccTouchesEnded");

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

void TiledMapAnimationLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCLOG("TiledMapAnimationLayer::ccTouchesBegan");
}

void TiledMapAnimationLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	CCLOG("TiledMapAnimationLayer::ccTouchesMoved");
}

void TiledMapAnimationLayer::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
	CCLOG("TiledMapAnimationLayer::ccTouchesCancelled");
}

static int g_nDudesCount = 0;
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
	float fMoveDuration = nNumberOfFrames * fFrameDelay;
	CCArray* animFramesArray = CCArray::createWithCapacity(nNumberOfFrames);
	char szFrameName[16] = {0};

	for (int i = 0; i < nNumberOfFrames; i++) 
	{
		sprintf(szFrameName, "%02d", i);
		CCSpriteFrame *pSpriteFrame = pCache->spriteFrameByName(szFrameName);
		animFramesArray->addObject(pSpriteFrame);
	}
 
	CCAnimation *pAnimation = CCAnimation::createWithSpriteFrames(animFramesArray, fFrameDelay);

	float fDudeFacingAngel = g_nDudesCount * 60.0f;
	float fDudeWalkingAngel = (g_nDudesCount * 60.0f);// + 270;

	CCLOG("Face to: %f", fDudeFacingAngel);
	CCLOG("Walk to: %f", fDudeWalkingAngel);

	CCRotateTo *pRotate = CCRotateTo::create(0.0f, fDudeFacingAngel);
	pDude->runAction(pRotate);

	float speed = 10;
	float dy = cos(fDudeWalkingAngel * M_PI / 180) * speed;
	float dx = sin(fDudeWalkingAngel * M_PI / 180) * speed;
	CCLOG("direction=[%f, %f]", dx, dy);
	CCPoint direction = ccp(dx, dy);
	// combine move with animation
	// the duration of the move is the number of frames in the animation * delay for each frame
	CCActionInterval *pSpawnActions = CCSpawn::create(CCAnimate::create(pAnimation), CCMoveBy::create(fMoveDuration, direction), NULL);
	pDude->runAction( CCRepeatForever::create( pSpawnActions ) );

	g_nDudesCount++;
}

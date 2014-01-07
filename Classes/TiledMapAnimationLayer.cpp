#include "TiledMapAnimationLayer.h"

#define DUDE_SPRITESHEET_FILENAME "dude2.png"

TiledMapAnimationLayer::TiledMapAnimationLayer()
{
	init();
}

bool TiledMapAnimationLayer::init()
{
	CCSpriteBatchNode* pSpriteBatch = CCSpriteBatchNode::create("Dude/dude.png");
	
	CCSpriteFrameCache* pCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	pCache->addSpriteFramesWithFile("Dude/dude.plist");	

	m_pDude = CCSprite::createWithSpriteFrameName("00");
	pSpriteBatch->addChild(m_pDude);
	pSpriteBatch->setPosition(200, 50);
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
	m_pDude->runAction( CCRepeatForever::create( pSpawnActions ) );

	return true;
}

#include "TiledMapScene.h"
#include "TiledMapLayer.h"

#define ZOOMIN_BUTTON	"buttons/Zoom-In-64.png"
#define ZOOMOUT_BUTTON	"buttons/Zoom-Out-64.png"

TiledMapLayer::TiledMapLayer()
{
	//init();
}

void TiledMapLayer::onEnter()
{
	CCLayer::onEnter();
	init();
}

bool TiledMapLayer::init()
{
	setTouchEnabled(true);
	//setTouchMode(kCCTouchesOneByOne);
	//setTouchPriority(1);

	// background color
    CCLayerColor* color = CCLayerColor::create( ccc4(64,64,64,255) );
    this->addChild(color, -1);

    m_map = CCTMXTiledMap::create("maps/tiledmap1.tmx");
    this->addChild(m_map, 0);

	CCSize mapSize = m_map->getContentSize();
	CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();

	CCLOG("Map Size=[%f x %f]", mapSize.width, mapSize.height);
	CCLOG("Win Size=[%f x %f]", winSize.width, winSize.height);

	m_map->setAnchorPoint(ccp(0.5f, 0.5f));
	m_map->setPosition(winSize.width/2, winSize.height/2);
	m_fScaleFactor = (winSize.width/mapSize.width < winSize.height/mapSize.height) ? winSize.width/mapSize.width : winSize.height/mapSize.height;
	CCLOG("scale by: %f, %f", winSize.width/mapSize.width, winSize.height/mapSize.height);
	CCLOG("scale factor: %f", m_fScaleFactor);
	scaleTo(m_fScaleFactor);
	//m_map->runAction(CCScaleBy::create(0.3f, winSize.width/mapSize.width, winSize.height/mapSize.height));


	return true;
}

void TiledMapLayer::increaseScale(float scaleDiff)
{
	float scale = m_fScaleFactor * (1 + scaleDiff);
	scaleTo(scale);
}

void TiledMapLayer::decreaseScale(float scaleDiff)
{
	float scale = m_fScaleFactor * (1 - scaleDiff);
	scaleTo(scale);
}

void TiledMapLayer::scaleTo(float scale)
{
	m_fScaleFactor = scale;
	CCScaleTo *pScale = CCScaleTo::create(0.3f, m_fScaleFactor);
	m_map->runAction(pScale);
}

bool TiledMapLayer::ccTouchBegan(CCTouch *touch, CCEvent * pEvent)
{
	CCLOG("TiledMapLayer::ccTouchBegan");
	TiledMapScene *pTiledMapScene= (TiledMapScene*)(this->getParent());
	//pTiledMapScene->ChangeScene();

	return true;
}

void TiledMapLayer::ccTouchEnded(CCTouch *touch, CCEvent * pEvent)
{
	CCLOG("TiledMapLayer::ccTouchEnded");
	CCPoint location = touch->getLocation();
	//addDudeWithCoordinates(location);
}

void TiledMapLayer::ccTouchCancelled(CCTouch *touch, CCEvent * pEvent)
{
	CCLOG("TiledMapLayer::ccTouchCancelled");
}

void TiledMapLayer::ccTouchMoved(CCTouch *touch, CCEvent * pEvent)
{
	CCLOG("TiledMapLayer::ccTouchMoved");
}

void TiledMapLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCLOG("TiledMapLayer::ccTouchesBegan");

	CCTouch *touch = (CCTouch *)pTouches->anyObject();
	CCPoint p1 = touch->getLocation();
	CCPoint p2 = touch->getLocationInView();
	CCLOG("location: [%f, %f], location in view: [%f, %f]", p1.x, p1.y, p2.x, p2.y);
	p1 = ccp(p1.x * m_fScaleFactor, p1.y * m_fScaleFactor);
	p2 = ccp(p2.x * m_fScaleFactor, p2.y * m_fScaleFactor);
	CCLOG("scaled location: [%f, %f], location in view: [%f, %f]", p1.x, p1.y, p2.x, p2.y);
}

void TiledMapLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	CCLOG("TiledMapLayer::ccTouchesMoved");


    CCSetIterator it;
    CCTouch* touch;

    for (it = pTouches->begin(); it != pTouches->end(); it++)
    {
        touch = (CCTouch*)(*it);

        if(!touch)
            break;
		
		CCPoint diff = touch->getDelta();
		CCPoint currentPos = m_map->getPosition();
		//CCLOG("Old Pos: [%f, %f]", currentPos.x, currentPos.y);
		CCSize layerSize = m_map->boundingBox().size;
		//CCLOG("Layer size: [%f, %f]", layerSize.width, layerSize.height);
		m_map->setPosition( ccpAdd(currentPos, diff) );
		
		CCPoint newPos = m_map->getPosition();
		//CCLOG("New position = [%f , %f]", newPos.x, newPos.y);
	}

	// check if the layer is off screen (if so, then move it back)
	CCPoint pos = m_map->getPosition();
	CCPoint anchor = m_map->getAnchorPoint();
	//CCLOG("pos=[%f,%f], anchor=[%f,%f]", pos.x, pos.y, anchor.x, anchor.y);
}

void TiledMapLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCLOG("TiledMapLayer::ccTouchesEnded");
}

void TiledMapLayer::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
	CCLOG("TiledMapLayer::ccTouchesCancelled");
}

void TiledMapLayer::addDudeWithCoordinates(CCPoint p)
{
	return;

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
	pDude->runAction( CCScaleTo::create(0.5f, 0.2f));
	CCActionInterval *pSpawnActions = CCSpawn::create(CCAnimate::create(pAnimation), CCMoveBy::create(fMoveDuration, ccp(0,10)), NULL);
	pDude->runAction( CCRepeatForever::create( pSpawnActions ) );
}
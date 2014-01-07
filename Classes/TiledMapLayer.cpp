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
	setTouchMode(kCCTouchesOneByOne);
	setTouchPriority(1);

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
	m_map->runAction(CCScaleBy::create(1.0f, winSize.width/mapSize.width, winSize.height/mapSize.height));

	createZoomMenu();

	return true;
}

void TiledMapLayer::createZoomMenu()
{
	CCSprite *pZoomIn = CCSprite::create(ZOOMIN_BUTTON);
	CCSprite *pZoomOut = CCSprite::create(ZOOMOUT_BUTTON);

	CCMenuItemSprite *pZoomInButton = CCMenuItemSprite::create(pZoomIn, NULL, NULL, this, menu_selector(TiledMapLayer::zoomIn));
	CCMenuItemSprite *pZoomOutButton = CCMenuItemSprite::create(pZoomOut, NULL, NULL, this, menu_selector(TiledMapLayer::zoomOut));

	m_pMenu = CCMenu::create(pZoomInButton, pZoomOutButton, NULL);
	this->addChild(m_pMenu);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSize menuSize(pZoomIn->getContentSize().width + pZoomOut->getContentSize().width, pZoomIn->getContentSize().height);

	m_pMenu->setAnchorPoint(ccp(0.5f, 0.5f));
	m_pMenu->alignItemsHorizontally();
	m_pMenu->setPosition(ccp(winSize.width - (menuSize.width/2), menuSize.height/2));
}

void TiledMapLayer::zoomIn(CCObject *sender)
{
	this->runAction( CCScaleBy::create(0.5f, 1.1f));
	CCPoint p = m_pMenu->getPosition();
}

void TiledMapLayer::zoomOut(CCObject *sender)
{
	this->runAction( CCScaleBy::create(0.5f, 0.9f));
	CCPoint p = m_pMenu->getPosition();
}

bool TiledMapLayer::ccTouchBegan(CCTouch *touch, CCEvent * pEvent)
{
	TiledMapScene *pTiledMapScene= (TiledMapScene*)(this->getParent());
	//pTiledMapScene->ChangeScene();

	return true;
}

void TiledMapLayer::ccTouchEnded(CCTouch *touch, CCEvent * pEvent)
{
	CCPoint location = touch->getLocation();
	addDudeWithCoordinates(location);
}

void TiledMapLayer::ccTouchCancelled(CCTouch *touch, CCEvent * pEvent)
{
}

void TiledMapLayer::ccTouchMoved(CCTouch *touch, CCEvent * pEvent)
{
	CCPoint diff = touch->getDelta();
    CCPoint currentPos = getPosition();
    setPosition( ccpAdd(currentPos, diff) );

	CCPoint newPos = getPosition();
	CCLOG("Pos = [%f , %f]", newPos.x, newPos.y);
}

void TiledMapLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
}

void TiledMapLayer::addDudeWithCoordinates(CCPoint p)
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
	pDude->runAction( CCScaleTo::create(0.5f, 0.2f));
	CCActionInterval *pSpawnActions = CCSpawn::create(CCAnimate::create(pAnimation), CCMoveBy::create(fMoveDuration, ccp(0,10)), NULL);
	pDude->runAction( CCRepeatForever::create( pSpawnActions ) );
}
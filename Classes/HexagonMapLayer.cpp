#include "HexagonMapLayer.h"

HexagonMapLayer::HexagonMapLayer()
{
}


void HexagonMapLayer::onEnter()
{
	CCLayer::onEnter();
	init();
}

bool HexagonMapLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	m_pTiledMap = CCTMXTiledMap::create("maps/hexagonmap2.tmx");
	if (!m_pTiledMap) 
	{
		// TODO: add logging
		return false;
	}

	m_pBackgroundLayer = m_pTiledMap->layerNamed("Background");
	if (!m_pBackgroundLayer)
	{
		return false;
	}

	this->addChild(m_pTiledMap);

	//CCSpriteBatchNode* pSpriteBatch = CCSpriteBatchNode::create("Dude/dude.png");
	//CCSpriteFrameCache* pCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	CCTMXObjectGroup *objectGroup = m_pTiledMap->objectGroupNamed("Objects");
	if(objectGroup == NULL)
	{
		CCLog("tile map has no objects object layer");
		return false;
	}
	
	CCDictionary *spawnPoint = objectGroup->objectNamed("MapCenter");
	
	int x = ((CCString)*spawnPoint->valueForKey("x")).intValue();
	int y = ((CCString)*spawnPoint->valueForKey("y")).intValue();
	CCLOG("MapCenter from tmx: [%d, %d]", x, y);

	createDudeWithCoordinates(ccp(x,y));
	setViewPointCenter(ccp(x,y));

	this->setTouchEnabled(true);

	return true;
}

void HexagonMapLayer::createDudeWithCoordinates(CCPoint location)
{
	m_pAnimatedDude = CCSpriteBatchNode::create("Dude/dude.png");
	CCSpriteFrameCache* pCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	pCache->addSpriteFramesWithFile("Dude/dude.plist");	
	m_pDudeSprite = CCSprite::createWithSpriteFrameName("00");
	m_pAnimatedDude->addChild(m_pDudeSprite);
	m_pAnimatedDude->setPosition(location);
	this->addChild(m_pAnimatedDude);

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
	m_pDudeSprite->runAction(CCRepeatForever::create(CCAnimate::create(pAnimation)));
}

void HexagonMapLayer::setViewPointCenter(CCPoint position)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
 
    int x = MAX(position.x, winSize.width/2);
    int y = MAX(position.y, winSize.height/2);
    x = MIN(x, (m_pTiledMap->getMapSize().width * this->m_pTiledMap->getTileSize().width) - winSize.width / 2);
    y = MIN(y, (m_pTiledMap->getMapSize().height * m_pTiledMap->getTileSize().height) - winSize.height/2);
    CCPoint actualPosition = ccp(x, y);
 
    CCPoint centerOfView = ccp(winSize.width/2, winSize.height/2);
    CCPoint viewPoint = ccpSub(centerOfView, actualPosition);
    this->setPosition(viewPoint);
}

void HexagonMapLayer::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool HexagonMapLayer::ccTouchBegan(CCTouch *touch, CCEvent *event)
{
    return true;
}

void HexagonMapLayer::ccTouchEnded(CCTouch *touch, CCEvent *event)
{
    CCPoint touchLocation = touch->getLocationInView();
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
    touchLocation = this->convertToNodeSpace(touchLocation);
 
	CCPoint playerPos = m_pAnimatedDude->getPosition();
    CCPoint diff = ccpSub(touchLocation, playerPos);
 
    if ( abs(diff.x) > abs(diff.y) ) {
        if (diff.x > 0) {
            playerPos.x += m_pTiledMap->getTileSize().width;
        } else {
            playerPos.x -= m_pTiledMap->getTileSize().width;
        }
    } else {
        if (diff.y > 0) {
            playerPos.y += m_pTiledMap->getTileSize().height;
        } else {
            playerPos.y -= m_pTiledMap->getTileSize().height;
        }
    }
 
    // safety check on the bounds of the map
    if (playerPos.x <= (m_pTiledMap->getMapSize().width * m_pTiledMap->getTileSize().width) &&
        playerPos.y <= (m_pTiledMap->getMapSize().height * m_pTiledMap->getTileSize().height) &&
        playerPos.y >= 0 &&
        playerPos.x >= 0 )
    {
        this->setDudePosition(playerPos);
    }
 
    this->setViewPointCenter(m_pAnimatedDude->getPosition());
}

void HexagonMapLayer::setDudePosition(CCPoint position) {
    m_pAnimatedDude->setPosition(position);
}
#include "TiledMapScene.h"
#include "TiledMapLayer.h"

TiledMapLayer::TiledMapLayer()
{
	init();
}

static int zevel = 0;

bool TiledMapLayer::init()
{
	setTouchEnabled(true);
	setTouchMode(kCCTouchesOneByOne);

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
	m_map->runAction(CCScaleBy::create(5.0f, winSize.width/mapSize.width, winSize.height/mapSize.height));

	return false;
}

bool TiledMapLayer::ccTouchBegan(CCTouch *touch, CCEvent * pEvent)
{
	TiledMapScene *pTiledMapScene= (TiledMapScene*)(this->getParent());
	//pTiledMapScene->ChangeScene();

	return true;
}

void TiledMapLayer::ccTouchEnded(CCTouch *touch, CCEvent * pEvent)
{
}

void TiledMapLayer::ccTouchCancelled(CCTouch *touch, CCEvent * pEvent)
{
}

void TiledMapLayer::ccTouchMoved(CCTouch *touch, CCEvent * pEvent)
{
	CCPoint diff = touch->getDelta();
    CCPoint currentPos = m_map->getPosition();
    m_map->setPosition( ccpAdd(currentPos, diff) );

	CCPoint newPos = m_map->getPosition();
	CCLOG("Pos = [%f , %f]", newPos.x, newPos.y);
}

void TiledMapLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CCTouch *touch = (CCTouch*)pTouches->anyObject();
    
    CCPoint diff = touch->getDelta();
    //CCNode *node = getChildByTag(kTagTileMap);
    CCPoint currentPos = m_map->getPosition();
    m_map->setPosition( ccpAdd(currentPos, diff) );
}

#include "HexagonMapLayer.h"

#define HEXAGON_MAPS_WIDTH_FACTOR 0.75f

//#define TILE_BOUNDING_BOX_ON_CLICK

#define LOG_CCPOINT(arg) CCLOG(#arg": [%f, %f]", arg.x, arg.y)
#define LOG_FLOAT(arg)   CCLOG(#arg": %f", arg)

HexagonMapLayer::HexagonMapLayer()
{
	m_fScaleFactor = 1.0f;
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

	m_pHighlitedLayer = m_pTiledMap->layerNamed("Highlighted");
	if (!m_pHighlitedLayer)
	{
		return false;
	}
	
	m_selectedTile = ccp(0,0);
	m_selectedTileGid = m_pHighlitedLayer->tileGIDAt(m_selectedTile);

	this->addChild(m_pTiledMap);

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
	//setViewPointCenter(ccp(x,y));

	this->setTouchEnabled(true);

	CCSize layerSize = this->getContentSize();
	CCSize mapSize = m_pTiledMap->getContentSize();

	// center the map within the layer
	m_pTiledMap->setAnchorPoint(ccp(0.5f * HEXAGON_MAPS_WIDTH_FACTOR, 0.5f));
	m_pTiledMap->setPosition(ccp(layerSize.width/2, layerSize.height/2));

	// scale the map to fit the layer
	float scale = layerSize.height / mapSize.height;
	scaleTo(scale*2);
	//scaleTo(1.0f);

	moveMapView(ccp(0,0));

	m_pDrawNode = CCDrawNode::create();
	m_pTiledMap->addChild(m_pDrawNode);

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

	m_pTiledMap->addChild(m_pAnimatedDude);
	//this->addChild(m_pAnimatedDude);

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
    x = MIN(x, (m_pTiledMap->getMapSize().width * m_pTiledMap->getTileSize().width) - winSize.width / 2);
    y = MIN(y, (m_pTiledMap->getMapSize().height * m_pTiledMap->getTileSize().height) - winSize.height/2);
    CCPoint actualPosition = ccp(x, y);
 
    CCPoint centerOfView = ccp(winSize.width/2, winSize.height/2);
    CCPoint viewPoint = ccpSub(centerOfView, actualPosition);
    m_pTiledMap->setPosition(viewPoint);
}

void HexagonMapLayer::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool HexagonMapLayer::ccTouchBegan(CCTouch *touch, CCEvent *event)
{
    return true;
}

CCPoint HexagonMapLayer::getMapCoordsFromTouch(CCTouch *touch)
{
	CCPoint touchLocation = touch->getLocationInView();
	touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
	CCLOG("touch on screen [%f, %f]", touchLocation.x, touchLocation.y);
	touchLocation = m_pTiledMap->convertToNodeSpace(touchLocation);
	CCLOG("touch on map [%f, %f]", touchLocation.x, touchLocation.y);

	CCSize tileSize = m_pTiledMap->getTileSize();
	CCSize mapSize = m_pTiledMap->getContentSize();

	CCPoint top = ccp(touchLocation.x, mapSize.height);
	CCPoint bottom = ccp(touchLocation.x, 0);
	CCPoint left = ccp(0, touchLocation.y);
	CCPoint right = ccp(mapSize.width, touchLocation.y);
	ccColor4F touchLocationColor = ccc4f(1.0f, 0.0f, 0.0f, 1.0f);

	int col, row;
	col = (int)((touchLocation.x - tileSize.width/8) / (tileSize.width * HEXAGON_MAPS_WIDTH_FACTOR));
	if (col & 1) 
	{
		row = (int)((touchLocation.y - (tileSize.height/2)) / tileSize.height);
	} else {
		row = (int)(touchLocation.y / tileSize.height);
	}
	CCLOG("col=%d", col);
	CCLOG("row=%d", row);

#ifdef TILE_BOUNDING_BOX_ON_CLICK
	m_pDrawNode->clear();
	m_pDrawNode->drawSegment(top, bottom, 2.0f, touchLocationColor);
	m_pDrawNode->drawSegment(left, right, 2.0f, touchLocationColor);

	ccColor4F gridColor = ccc4f(0.0f, 0.0f, 1.0f, 1.0f);
	float gridLeft, gridRight, gridUp, gridBottom;

	gridLeft = col * (tileSize.width * HEXAGON_MAPS_WIDTH_FACTOR) + (tileSize.width / 8);
	//gridRight = gridLeft + (tileSize.width * HEXAGON_MAPS_WIDTH_FACTOR);
	gridRight = gridLeft + tileSize.width - (tileSize.width / 4);

	gridBottom = row * tileSize.height;
	if (col & 1) {
		gridBottom += (tileSize.height/2);
	}
	gridUp = gridBottom + tileSize.height;

	m_pDrawNode->drawSegment(ccp(gridLeft, gridBottom), ccp(gridLeft, gridUp), 2.0f, gridColor);
	m_pDrawNode->drawSegment(ccp(gridRight, gridBottom), ccp(gridRight, gridUp), 2.0f, gridColor);
	m_pDrawNode->drawSegment(ccp(gridLeft, gridBottom), ccp(gridRight, gridBottom), 2.0f, gridColor);
	m_pDrawNode->drawSegment(ccp(gridLeft, gridUp), ccp(gridRight, gridUp), 2.0f, gridColor);
#endif // TILE_BOUNDING_BOX_ON_CLICK

	if (col & 1) {
		row = m_pTiledMap->getMapSize().height - (row + 2);
	} else {
		row = m_pTiledMap->getMapSize().height - (row + 1);
	}

	CCPoint coords = ccp(col, row);

	return coords;
}

void HexagonMapLayer::ccTouchEnded(CCTouch *touch, CCEvent *event)
{
	CCPoint coords = getMapCoordsFromTouch(touch);
	
	// TODO: validate that the coordinate is within the selectable boundries (within the hexagon).

	// remove the last highlighted tile
	m_pHighlitedLayer->removeTileAt(m_selectedTile);

	// highlight the newly selected tile
	m_selectedTile = coords;
	m_pHighlitedLayer->setTileGID(m_selectedTileGid, m_selectedTile);
}

void HexagonMapLayer::ccTouchMoved(CCTouch *touch, CCEvent *event)
{
	CCLOG("HexagonMapLayer::ccTouchMoved");
	CCPoint location = touch->getLocationInView();
	CCLOG("move: location in view [%f, %f]", location.x, location.y);

	CCPoint diff = touch->getDelta();
	CCLOG("move: diff [%f, %f]", diff.x, diff.y);

	moveMapView(diff);
}

void HexagonMapLayer::moveMapView(CCPoint diff)
{
	CCPoint currPosition = m_pTiledMap->getPosition();
	CCLOG("move: curr [%f, %f]", currPosition.x, currPosition.y);

	CCPoint newPosition = ccpAdd(currPosition, diff);
	CCLOG("move: new [%f, %f]", newPosition.x, newPosition.y);

	m_pTiledMap->setPosition(newPosition);

	fixMapPosition();
}

void HexagonMapLayer::fixMapPosition()
{
	CCLOG("*** HexagonMapLayer::fixMapPosition()");

	CCPoint position = m_pTiledMap->getPosition();
	LOG_CCPOINT(position);

	CCSize layerSize = this->getContentSize();
	CCPoint centerOfView = ccp(layerSize.width/2, layerSize.height/2);
	LOG_CCPOINT(centerOfView);

	CCPoint anchor = m_pTiledMap->getAnchorPoint();
	float mapWidth = m_fScaleFactor * m_pTiledMap->getContentSize().width * HEXAGON_MAPS_WIDTH_FACTOR;
	float mapHeight = m_fScaleFactor * m_pTiledMap->getContentSize().height;
	LOG_FLOAT(mapWidth);
	LOG_FLOAT(mapHeight);

	//  if map is too small then need to enlarge it
	if (mapWidth < layerSize.width) 
	{
		float mapw = HEXAGON_MAPS_WIDTH_FACTOR * m_pTiledMap->getContentSize().width;
		scaleTo(layerSize.width / mapw);
	} else if (mapHeight < layerSize.height) {
		scaleTo(layerSize.height / m_pTiledMap->getContentSize().height);
	}

	CCPoint fixedPosition = position;
	if ((fixedPosition.x - m_fScaleFactor * m_pTiledMap->getContentSize().width * anchor.x) > 0) {
		fixedPosition.x = m_fScaleFactor * m_pTiledMap->getContentSize().width * anchor.x;
	}
	if ((fixedPosition.y - m_fScaleFactor * m_pTiledMap->getContentSize().height * anchor.y) > 0) {
		fixedPosition.y = m_fScaleFactor * m_pTiledMap->getContentSize().height * anchor.y;
	}
	float rightDiff = fixedPosition.x + m_fScaleFactor * m_pTiledMap->getContentSize().width * (HEXAGON_MAPS_WIDTH_FACTOR - anchor.x) - layerSize.width;
	if (rightDiff < 0)
	{
		fixedPosition.x -= rightDiff;
	}
	float topDiff = fixedPosition.y + m_fScaleFactor * m_pTiledMap->getContentSize().height * (1 - anchor.y) - layerSize.height;
	if (topDiff < 0) 
	{
		fixedPosition.y -= topDiff;
	}

	m_pTiledMap->setPosition(fixedPosition);
}

void HexagonMapLayer::setDudePosition(CCPoint position) 
{
	CCMoveTo *pMove = CCMoveTo::create(0.3f, position);
	m_pAnimatedDude->runAction(pMove);
    //m_pAnimatedDude->setPosition(position);
}

void HexagonMapLayer::increaseScale(float scaleDiff)
{
	float scale = m_fScaleFactor * (1 + scaleDiff);
	scaleTo(scale);
}

void HexagonMapLayer::decreaseScale(float scaleDiff)
{
	float scale = m_fScaleFactor * (1 - scaleDiff);
	scaleTo(scale);
}

void HexagonMapLayer::scaleTo(float scale)
{
	CCLOG("HexagonMapLayer::scaleTo %f", scale);
	m_fScaleFactor = scale;
	CCScaleTo *pScale = CCScaleTo::create(0.2f, m_fScaleFactor);
	m_pTiledMap->runAction(pScale);
	//this->runAction(pScale);

	fixMapPosition();
}

CCPoint HexagonMapLayer::pixelToHexagonGrid(CCPoint p)
{
	CCPoint xy;

	CCSize layerSize = this->getContentSize();
	CCLOG("layerSize: [%f, %f]", layerSize.width, layerSize.height);

	float tileWidth = m_pTiledMap->getTileSize().width;
	float tileHeight = m_pTiledMap->getTileSize().height;

	float rows = m_pTiledMap->getMapSize().height;
	float cols = m_pTiledMap->getMapSize().width;

	CCLOG("map rows,cols = [%f, %f]", rows, cols);
	CCLOG("tile: [%f x %f] pixels", tileWidth, tileHeight);
	CCLOG("map: [%f, %f] pixels", cols*tileWidth, rows*tileHeight);
	CCLOG("clicked at: [%f, %f]", p.x, p.y);


	int tileRow = (int) p.y / (int) tileHeight;
	int tileCol;
	if (tileRow & 1) 
	{
		tileCol = (int) (p.x + (tileWidth / 2 )) / tileWidth;
	} else {
		tileCol = (int) p.x / (int) tileWidth;
	}
	CCLOG("tile: row col = [%d, %d]", tileRow, tileCol);

	//m_pBackgroundLayer->removeTileAt(ccp(tileRow, tileCol));
	//m_pBackgroundLayer->removeChildAtIndex

	return xy;
}

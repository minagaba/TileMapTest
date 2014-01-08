#include "TiledMapButtonsLayer.h"
#include "TiledMapScene.h"

#define ZOOMIN_BUTTON	"buttons/Zoom-In-64.png"
#define ZOOMOUT_BUTTON	"buttons/Zoom-Out-64.png"

TiledMapButtonsLayer::TiledMapButtonsLayer()
{
}

void TiledMapButtonsLayer::onEnter()
{
	CCLayer::onEnter();
	init();
}


bool TiledMapButtonsLayer::init()
{
	createZoomButtons();
	return true;
}

void TiledMapButtonsLayer::createZoomButtons()
{
	CCSprite *pZoomIn = CCSprite::create(ZOOMIN_BUTTON);
	CCSprite *pZoomOut = CCSprite::create(ZOOMOUT_BUTTON);

	CCMenuItemSprite *pZoomInButton = CCMenuItemSprite::create(pZoomIn, NULL, NULL, this, menu_selector(TiledMapButtonsLayer::zoomIn));
	CCMenuItemSprite *pZoomOutButton = CCMenuItemSprite::create(pZoomOut, NULL, NULL, this, menu_selector(TiledMapButtonsLayer::zoomOut));

	m_pMenu = CCMenu::create(pZoomInButton, pZoomOutButton, NULL);
	this->addChild(m_pMenu);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSize menuSize(pZoomIn->getContentSize().width + pZoomOut->getContentSize().width, pZoomIn->getContentSize().height);

	m_pMenu->setAnchorPoint(ccp(0.5f, 0.5f));
	m_pMenu->alignItemsHorizontally();
	m_pMenu->setPosition(ccp(winSize.width - (menuSize.width/2), menuSize.height/2));
}

void TiledMapButtonsLayer::zoomIn(CCObject *sender)
{
	TiledMapScene *pScene = (TiledMapScene *)this->getParent();
	pScene->zoomMapInOut(true);
	//this->runAction( CCScaleBy::create(0.5f, 1.1f));
	//CCPoint p = m_pMenu->getPosition();
}

void TiledMapButtonsLayer::zoomOut(CCObject *sender)
{
	TiledMapScene *pScene = (TiledMapScene *)this->getParent();
	pScene->zoomMapInOut(false);
	//this->runAction( CCScaleBy::create(0.5f, 0.9f));
	//CCPoint p = m_pMenu->getPosition();
}
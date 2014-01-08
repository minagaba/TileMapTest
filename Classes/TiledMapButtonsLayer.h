#ifndef __TILEDMAPBUTTONSLAYER_H__
#define __TILEDMAPBUTTONSLAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class TiledMapButtonsLayer : public CCLayer
{
public:
	TiledMapButtonsLayer();

	bool init();
	/*
    virtual bool ccTouchBegan(CCTouch *touch, CCEvent * pEvent);
    virtual void ccTouchEnded(CCTouch *touch, CCEvent * pEvent);
    virtual void ccTouchCancelled(CCTouch *touch, CCEvent * pEvent);
    virtual void ccTouchMoved(CCTouch *touch, CCEvent * pEvent);

	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
	*/
	virtual void onEnter();

private:
	void createZoomButtons();
	void zoomIn(CCObject *sender);
	void zoomOut(CCObject *sender);

	CCMenu *m_pMenu;
};

#endif // __TILEDMAPBUTTONSLAYER_H__
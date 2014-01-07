#ifndef __TILEDMAPLAYER_H__
#define __TILEDMAPLAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class TiledMapLayer : public CCLayer
{
public:
	TiledMapLayer();

	bool init();

    virtual bool ccTouchBegan(CCTouch *touch, CCEvent * pEvent);
    virtual void ccTouchEnded(CCTouch *touch, CCEvent * pEvent);
    virtual void ccTouchCancelled(CCTouch *touch, CCEvent * pEvent);
    virtual void ccTouchMoved(CCTouch *touch, CCEvent * pEvent);

	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);

	virtual void onEnter();

private:
	void addDudeWithCoordinates(CCPoint p);
	void createZoomMenu();

	void zoomIn(CCObject *sender);
	void zoomOut(CCObject *sender);

	CCTMXTiledMap* m_map;
	CCMenu *m_pMenu;
};

#endif // __TILEDMAPLAYER_H__

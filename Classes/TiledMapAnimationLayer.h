#ifndef __TILEDMAPANIMATIONLAYER_H__
#define __TILEDMAPANIMATIONLAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class TiledMapAnimationLayer : public CCLayer
{
public:
	TiledMapAnimationLayer();

	bool init();

    virtual bool ccTouchBegan(CCTouch *touch, CCEvent * pEvent);
    virtual void ccTouchEnded(CCTouch *touch, CCEvent * pEvent);
    virtual void ccTouchCancelled(CCTouch *touch, CCEvent * pEvent);
    virtual void ccTouchMoved(CCTouch *touch, CCEvent * pEvent);

	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);

	virtual void onEnter();

private:
	void addDudeWithCoordinates(CCPoint p);

	CCSprite *m_pDude;
};

#endif // __TILEDMAPANIMATIONLAYER_H__

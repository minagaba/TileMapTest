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

	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);

	virtual void onEnter();

	void increaseScale(float scaleDiff = 0.1f);
	void decreaseScale(float scaleDiff = 0.1f);
	void scaleTo(float scale);

private:
	void addDudeWithCoordinates(CCPoint p);

	CCTMXTiledMap* m_map;
	float          m_fScaleFactor;
};

#endif // __TILEDMAPLAYER_H__

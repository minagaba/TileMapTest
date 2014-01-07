#ifndef __TILEDMAPANIMATIONLAYER_H__
#define __TILEDMAPANIMATIONLAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class TiledMapAnimationLayer : public CCLayer
{
public:
	TiledMapAnimationLayer();

	bool init();

	virtual void onEnter();
    virtual bool ccTouchBegan(CCTouch *touch, CCEvent * pEvent);
    virtual void ccTouchEnded(CCTouch *touch, CCEvent * pEvent);
    virtual void ccTouchCancelled(CCTouch *touch, CCEvent * pEvent);
    virtual void ccTouchMoved(CCTouch *touch, CCEvent * pEvent);

	virtual void ccTouchesEnded(CCSet* touches, CCEvent* event);
	
private:
	void addDudeWithCoordinates(CCPoint p);

	CCSprite *m_pDude;
};

#endif // __TILEDMAPANIMATIONLAYER_H__

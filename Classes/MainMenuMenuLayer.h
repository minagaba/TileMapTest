#ifndef __MAINMENUMENULAYER_H__
#define __MAINMENUMENULAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class MainMenuMenuLayer : public cocos2d::CCLayer
{
public:
	MainMenuMenuLayer();

	void PlayButtonCallback(CCObject* sender);

    virtual bool ccTouchBegan(CCTouch *touch, CCEvent * pEvent);
    virtual void ccTouchEnded(CCTouch *touch, CCEvent * pEvent);
    virtual void ccTouchCancelled(CCTouch *touch, CCEvent * pEvent);
    virtual void ccTouchMoved(CCTouch *touch, CCEvent * pEvent);

};

#endif // __MAINMENUMENULAYER_H__

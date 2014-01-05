#ifndef __MAINMENUSCENE_H__
#define __MAINMENUSCENE_H__

#include "cocos2d.h"

/*
class MainMenuScene1 : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(MainMenuScene1);
};
*/

class MainMenuScene : public cocos2d::CCScene
{
public:
	MainMenuScene();

	virtual bool init();

	static cocos2d::CCScene* create();
};

#endif // __MAINMENUSCENE_H__

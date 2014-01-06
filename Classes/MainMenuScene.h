#ifndef __MAINMENUSCENE_H__
#define __MAINMENUSCENE_H__

#include "cocos2d.h"

class MainMenuScene : public cocos2d::CCScene
{
public:
	MainMenuScene();

	virtual bool init();

	static cocos2d::CCScene* create();
	void ChangeScene();
};

#endif // __MAINMENUSCENE_H__

#ifndef __TILEDMAPANIMATIONLAYER_H__
#define __TILEDMAPANIMATIONLAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class TiledMapAnimationLayer : public CCLayer
{
public:
	TiledMapAnimationLayer();

	bool init();

private:
	CCSprite *m_pDude;
};

#endif // __TILEDMAPANIMATIONLAYER_H__

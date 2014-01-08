#ifndef __TILEDMAPSCENE_H__
#define __TILEDMAPSCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class TiledMapScene : public CCScene
{
public:
	TiledMapScene();

	virtual bool init();

	static CCScene* create();
	void ChangeScene();

	void zoomMapInOut(bool bZoomIn);

private:
	CCLayer *m_pMapLayer;

};

#endif // __TILEDMAPSCENE_H__
#ifndef __HEXAGONMAPLAYER_H__
#define __HEXAGONMAPLAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class HexagonMapLayer : public CCLayer
{
public: 
	// constructor
	HexagonMapLayer();

	// overrides
	virtual void onEnter();
	bool init();
	void registerWithTouchDispatcher();
	bool ccTouchBegan(CCTouch *touch, CCEvent *event);
	void ccTouchEnded(CCTouch *touch, CCEvent *event);
	void ccTouchMoved(CCTouch *touch, CCEvent *event);

	// methods
	void increaseScale(float scaleDiff = 0.1f);
	void decreaseScale(float scaleDiff = 0.1f);
	void scaleTo(float scale);

private:
	void createDudeWithCoordinates(CCPoint location);
	void setViewPointCenter(CCPoint position);
	void setDudePosition(CCPoint position);

	CCPoint pixelToHexagonGrid(CCPoint p);
	//void highlightTile(CCPoint position);
	void moveMapView(CCPoint diff);
	void fixMapPosition();

	CCTMXTiledMap *m_pTiledMap;
	CCTMXLayer	  *m_pBackgroundLayer;

	CCSpriteBatchNode *m_pAnimatedDude;
	CCSprite          *m_pDudeSprite;

	float          m_fScaleFactor;
};

#endif // __HEXAGONMAPLAYER_H__
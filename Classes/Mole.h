#ifndef __MOLE_H__
#define __MOLE_H__

#include "cocos2d.h"
#include "chipmunk_types.h"
#include "cpVect.h"


USING_NS_CC;

class Mole : public CCSprite
{
public:    
	 
	static Mole* create(const std::string& filename);
    virtual void update(float dt);
    void  initialize();

	 void showUp(float dt);
	 void disappear(float dt);
 
	 //bool containsTouchLocation(CCTouch* touch);
    /*CC_SYNTHESIZE(float, distanceMoved_, DistanceMoved);
    CC_SYNTHESIZE(cocos2d::CCPoint, velocity_, Velocity);
    CC_SYNTHESIZE(bool, expired_, Expired);*/
	CC_SYNTHESIZE(float,eachRoundTime_,EachRoundTime);
	CC_SYNTHESIZE(float,eachRoundPassedTime_,EachRoundPassedTime);
	CC_SYNTHESIZE(float,textureWidth_,TextureWidth);
	CC_SYNTHESIZE(float, _aliveTime, AliveTime);
	CC_SYNTHESIZE(cpVect,frame2D,Frame2D);
	CC_SYNTHESIZE(cocos2d::CCRect,visibleRect,VisibleRect);
	
	//CC_SYNTHESIZE(bool, _alive, Alive);
	CC_SYNTHESIZE(bool,showUpFinshed_,ShowUpFinshed);
	cpVect currentFrame2D_;
	float icount_;
	bool _alive;

	bool _update=false;
	void setUpdate(bool isUpdate);
	bool isUpdate();

	void setAlive(bool isAlive);
	bool getAlive();
	virtual bool onTouchBegan(CCTouch* touch, CCEvent* event);
	
	int getRandomNumber();

	int random(int start,int end);
	/** @} */
	
};
#endif // __BULLET_H__
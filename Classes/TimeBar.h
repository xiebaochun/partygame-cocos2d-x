//
//  Bullet.h
//  Asteroids
//
//  Created by Clawoo on 9/18/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef __TIMEBAR_H__
#define __TIMEBAR_H__

#include "cocos2d.h"


class TimeBar : public cocos2d::CCSprite
{
public:    
    virtual void update(float dt);
	static TimeBar* spriteWithFile(const char *pszFileName);
	virtual bool init();

	CC_SYNTHESIZE(bool,running_,Running);
    /*CC_SYNTHESIZE(float, distanceMoved_, DistanceMoved);
    CC_SYNTHESIZE(cocos2d::CCPoint, velocity_, Velocity);
    CC_SYNTHESIZE(bool, expired_, Expired);*/
	CC_SYNTHESIZE(float,eachRoundTime_,EachRoundTime);
	CC_SYNTHESIZE(float,eachRoundPassedTime_,EachRoundPassedTime);
	CC_SYNTHESIZE(float,textureWidth_,TextureWidth);
	// implement the "static node()" method manually
	CREATE_FUNC(TimeBar);
};

#endif // __BULLET_H__
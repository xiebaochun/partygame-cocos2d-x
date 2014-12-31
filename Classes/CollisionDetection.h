//
//  CollisionDetection.h
//  Created by Mudit Jaju on 30/08/13.
//
//  SINGLETON class for checking Pixel Based Collision Detection

#ifndef __CollisionDetection__
#define __CollisionDetection__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class CollisionDetection {
public:
	//Handle for getting the Singleton Object
	static CollisionDetection* GetInstance();
	//Function signature for checking for collision detection spr1, spr2 are the concerned sprites
	//pp is bool, set to true if Pixel Perfection Collision is required. Else set to false
	//_rt is the secondary buffer used in our system
	bool areTheSpritesColliding(CCSprite* spr1, CCSprite* spr2, bool pp, CCRenderTexture* _rt);
private:
	static CollisionDetection* instance;
	CollisionDetection();

	// Values below are all required for openGL shading
	CCGLProgram *glProgram;
	ccColor4B *buffer;
	int uniformColorRed;
	int uniformColorBlue;

};

#endif /* defined(__CollisionDetection__) */
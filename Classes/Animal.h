#ifndef __ANIMAL_H__
#define __ANIMAL_H__

#include "cocos2d.h"


USING_NS_CC;

class Animal : public CCSprite
{
public:    
	 
	static Animal* create(const std::string& filename);
    virtual void update(float dt);
    void  initialize(const std::string& filename);
	float icount_;

	virtual bool onTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void onTouchEnded(CCTouch* touch, CCEvent* event);

	bool isTouched = false;

	CCSprite* outline;

private:
	

};
#endif // __BULLET_H__
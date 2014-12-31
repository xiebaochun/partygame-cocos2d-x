#ifndef __CARD_H__
#define __CARD_H__

#include "cocos2d.h"


USING_NS_CC;


class HoldCard : public Sprite
{
public:

	static HoldCard* create(const std::string& filename);
	//virtual void update(float dt);
	void  initialize();
	//float icount_;
	/*virtual bool onTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void onTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void onTouchEnded(CCTouch* touch, CCEvent* event);
	bool isHolded = false;*/
	bool isHaveCard = false;
private:


};


class Card : public Sprite
{
public:    
	 
	static Card* create(const std::string& filename);
    virtual void update(float dt);
	virtual void setPosition_once(Point &position);
    void  initialize();
	float icount_;
	int index;
	Point targetPosition;
	Point oldPosition;
	//Point originPosition;
	virtual bool onTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void onTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void onTouchEnded(CCTouch* touch, CCEvent* event);
	bool isHolded = false;
	bool isRequiredToChangePlace = false;
	//bool isCollision = false;
private:
	

};
#endif // __BULLET_H__
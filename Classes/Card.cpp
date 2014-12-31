//
//  Card.cpp
//  Card
//
//  Created by juerry on 14/05/05.
//  Copyright 2014 __asiasoft__. All rights reserved.
//
#include "HelloWorldScene.h"
#include "Card.h"
#include "DragScene.h"

USING_NS_CC;

HoldCard* HoldCard::create(const std::string& filename)
{
	HoldCard *sprite = new HoldCard();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->initialize();
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}
void HoldCard::initialize()
{
	this->setScale(0.45);
	this->setAnchorPoint(ccp(0, 0));

	/*auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(false);

	touchListener->onTouchBegan = CC_CALLBACK_2(Card::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(Card::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(Card::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);*/

}


Card* Card::create(const std::string& filename)
{
	Card *sprite = new Card();
    if (sprite && sprite->initWithFile("cards/"+filename+".png"))
    {
		sprite->initialize();
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void Card::initialize()
{        	
	    this->setScale(0.45);
	    this->setAnchorPoint(ccp(0,0));

		auto touchListener = EventListenerTouchOneByOne::create();
	    touchListener->setSwallowTouches(false);
	        
	    touchListener->onTouchBegan = CC_CALLBACK_2(Card::onTouchBegan, this);
		touchListener->onTouchMoved = CC_CALLBACK_2(Card::onTouchMoved, this);
		touchListener->onTouchEnded = CC_CALLBACK_2(Card::onTouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

}
void Card::update(float dt)
{
	
	
}
void Card::setPosition_once(Point &pos)
{
	Sprite::setPosition(pos);
	this->oldPosition = pos;
	//this->originPosition = pos;
}

bool Card::onTouchBegan(CCTouch* touch, CCEvent* event)
{
	//if (m_state != kPlayerStateUngrabbed) return false;
	//if ( !containsTouchLocation(touch) ) return false;//touch on the sprite, then we do something

	//m_state = kPlayerStateGrabbed;
	
	Point locationInNode = this->convertToNodeSpace(touch->getLocation());  
            Size s = this->getContentSize();  
			Rect rect = Rect(0, 0, s.width, s.height);
              
			if (rect.containsPoint(locationInNode) && DragScene::gameState == DragScene::GameState::playing)
            {  
				this->isHolded = true;
				this->setGlobalZOrder(3);
				//this->getParent()->sortAllChildren();
            }  
	return true;
}
void Card::onTouchMoved(CCTouch* touch, CCEvent* event)
{
	//if (m_state != kPlayerStateUngrabbed) return false;
	//if ( !containsTouchLocation(touch) ) return false;//touch on the sprite, then we do something

	//m_state = kPlayerStateGrabbed;
	Point locationInNode = this->convertToNodeSpace(touch->getLocation());
	Size s = this->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);

	if (rect.containsPoint(locationInNode) && DragScene::gameState == DragScene::GameState::playing)
	{
		//this->setPosition(touch->getLocation());
	}
	if (this->isHolded == true)
	{
		this->setPosition(ccp(touch->getLocation().x - s.width / 4, touch->getLocation().y - s.height / 4));
	}
	
}
void Card::onTouchEnded(CCTouch* touch, CCEvent* event)
{
	//if (m_state != kPlayerStateUngrabbed) return false;
	//if ( !containsTouchLocation(touch) ) return false;//touch on the sprite, then we do something

	//m_state = kPlayerStateGrabbed;
	Point locationInNode = this->convertToNodeSpace(touch->getLocation());
	Size s = this->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);

	if (this->isHolded == true||this->isRequiredToChangePlace==true)
	{
		this->runAction(MoveTo::create(0.2, targetPosition));
		this->oldPosition = targetPosition;
	}
	

	if (rect.containsPoint(locationInNode) && DragScene::gameState == DragScene::GameState::playing)
	{
		this->isHolded = false;
	}
	this->isHolded = false;
	this->isRequiredToChangePlace = false;
	this->setGlobalZOrder(2);
	
	



}
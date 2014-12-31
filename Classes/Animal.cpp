//
//  Animal.cpp
//  Animal
//
//  Created by Clawoo on 14/05/05.
//  Copyright 2014 __MyCompanyName__. All rights reserved.
//

#include "Animal.h"
#include "VisionScene.h"

USING_NS_CC;

Animal* Animal::create(const std::string& filename)
{
	Animal *sprite = new Animal();
    if (sprite && sprite->initWithFile(filename+"/answer.png"))
    {
		sprite->initialize(filename);
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}
void Animal::initialize(const std::string& filename)
{
	     
	    outline = CCSprite::create(filename+"/01.png");
		outline->setScale(0.5);
		outline->setPosition(200+CCRANDOM_0_1() * 200, 200+CCRANDOM_0_1() * 200);
		setScale(0.5);

		//this->addChild(outline);

		auto touchListener = EventListenerTouchOneByOne::create();
	    touchListener->setSwallowTouches(false);
	        
	    touchListener->onTouchBegan = CC_CALLBACK_2(Animal::onTouchBegan, this);
		touchListener->onTouchEnded = CC_CALLBACK_2(Animal::onTouchEnded, this);
	
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);


		/*cc_timeval psv;f
		     CCTime::gettimeofdayCocos2d(&psv, NULL);
		     unsigned long int seed = psv.tv_sec * 1000 + psv.tv_usec / 1000;
		     srand(seed);*/

}
void Animal::update(float dt)
{
	
	
}


bool Animal::onTouchBegan(CCTouch* touch, CCEvent* event)
{
	//if (m_state != kPlayerStateUngrabbed) return false;
	//if ( !containsTouchLocation(touch) ) return false;//touch on the sprite, then we do something

	//m_state = kPlayerStateGrabbed;
	Point locationInNode = this->convertToNodeSpace(touch->getLocation());  
            Size s = this->getContentSize();  
            Rect rect = Rect(0, 20, s.width, s.height-20);  
              
			if (rect.containsPoint(locationInNode) && VisionScene::gameState == VisionScene::GameState::playing)
            {  
				CCLOG("enter animal touch begin");
				this->isTouched = true;
				
            }  
	return true;
}
void Animal::onTouchEnded(CCTouch* touch, CCEvent* event)
{
	Point locationInNode = this->convertToNodeSpace(touch->getLocation());
	Size s = this->getContentSize();
	Rect rect = Rect(0, 20, s.width, s.height - 20);

	if (rect.containsPoint(locationInNode) && VisionScene::gameState == VisionScene::GameState::playing)
	{
		//this->setVisible(false);
		
		CCLOG("enter animal touch end");
		if (this->isTouched == true)
		{
			if (this->outline->isVisible())
			{
				VisionScene::isAnswerRight = false;
				auto action = Blink::create(0.3f,5);//blink some times,arguments:time,blink times
				this->outline->runAction(action);

			}
			else
			{
				VisionScene::isAnswerRight = true;
			}
			this->isTouched = false;
			VisionScene::isPrepareNext = true;
		}
		
	}
}
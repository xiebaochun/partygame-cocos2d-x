//
//  Bullet.cpp
//  Asteroids
//
//  Created by Clawoo on 9/18/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Mole.h"
#include "HelloWOrldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Mole* Mole::create(const std::string& filename)
{
	Mole *sprite = new Mole();
    if (sprite && sprite->initWithFile(filename))
    {
		sprite->initialize();
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}
void Mole::initialize()
{
	this->icount_=0;
	this->setAlive(false);
	this->setAliveTime((float)CCRANDOM_0_1() * 2 + 2);
	this->setVisible(false);
	//this->setShowUpFinshed(false);
	this->currentFrame2D_.x=6;
	this->currentFrame2D_.y=0;
	this->setAnchorPoint(ccp(0,0));
	/*this->setEachRoundTime(20);
	this->setEachRoundPassedTime(0);*/
	this->setFrame2D(cpv(7,1));
	this->setTextureWidth(this->getContentSize().width);
	this->setVisibleRect(CCRectMake(0,0,this->getContentSize().width/this->getFrame2D().x,this->getContentSize().height/this->getFrame2D().y));
	this->setVisibleRect(CCRectMake(this->currentFrame2D_.x*this->getVisibleRect().size.width,this->currentFrame2D_.y*this->getVisibleRect().size.height,this->getVisibleRect().size.width,this->getVisibleRect().size.height));
	this->setTextureRect(this->getVisibleRect());
	this->setUpdate(true);
	
		auto touchListener = EventListenerTouchOneByOne::create();
	    touchListener->setSwallowTouches(false);
	        
	    touchListener->onTouchBegan = CC_CALLBACK_2(Mole::onTouchBegan, this);
	
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);


		/*cc_timeval psv;f
		     CCTime::gettimeofdayCocos2d(&psv, NULL);
		     unsigned long int seed = psv.tv_sec * 1000 + psv.tv_usec / 1000;
		     srand(seed);*/

}
void Mole::update(float dt)
{
	if (HelloWorld::gameState == HelloWorld::GameState::playing)
	{
		this->showUp(dt);
		this->disappear(dt);
		if (this->isVisible() == true && this->getAlive() == true)_aliveTime -= dt;
		//if (this->isVisible() == false)_aliveTime += dt;
		//if (getAliveTime() >= 3)this->setAlive(true); 
		if (getAliveTime() <= 0)this->setAlive(false);
		
	}
	
}
void Mole::setUpdate(bool isUpdate)
{
	if (isUpdate)
	{
		if (!_update)this->scheduleUpdate(); _update = isUpdate;
	     
	}
	else
	{
		if (_update)this->unscheduleUpdate(); _update = isUpdate;
	}
}
bool Mole::isUpdate()
{
	return _update;
}
void Mole::showUp(float dt)
{
	if (this->isVisible() == true && this->getAlive() == true && this->getShowUpFinshed() == false && this->currentFrame2D_.x >= 0)
	{
		this->icount_+=dt;
		if(this->icount_>=0.1f)
		{
			this->icount_=0;
			this->currentFrame2D_.x--;
			//this->setVisibleRect(CCRectMake(this->currentFrame2D_.x,this->currentFrame2D_.y,this->getVisibleRect().size.width,this->getVisibleRect().size.height));
		
			if(this->currentFrame2D_.x<=0)
			{
				this->currentFrame2D_.x = 0;

				//this->setAlive(false);
				this->setShowUpFinshed(true);
			   
			}
			this->setVisibleRect(CCRectMake(this->currentFrame2D_.x*this->getVisibleRect().size.width, this->currentFrame2D_.y*this->getVisibleRect().size.height, this->getVisibleRect().size.width, this->getVisibleRect().size.height));
			this->setTextureRect(this->getVisibleRect());
		}
	}
}
void Mole::disappear(float dt)
{
	if (this->isVisible() == true && this->getAlive() == false && this->getShowUpFinshed() == true && this->currentFrame2D_.x <= 6)
	{
		this->icount_+=dt;
		if(this->icount_>=0.1f)
		{
			this->icount_=0;
			this->currentFrame2D_.x++;
			//this->setVisibleRect(CCRectMake(this->currentFrame2D_.x,this->currentFrame2D_.y,this->getVisibleRect().size.width,this->getVisibleRect().size.height));
			this->setVisibleRect(CCRectMake(this->currentFrame2D_.x*this->getVisibleRect().size.width,this->currentFrame2D_.y*this->getVisibleRect().size.height,this->getVisibleRect().size.width,this->getVisibleRect().size.height));
			this->setTextureRect(this->getVisibleRect());
			if(this->currentFrame2D_.x>=6)
			{
				//this->setAlive(true);
				this->setShowUpFinshed(false);
				this->setVisible(false);
			}
		}
	}
}
void Mole::setAlive(bool isAlive)
{
	if (isAlive == true)this->setVisible(true); this->setShowUpFinshed(false); this->setAliveTime((float)CCRANDOM_0_1() * 2 + 2);

	if (isAlive == false)this->setShowUpFinshed(true);// this->setAliveTime(0); 
	_alive = isAlive;
}
bool Mole::getAlive()
{
	return _alive;
}

bool Mole::onTouchBegan(CCTouch* touch, CCEvent* event)
{
	//if (m_state != kPlayerStateUngrabbed) return false;
	//if ( !containsTouchLocation(touch) ) return false;//touch on the sprite, then we do something

	//m_state = kPlayerStateGrabbed;
	Point locationInNode = this->convertToNodeSpace(touch->getLocation());  
            Size s = this->getContentSize();  
            Rect rect = Rect(0, 20, s.width, s.height-20);  
              
			if (rect.containsPoint(locationInNode) && HelloWorld::gameState == HelloWorld::GameState::playing)
            {  
				if (this->isVisible() == true&&this->getAlive()==true)HelloWorld::score++;
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("hit_03.wav", false);
                //this->setColor(Color3B::RED);  
                this->setAlive(false);
				
            }  
	
	//this->setVisible(false);
	return true;
}
int Mole::getRandomNumber(){
	     int randNumber = random(0, 10);
	     return randNumber;
	
}
int Mole::random(int start, int end){
	
		     return CCRANDOM_0_1()*end + start;
	
}

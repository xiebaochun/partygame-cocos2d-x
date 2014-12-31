//
//  Bullet.cpp
//  Asteroids
//
//  Created by Clawoo on 9/18/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "TimeBar.h"

USING_NS_CC;

TimeBar* TimeBar::spriteWithFile(const char *pszFileName)
{
    TimeBar *pobSprite = new TimeBar();
	//TimeBar *pobSprite = TimeBar::create();
	if (pobSprite&& pobSprite->initWithFile(pszFileName))
    {
        //pobSprite->scheduleUpdate();
        //pobSprite->setDistanceMoved(0);
		//pobSprite->setPosition(ccp(640,650));
		pobSprite->init();
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
	return NULL;
}
bool TimeBar::init()
{
	this->setAnchorPoint(ccp(0,0));
	this->setEachRoundTime(60);
	this->setEachRoundPassedTime(0);
	this->setRunning(false);
	this->setTextureWidth(this->getContentSize().width);
	this->scheduleUpdate();
	return true;
}
void TimeBar::update(float dt)
{
	
    //this->setPosition(ccp(this->getPosition().x + velocity_.x, this->getPosition().y + velocity_.y));
    //
    //CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
    //
    //// Increment the distance moved by the velocity vector
    //distanceMoved_ += sqrt(pow(velocity_.x, 2) + pow(velocity_.y, 2));
    // 
    //// Determine if bullet is expired -- check to see if its gone at least half the width of the screen
    //if (distanceMoved_ > windowSize.width / 2)
    //{
    //    expired_ = true;
    //}
    //
    //// If object moves off the bounds of the screen, make it appear on the other side
    //if (this->getPosition().x < 0)
    //{
    //    this->setPosition(ccp(windowSize.width, this->getPosition().y));
    //}
    //else if (this->getPosition().x > windowSize.width)
    //{
    //    this->setPosition(ccp(0, this->getPosition().y));
    //}
    //
    //if (this->getPosition().y < 0)
    //{
    //    this->setPosition(ccp(this->getPosition().x, windowSize.height));
    //}
    //else if (this->getPosition().y > windowSize.height)
    //{
    //    this->setPosition(ccp(this->getPosition().x, 0));
    //}
	if(this->getRunning()==true)
	{
		this->setEachRoundPassedTime(this->getEachRoundPassedTime()+dt);
		if(this->getEachRoundPassedTime()>this->getEachRoundTime())
		{
			
			this->setRunning(false);
			
			//this->setEachRoundPassedTime(0);
		}
		//this->setTextureRect(CCRectMake(0,0,this->getTextureWidth()*(float)this->getEachRoundTime(),this->getContentSize().height));
		this->setTextureRect(CCRectMake(0,0,this->getTextureWidth()*(1.0f-this->getEachRoundPassedTime()/this->getEachRoundTime()),this->getContentSize().height));
		}
	   
	}
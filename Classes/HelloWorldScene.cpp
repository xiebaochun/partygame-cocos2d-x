#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include  "StartScene.h"

USING_NS_CC;

int HelloWorld::score = 0;
HelloWorld::GameState HelloWorld::gameState= GameState::start;
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);
	//scene->autorelease();
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.1);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bg.wav",true);
	
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

   
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    //this->addChild(menu, 1);





    /////////////////////////////
    // 3. add your codes below...
	//******************************************load menu *****************************************
	auto startItem = MenuItemImage::create("GameStart.png", "GameStart.png", CC_CALLBACK_1(HelloWorld::menuCallBack, this));
	startMenu = Menu::create(startItem, NULL);
	startMenu->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(startMenu, 2);

	auto replayItem = MenuItemImage::create("replay.png", "replay1.png", CC_CALLBACK_1(HelloWorld::menuCallBack, this));
	replayMenu = Menu::create(replayItem, NULL);
	replayMenu->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	replayMenu->setVisible(false);
	this->addChild(replayMenu, 2);

	auto passItem = MenuItemImage::create("Continue.png", "Continue1.png", CC_CALLBACK_1(HelloWorld::menuCallBack, this));
	passMenu = Menu::create(passItem, NULL);
	passMenu->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	passMenu->setVisible(false);
	this->addChild(passMenu, 2);

	auto exitItem = MenuItemImage::create("game_b_exit.png", "game_b_exit.png", CC_CALLBACK_1(HelloWorld::menuCallBack, this));
	exitMenu = Menu::create(exitItem, NULL);
	exitMenu->setPosition(visibleSize.width - exitItem->getContentSize().width / 2-13, visibleSize.height - exitItem->getContentSize().height / 2-1);
	exitMenu->setVisible(true);
	this->addChild(exitMenu, 2);

	//************************************************************ add keyBoard listener
	auto keyBoardListener = EventListenerKeyboard::create();
	keyBoardListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::keyPressed,this);
	keyBoardListener->onKeyReleased = CC_CALLBACK_2(HelloWorld::keyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyBoardListener, this);



    // add a label shows "Hello World"
    // create and initialize a label
 
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	sprite->setVisible(false);
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
	//************************************ Sprite **************************************
    // add "HelloWorld" splash screen"
    //CCSprite* pSprite = CCSprite::create("HelloWorld.png");
	CCSprite* pSprite = CCSprite::create("bg_c.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);

	
	CCSprite* spBackground_01=CCSprite::create("bg1.png");
	spBackground_01->setAnchorPoint(ccp(0,0));
	spBackground_01->setPosition(ccp(origin.x,origin.y));
	//spBackground_01->setScale(1);
	spBackground_01->setVisible(false);
	this->addChild(spBackground_01,0);

	spBackground_02=CCSprite::create("bg2.png");
	spBackground_02->setAnchorPoint(ccp(0,0));
	spBackground_02->setVisible(true);
	//spBackground_01->setPosition(ccp(640,384));
	this->addChild(spBackground_02,0);

	spBackground_03=CCSprite::create("bg3.png");
	spBackground_03->setAnchorPoint(ccp(0,0));
	spBackground_03->setVisible(false);
	//spBackground_01->setPosition(ccp(640,384));
	this->addChild(spBackground_03,0);
	
	CCSprite* stateBar=CCSprite::create("StateBar.png");
	//stateBar->setAnchorPoint(ccp(0.5,0));
	stateBar->setVisible(true);
	CCPoint STATE_BAR_POSITION=ccp(visibleSize.width/2 + origin.x,visibleSize.height-stateBar->getContentSize().height/2);
	stateBar->setPosition(STATE_BAR_POSITION);
	//stateBar->setScale(1.5f);
	//stateBar->setTextureRect(CCRectMake(0,0,300,200));
	this->addChild(stateBar,1);

	//********************************** TimeBar **********************************
	_timeBar=(TimeBar*)TimeBar::spriteWithFile("TimeBar.png");
	_timeBar->setPosition(ccp(visibleSize.width/2-_timeBar->getTextureWidth()/2+27,613));
	//timeBar_->setEachRoundTime(20);
	//timeBar_->setTextureRect(CCRectMake(0,0,400,timeBar_->getContentSize().height));
	this->addChild(_timeBar,2);

	//************************************ Label **************************************
	int width=visibleSize.width;
	int height=visibleSize.height;
	CCString* ns=CCString::createWithFormat("%d*%d origin:%d*%d",width,height,(int)origin.x,(int)origin.y);

	 pLabel = CCLabelTTF::create(ns->getCString(), "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));
	pLabel->setColor(ccc3(0,0,0));
    // add the label as a child to this layer
    this->addChild(pLabel, 5);

	scoreLabel=CCLabelTTF::create("1", "Arial", 36);
	scoreLabel->setPosition(ccp(260,690));
	scoreLabel->setColor(ccc3(0,0,0));
	this->addChild(scoreLabel,2);

    stageLabel=CCLabelTTF::create("1", "Arial", 36);
	stageLabel->setPosition(ccp(630,690));
	stageLabel->setColor(ccc3(0,0,0));
	this->addChild(stageLabel,2);

	targetLabel=CCLabelTTF::create("1", "Arial", 36);
	targetLabel->setPosition(ccp(960,690));
	targetLabel->setColor(ccc3(0,0,0));
	this->addChild(targetLabel,2);
	



	//*********************************************************load mole ***************************************************
	mole = Mole::create("hit_2.png");
	mole->setPosition(ccp(mole->getContentSize().width / 2, mole->getContentSize().height / 2));
	//this->addChild(mole, 1);

	molePositions = CCPointArray::create(9);
	for (int i = 0; i < 9; i++)
	{
		//CCPoint point =ccp(0, 0);
		molePositions->addControlPoint(ccp(185 + 380 * (i % 3), 360 - 150 * (i / 3)));
	}
	for (int i = 0; i < 9; i++)
	{
		Mole* mole;
		i % 2 == 1 ?mole = Mole::create("hit_1.png"):mole = Mole::create("hit_3.png");
		moles.pushBack(mole);
		mole_crabs[i] = mole;
		if (i > 5)mole->setUpdate(false);
		//mole->setPosition(ccp(molePositions->getControlPointAtIndex(i).x-16, molePositions->getControlPointAtIndex(i).y));
		//mole->unscheduleUpdate();
		this->addChild(mole,1);
	}

	for (int i = 0; i < 9; i++)
	{
		Mole* mole = Mole::create("hit_2.png");
		moles.pushBack(mole);
		mole_cutes[i] = mole;
		//mole->setVisible(true);if mole >5 then enable the mole who index more more than 5
		if (i > 5)mole->setUpdate(false);
		//mole->setPosition(molePositions->getControlPointAtIndex(i));
		this->addChild(mole);
	}

	//moles.at(0)->scheduleUpdate();
	//moles.at(0)->scheduleUpdate();
	//schedule update
	this->scheduleUpdate();

    return true;
}
void HelloWorld::update(float dt)
{
	currentKeyState_Up = KeyState_Up;

	if (currentKeyState_Up== keyState::pressed&&preKeyState_Up == keyState::released)
	{	
		iCount++;
		//CCLog("hello this a up arrow!!!!!!!");
		if (iCount % 2 == 1)
		{
			mole->setAlive(false);
			for (Mole* mole : moles)
			{
				mole->setAlive(false);
			}
		}
		else
		{
			mole->setAlive(true);;
			for (Mole* mole : moles)
			{
				mole->setAlive(true);
			}
		}
		//mole->setColor(Color3B::RED);
		//mole->setVisible(false);
		//bool isvisible = mole->isVisible();
		//spBackground_02->setVisible(false);
	}
	preKeyState_Up = currentKeyState_Up;
	
	
	stateBarUpdate();
	
	switch (gameState)
	{
		case start:
			break;

           
		case playing:
			if (_timeBar->getRunning() == false&&passMenu->isVisible()==false&&replayMenu->isVisible()==false)
			{
				gameState = GameState::start;
				if (HelloWorld::score >= target)
				{
					passMenu->setVisible(true);
					stage++;
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sccess.wav", false);
				}
				else
				{
					replayMenu->setVisible(true);
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("prompt.wav", false);
				}
				
			}
			 
			generate_alta_time -= dt;
			if (generate_alta_time <= 0)
			{
				molePositions = CCPointArray::create(9);
				for (int i = 0; i < 9; i++)
				{
					//CCPoint point =ccp(0, 0);
					molePositions->addControlPoint(ccp(185 + 380 * (i % 3), 360 - 150 * (i / 3)));
				}
				generate_alta_time = 1;
				CCPoint p;
				int countOut = 0;
				while (true)
				{
					countOut++;
					if (countOut >= 100)break;
					int index = (int)(CCRANDOM_0_1() * holeCount);
					
					CCString* s = CCString::createWithFormat("the random number:%d", index);
					p = ccp(molePositions->getControlPointAtIndex(index).x, molePositions->getControlPointAtIndex(index).y);
					if (checkPosition(p))
					{
						//CCLog(s->getCString());
						if ((int)(CCRANDOM_0_1() * 6) % 2 == 1)
						{
							for (Mole* mole:mole_crabs)
							{				
								if (mole->isVisible() == false)
								{
									mole->setAlive(true); 
									mole->setPosition(ccp(p.x - 16, p.y)); 
									mole->setAliveTime((float)CCRANDOM_0_1() * 2 + 2);  
									break;		
								}
							}
						}
						else
						{
							for (Mole* mole:mole_cutes)
							{
								if (mole->isVisible() == false)
								{
									mole->setAlive(true);
									mole->setPosition(p);
									mole->setAliveTime((float)CCRANDOM_0_1() * 2 + 2);
									break;
								}
							}
						}
					    break;
					}
				}
				//CCString* s = CCString::createWithFormat("the random number:%d", (int)(CCRANDOM_0_1() * 6));
				//CCLog(s->getCString());
			}
			break;

		case over:
			break;
	}


}
//deal with the keyboard keys press Envent 
void HelloWorld::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		KeyState_Up = keyState::pressed;
		//mole->setAlive(false);
		CCLog("hello this a up arrow!!!!!!!");
	}

	//if pressed the escape key then close the game application
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		Director::sharedDirector()->end();
	}
}
void HelloWorld::keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	
	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		KeyState_Up = keyState::released;
		//mole->setColor(Color3B::RED);
		//CCLog("hello this a up arrow!!!!!!!");
		
	}
	
}

void HelloWorld::menuCallBack(cocos2d::Ref* pSender)
{
	CCNode* node = (CCNode*)pSender;
	//node->setVisible(false);
	node->getParent()->setVisible(false);
	//node->setVisible(false);
	CCLog(node->getParent()->isVisible() ? "Node visible :true" : "Node visible :false");
	if (node->getParent() == replayMenu || node->getParent() == passMenu)
	{
		_timeBar->setRunning(true);
		_timeBar->setEachRoundPassedTime(0);
		score = 0;
		target += 3;
		HelloWorld::gameState = HelloWorld::GameState::playing;

		if (node->getParent() == passMenu)
		{
			if (stage>=3)
			{
				holeCount = 9;
				spBackground_02->setVisible(false);
				spBackground_03->setVisible(true);
				for (Mole* mole : mole_cutes)
				{
					mole->setUpdate(true);
				}
			}
			
		}
	}
	if (node->getParent() == startMenu)
	{
		HelloWorld::gameState = HelloWorld::GameState::playing;
		_timeBar->setRunning(true);
		CCLog("start Menu call back!");
	}
	if (node->getParent() == exitMenu)
	{
		
		CCTransitionScene* transition = CCTransitionFlipAngular::create(1.2f, StartScene::createScene());
		CCDirector::sharedDirector()->replaceScene(transition);
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	    HelloWorld::gameState = GameState::start;
		score = 0;
	}
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("click.wav", false);
	//CCSprite* sprite = (CCPrite)
}
void HelloWorld::stateBarUpdate()
{
	CCString* s = CCString::createWithFormat("%d", (int)score);
	scoreLabel->setString(s->getCString());

	 s = CCString::createWithFormat("%d", (int)stage);
	stageLabel->setString(s->getCString());

	 s = CCString::createWithFormat("%d", (int)target);
	targetLabel->setString(s->getCString());
}
bool HelloWorld::checkPosition(CCPoint p)
{
	for (Mole* mole : mole_crabs)
	{
		if (p == ccp(mole->getPosition().x + 16, mole->getPosition().y)&&mole->isVisible()==true)
		{
			return false;
		}
	}
	for (Mole* mole : mole_cutes)
	{
		if (p == mole->getPosition()&& mole->isVisible() == true)
		{
			return false;
		}
	}
	return true;
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

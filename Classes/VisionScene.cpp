#include "VisionScene.h"
#include "StartScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;

int VisionScene::score = 0;
bool VisionScene::isPrepareNext = false;
bool VisionScene::isAnswerRight = NULL;
VisionScene::GameState VisionScene::gameState = start;

Scene* VisionScene::createScene()
{
	CCLOG("into create VisionScene");
	auto scene=Scene::create();
	auto layer=VisionScene::create();
	scene->addChild(layer);
	//scene->autorelease();
	CCLOG("out create VisionScene");
	return scene;
}
bool VisionScene::init()
{
	CCLOG("into init VisionScene");
	if(!Layer::init())
	{
		return false;
	}
    visibleSize=Director::getInstance()->getVisibleSize();
	Point origin=Director::getInstance()->getVisibleOrigin();

	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bg_start.wav", true);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bg.wav", true);

	CCSprite* spBackground_01 = CCSprite::create("bg_c.png");
	spBackground_01->setAnchorPoint(ccp(0, 0));
	spBackground_01->setPosition(ccp(origin.x, origin.y));
	//spBackground_01->setScale(1);
	//spBackground_01->setVisible(false);
	this->addChild(spBackground_01, 0);

	CCSprite* stateBar = CCSprite::create("StateBar.png");
	//stateBar->setAnchorPoint(ccp(0.5,0));
	stateBar->setVisible(true);
	CCPoint STATE_BAR_POSITION = ccp(visibleSize.width / 2 + origin.x, visibleSize.height - stateBar->getContentSize().height / 2);
	stateBar->setPosition(STATE_BAR_POSITION);
	//stateBar->setScale(1.5f);
	//stateBar->setTextureRect(CCRectMake(0,0,300,200));
	this->addChild(stateBar, 1);

	//******************************************load menu *****************************************
	CCLOG("into create VisionScene startItem");
	auto startItem = MenuItemImage::create("GameStart.png", "GameStart.png", CC_CALLBACK_1(VisionScene::menuCallBack, this));
	startMenu = Menu::create(startItem, NULL);
	startMenu->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(startMenu, 2);
	CCLOG("into create VisionScene replayItem");
	auto replayItem = MenuItemImage::create("replay.png", "replay1.png", CC_CALLBACK_1(VisionScene::menuCallBack, this));
	replayMenu = Menu::create(replayItem, NULL);
	replayMenu->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	replayMenu->setVisible(false);
	this->addChild(replayMenu, 2);
	CCLOG("into create VisionScene passItem");
	auto passItem = MenuItemImage::create("Continue.png", "Continue1.png", CC_CALLBACK_1(VisionScene::menuCallBack, this));
	passMenu = Menu::create(passItem, NULL);
	passMenu->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	passMenu->setVisible(false);
	this->addChild(passMenu, 2);
	CCLOG("into create VisionScene exitItem");
	auto exitItem = MenuItemImage::create("game_b_exit.png", "game_b_exit.png", CC_CALLBACK_1(VisionScene::menuCallBack, this));
	exitMenu = Menu::create(exitItem, NULL);
	exitMenu->setPosition(visibleSize.width - exitItem->getContentSize().width / 2 - 13, visibleSize.height - exitItem->getContentSize().height / 2 - 1);
	exitMenu->setVisible(true);
	this->addChild(exitMenu, 2);
	CCLOG("into create VisionScene helpItem");
	auto helpItem = MenuItemImage::create("help.png", "help1.png", CC_CALLBACK_1(VisionScene::menuCallBack, this));
	helpMenu = Menu::create(helpItem, NULL);
	helpMenu->setPosition(visibleSize.width - helpItem->getContentSize().width/2,helpItem->getContentSize().height/2);
	helpMenu->setVisible(true);
	this->addChild(helpMenu, 2);
	CCLOG("into create VisionScene gameInfoItem");
	auto gameInfoItem = MenuItemImage::create("layout-04.png", "layout-04.png", CC_CALLBACK_1(VisionScene::menuCallBack, this));
	gameInfoMenu = Menu::create(gameInfoItem, NULL);
	gameInfoMenu->setPosition(3*visibleSize.width / 2, 3*visibleSize.height / 2);
	//gameInfoMenu->setVisible(false);
	this->addChild(gameInfoMenu, 5);
	

	//********************************** TimeBar **********************************
	CCLOG("into create VisionScene _timeBar");
	_timeBar = (TimeBar*)TimeBar::spriteWithFile("TimeBar.png");
	_timeBar->setPosition(ccp(visibleSize.width / 2 - _timeBar->getTextureWidth() / 2 + 27, 613));
	//timeBar_->setEachRoundTime(20);
	//timeBar_->setTextureRect(CCRectMake(0,0,400,timeBar_->getContentSize().height));
	this->addChild(_timeBar, 2);

	CCLOG("into create VisionScene scoreLabel");
	scoreLabel = CCLabelTTF::create("1", "Arial", 36);
	scoreLabel->setPosition(ccp(260, 690));
	scoreLabel->setColor(ccc3(0, 0, 0));
	this->addChild(scoreLabel, 2);
	CCLOG("into create VisionScene stageLabel");
	stageLabel = CCLabelTTF::create("1", "Arial", 36);
	stageLabel->setPosition(ccp(630, 690));
	stageLabel->setColor(ccc3(0, 0, 0));
	this->addChild(stageLabel, 2);
	CCLOG("into create VisionScene targetLabel");
	targetLabel = CCLabelTTF::create("1", "Arial", 36);
	targetLabel->setPosition(ccp(960, 690));
	targetLabel->setColor(ccc3(0, 0, 0));
	this->addChild(targetLabel, 2);

	//********************************** initialize the sprites **********************************
	answerShow = Sprite::create("answerShow.png");
	showAnswerTextTureHeight = answerShow->getTextureRect().size.height;
	showAnswerTextTureWidth = answerShow->getTextureRect().size.width;
	answerShow->setTextureRect(CCRect(0, showAnswerTextTureHeight / 2, showAnswerTextTureWidth, showAnswerTextTureHeight/ 2));
	answerShow->setPosition(ccp(visibleSize.width / 2, visibleSize.height/ 2));
	answerShow->setVisible(false);
	this->addChild(answerShow,2);

	//********************************** initialize the animals **********************************

	/*animal = Animal::create("vision/ab-01");
	animal->setPosition(200, 200);
	animal->outline->setPosition(ccp(500, 500));
	this->addChild(animal, 3);
	this->addChild(animal->outline, 1);*/

	


	this->scheduleUpdate();
	CCLOG("out init VisionScene");
	return true;
}

void VisionScene::update(float dt)
{
	stateBarUpdate();

	switch (gameState)
	{
	case start:
		break;

	case playing:
		
		if (isPrepareNext)
		{
			
			if (VisionScene::isAnswerRight == true)
			{
				score++;
				answerShow->setTextureRect(CCRect(0, 0, showAnswerTextTureWidth, showAnswerTextTureHeight / 2));
			}
			else{
				answerShow->setTextureRect(CCRect(0, showAnswerTextTureHeight / 2, showAnswerTextTureWidth, showAnswerTextTureHeight / 2));
			}
			answerShow->setVisible(true);
			//CCLOG("enter answerShow action");
			auto action = Sequence::create(FadeIn::create(0.3f), FadeOut::create(0.3f), CallFuncN::create(CC_CALLBACK_1(VisionScene::answerShowCallBack, this)), NULL);
			answerShow->runAction(action);
			isAnswerRight = NULL;
			isPrepareNext = false;
			
		}
		
		break;
	case over:
		break;
	}

}
void VisionScene::answerShowCallBack(cocos2d::Ref* pSender)
{
	CCLOG("enter answerShow callback");
	//answerShow->runAction(MoveBy::create(0.2f,Point(visibleSize.width/2,visibleSize.height/2)));
	prepareNextGroupAnimal();
}
void VisionScene::menuCallBack(cocos2d::Ref* pSender)
{
	CCNode* node = (CCNode*)pSender;
	
	if (node->getParent() == exitMenu)
	{
		CCScene* scene = StartScene::createScene();
		CCTransitionScene* transition = CCTransitionFlipAngular::create(1.2f, scene);
		CCDirector::sharedDirector()->replaceScene(transition);
		node->getParent()->setVisible(false);
	}
	if (node->getParent() == startMenu)
	{
		prepareNextGroupAnimal();
		//prepareNextGroupAnimal();
		gameState = playing;
		_timeBar->setRunning(true);
		node->getParent()->setVisible(false);
		
	}
	if (node->getParent() == replayMenu)
	{
		prepareNextGroupAnimal();
		node->getParent()->setVisible(false);
	}
	if (node->getParent() == passMenu)
	{
		prepareNextGroupAnimal();
		node->getParent()->setVisible(false);
	}
	if (node->getParent() == helpMenu)
	{
		//gameInfoMenu->setVisible(true);
		auto action = JumpTo::create(1,Point(visibleSize.width/2,visibleSize.height/2),50,5);
		gameInfoMenu->runAction(action);
		
		CCLOG("enter helpMenu Click");
		gameInfoMenu->isVisible() ? log("gameInfoMenu visible:true") : log("gameInfoMenu visible:false");
		node->getParent()->setVisible(false);
		_timeBar->setRunning(false);
	}
	
	if (node->getParent() == gameInfoMenu)
	{
		auto action1 = JumpTo::create(1, Point(3*visibleSize.width / 2, 3*visibleSize.height / 2), 50, 5);
		auto action = Sequence::create(action1, CallFuncN::create(CC_CALLBACK_1(VisionScene::GameInfoMenuCallBack, this)), NULL);
	    gameInfoMenu->runAction(action);
		//CCLOG("enter gameInfoMenu click");
		helpMenu->setVisible(true);

	}

}
void VisionScene::GameInfoMenuCallBack(cocos2d::Ref* pSender)
{
	_timeBar->setRunning(true);
	CCLOG("enter gameInfoMenu Call Back");
	gameInfoMenu->isVisible() ? log("gameInfoMenu visible:true") : log("gameInfoMenu visible:false");
}
void VisionScene::stateBarUpdate()
{
	CCString* s = CCString::createWithFormat("%d", (int)score);
	scoreLabel->setString(s->getCString());

	s = CCString::createWithFormat("%d", (int)stage);
	stageLabel->setString(s->getCString());

	s = CCString::createWithFormat("%d", (int)target);
	targetLabel->setString(s->getCString());
}
void VisionScene::prepareNextGroupAnimal()
{
	if (!animals.empty())
	{
		/*Vector<Animal*>::iterator iter;

		for (iter = animals.begin(); iter != animals.end(); ++iter)
		{
			Animal* temp = *iter;

			this->removeChild(temp);

		}*/
		for (auto iter : animals)
		{
			this->removeChild(iter);
			this->removeChild(iter->outline);
		}
		animals.clear();
	}
	int unvisibleIndex = CCRANDOM_0_1() * 4;

	std::vector<int> indexContainer;
	for (int i = 0; i < 4; i++)
	{
		CCInteger* index = 0;
		int counter = 0;
		
		while (true)
		{

			index = CCInteger::create(CCRANDOM_0_1() * 21 + 1);
			CCString* ns = CCString::createWithFormat("the index:%d", (int)index->getValue());
			//CCLOG(ns->getCString());
			counter++;
			if (counter >= 50)
			{
				counter = 0;
				//break;
			}
			if (std::find(indexContainer.begin(), indexContainer.end(), index->getValue()) == indexContainer.end())
			{
				indexContainer.push_back(index->getValue());
				break;
			}
		}

		CCString* filePath;
		//int num = index->getValue();
		//CCString* filePath = CCString::createWithFormat("vision/ab-0%d", (int)index->getValue());
		if (index->getValue() < 10)
		{
			filePath = CCString::createWithFormat("vision/ab-0%d", (int)index->getValue());
		}
		else
		{
			filePath = CCString::createWithFormat("vision/ab-%d", (int)index->getValue());
		}
		//CCLOG(filePath->getCString());
		//Animal* animal = NULL;

		Animal* animal = Animal::create(filePath->getCString());
		animal->setPosition(780 + 300 * (i % 2), 430 - 250 * (i / 2));
		//animal->addChild(animal->outline);
		animal->outline->setPosition(animal->outline->getPosition());
		animals.pushBack(animal);
		this->addChild(animal->outline);
		this->addChild(animal, 1);
		//this->addChild(animal->outline, 1);
		if (i == unvisibleIndex)
		{
			animal->outline->setVisible(false);
		}
	}
}

 VisionScene::~VisionScene()
{
	   //CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}
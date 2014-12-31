#include "DragScene.h"
#include "StartScene.h"
#include "SimpleAudioEngine.h"
#include "CXmlStream.h"
#include "CollisionDetection.h"

USING_NS_CC;

int DragScene::score = 0;

DragScene::GameState DragScene::gameState = start;

Scene* DragScene::createScene()
{
	auto scene = Scene::create();
	auto layer = DragScene::create();
	scene->addChild(layer);
	//scene->autorelease();
	return scene;
}
bool DragScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bg_start.wav", true);
	DragScene::score = 0;
	DragScene::gameState = start;


	CCSprite* spBackground_01 = CCSprite::create("bg_b.png");
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
	auto startItem = MenuItemImage::create("GameStart.png", "GameStart.png", CC_CALLBACK_1(DragScene::menuCallBack, this));
	startMenu = Menu::create(startItem, NULL);
	startMenu->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(startMenu, menulayerIndex+1);

	auto replayItem = MenuItemImage::create("replay.png", "replay1.png", CC_CALLBACK_1(DragScene::menuCallBack, this));
	replayMenu = Menu::create(replayItem, NULL);
	replayMenu->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	replayMenu->setVisible(false);
	this->addChild(replayMenu, menulayerIndex);

	auto passItem = MenuItemImage::create("Continue.png", "Continue1.png", CC_CALLBACK_1(DragScene::menuCallBack, this));
	passMenu = Menu::create(passItem, NULL);
	passMenu->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	passMenu->setVisible(false);
	this->addChild(passMenu, menulayerIndex);

	auto exitItem = MenuItemImage::create("game_b_exit.png", "game_b_exit.png", CC_CALLBACK_1(DragScene::menuCallBack, this));
	exitMenu = Menu::create(exitItem, NULL);
	exitMenu->setPosition(visibleSize.width - exitItem->getContentSize().width / 2 - 13, visibleSize.height - exitItem->getContentSize().height / 2 - 1);
	exitMenu->setVisible(true);
	this->addChild(exitMenu, menulayerIndex);

	auto confirmItem = MenuItemImage::create("confirm.png", "confirm.png", CC_CALLBACK_1(DragScene::menuCallBack, this));
	confirmItem->setScale(0.5);
	confirmMenu = Menu::create(confirmItem, NULL);
	confirmMenu->setPosition(visibleSize.width - confirmItem->getContentSize().width/2+50, confirmItem->getContentSize().height / 2 - 36);
	confirmMenu->setVisible(true);
	this->addChild(confirmMenu, menulayerIndex);

	//********************************** TimeBar **********************************
	_timeBar = (TimeBar*)TimeBar::spriteWithFile("TimeBar.png");
	_timeBar->setPosition(ccp(visibleSize.width / 2 - _timeBar->getTextureWidth() / 2 + 27, 613));
	//timeBar_->setEachRoundTime(20);
	//timeBar_->setTextureRect(CCRectMake(0,0,400,timeBar_->getContentSize().height));
	this->addChild(_timeBar, menulayerIndex);

	//********************************** label **********************************
	scoreLabel = CCLabelTTF::create("0", "Arial", 36);
	scoreLabel->setPosition(ccp(260, 690));
	scoreLabel->setColor(ccc3(0, 0, 0));
	this->addChild(scoreLabel, 2);

	stageLabel = CCLabelTTF::create("1", "Arial", 36);
	stageLabel->setPosition(ccp(630, 690));
	stageLabel->setColor(ccc3(0, 0, 0));
	this->addChild(stageLabel, 2);

	targetLabel = CCLabelTTF::create("1", "Arial", 36);
	targetLabel->setPosition(ccp(960, 690));
	targetLabel->setColor(ccc3(0, 0, 0));
	this->addChild(targetLabel, 2);

	//********************************** initialize the question label **********************************
	questionLabel = CCLabelTTF::create(CXmlStream::GetStringByKeyFromFile("question2.xml","question_01"), "Arial", 36);
	questionLabel->setAnchorPoint(ccp(0,1));
	questionLabel->setPosition(ccp(70, 500));
	questionLabel->setHorizontalAlignment(TextHAlignment::LEFT);
	questionLabel->setDimensions(CCSize(300, 300));
	questionLabel->setColor(ccc3(0, 0, 0));
	this->addChild(questionLabel, 2);

	//********************************** load cards an define the cards` positions **********************************
	for (int cardIndex = 1; cardIndex < 6; cardIndex++)
	{
		CCString* path = CCString::createWithFormat("red-%d", cardIndex);
		redCards.pushBack(Card::create(CCString::createWithFormat("red-%d", cardIndex)->getCString()));
		redCards.at(cardIndex - 1)->index = cardIndex;
		blueCards.pushBack(Card::create(CCString::createWithFormat("blue-%d", cardIndex)->getCString()));
		blueCards.at(cardIndex - 1)->index = cardIndex;
		greenCards.pushBack(Card::create(CCString::createWithFormat("green-%d", cardIndex)->getCString()));
		greenCards.at(cardIndex - 1)->index = cardIndex;
	}
	for (int i = 0; i < 5; i++)
	{
		holdCards.pushBack(HoldCard::create("answer_frame.png"));
		holdCards.at(i)->setVisible(false);
	}
	cards[0] = redCards;
	cards[1] = blueCards;
	cards[2] = greenCards;

	for (int i = 0; i < 10; i++)
	{
		Point point = ccp(500 + (i % 5) * 150, 260 - (i / 5) * 150);
		cardPositions[i] = point;

	}

	//********************************** initialize the sprites **********************************
	answerShow = Sprite::create("answerShow.png");
	showAnswerTextTureHeight = answerShow->getTextureRect().size.height;
	showAnswerTextTureWidth = answerShow->getTextureRect().size.width;
	answerShow->setTextureRect(CCRect(0, showAnswerTextTureHeight / 2, showAnswerTextTureWidth, showAnswerTextTureHeight / 2));
	answerShow->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	answerShow->setVisible(false);
	this->addChild(answerShow, 15);

	//easyQuestion = new CXmlStream("question1.xml");//deprecated

	//sortQuestion = new CXmlStream("question2.xml");//deprecated

	this->scheduleUpdate();
	//this->schedule(schedule_selector(DragScene::collideDetect), 10.0f);
	_rt = CCRenderTexture::create(visibleSize.width * 2, visibleSize.height * 2);
	_rt->setPosition(ccp(visibleSize.width, visibleSize.height));
	_rt->retain();
	_rt->setVisible(false);

	return true;
}
//game main update & main logic
void DragScene::update(float dt)
{
	
	
	stateBarUpdate();
	switch (gameState)
	{
	case start:
		break;


	case playing:
		if (_timeBar->getRunning() == false && passMenu->isVisible() == false && replayMenu->isVisible() == false)
		{
			for (auto card : cardContainer)
			{
				this->reorderChild(card, 2);

			}
			gameState = GameState::start;
			if (score >= target)
			{
				passMenu->setVisible(true);
				this->reorderChild(passMenu, 20);
				if(stage<5)stage++;
				target++;
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sccess.wav", false);
			}
			else
			{
				replayMenu->setVisible(true);
				this->reorderChild(replayMenu, 20);
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("prompt.wav", false);
			}
			
		}
		
		collideDetect();
		

		break;

	case over:
		break;
	default:
		break;
	}

	
}
void DragScene::menuCallBack(cocos2d::Ref* pSender)
{
	CCNode* node = (CCNode*)pSender;
	

	if (node->getParent() == exitMenu)
	{
		CCTransitionScene* transition = CCTransitionFlipAngular::create(1.2f, StartScene::createScene());
		CCDirector::sharedDirector()->replaceScene(transition);
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
		node->getParent()->setVisible(false);
	}
	if (node->getParent() == replayMenu || node->getParent() == passMenu)
	{
		//CCLOG("into replayMenu");
		isPrepareNext = true;
		_timeBar->setEachRoundPassedTime(0);
		_timeBar->setRunning(true);

		gameState = playing;
		prepareNextGroupCards();
		
		node->getParent()->setVisible(false);
		//CCLOG("into replayMenu");
	}
	if (node->getParent() == startMenu)
	{
		   //CCLOG("into start menu");
			isPrepareNext = true;			
			prepareNextGroupCards();
			_timeBar->setRunning(true);
			gameState = playing;
			node->getParent()->setVisible(false);
			//CCLOG("out start menu");
	}
	if (node->getParent() == confirmMenu)
	{
		answerShow->setGlobalZOrder(11);
		confirmMenu->setGlobalZOrder(20);
		if (checkAnswer())
		{	
			score++;
			answerShow->setTextureRect(CCRect(0, 0, showAnswerTextTureWidth, showAnswerTextTureHeight / 2));
			
			answerShow->setVisible(true);
			//CCLOG("enter answerShow action");
			auto action = Sequence::create(FadeIn::create(0.3f), FadeOut::create(0.3f), CallFuncN::create(CC_CALLBACK_1(DragScene::answerShowCallBack, this)), NULL);
			answerShow->runAction(action);
			
		}
		else{
			answerShow->setTextureRect(CCRect(0, showAnswerTextTureHeight / 2, showAnswerTextTureWidth, showAnswerTextTureHeight / 2));
			answerShow->setVisible(true);
			//CCLOG("enter answerShow action");
			auto action = Sequence::create(FadeIn::create(0.3f), FadeOut::create(0.3f), NULL);
			answerShow->runAction(action);
		}
		
	}
}
void DragScene::answerShowCallBack(cocos2d::Ref* pSender)
{
	prepareNextGroupCards();
}
bool DragScene::checkAnswer()
{
	bool isFindCards = false;
	int i = 0;
	Vector<Card*> inHoldCardContainer;//this container placed the answerCards in hold place
	///////////////////////////////////check is is all holdCards have holded card///////////////////////////////////////
	for (auto holdCard : holdCards)
	{
		if (holdCard->isVisible() == true)
		{
			/*i++;
			CCString* s = CCString::createWithFormat("-------check------%d",i);
			CCLOG(s->getCString());*/
			for (auto answerCard : cardContainer)
			{
				if (answerCard->isVisible() == true)
				{
					/*i++;
					CCString* s = CCString::createWithFormat("-------check------%d", i);
					CCLOG(s->getCString());*/
					if (checkCardsCollision(holdCard, answerCard))
					{
						isFindCards = true;
						inHoldCardContainer.pushBack(answerCard);
						break;
					}
				}
				
			}
			/*isFindCards ? CCLOG("isFindCards=true") : CCLOG("isFindCards=fasle");*/
			if (isFindCards == false){
				return false;
			}
			else{
				isFindCards = false;
			}
			
		}

		
	}
	//if (mode == 0)CCLOG("mode=0");
	//if (mode == 1)CCLOG("mode=1");
	////////////////////////////////////////according to mode to check is answer right////////////////////
	if (mode == 0||mode==1)
	{
		switch (questionIndex)
		{
		case 1:
			for (auto card : inHoldCardContainer)
			{
				if (!redCards.contains(card))
				{
					return false;
				}
			}
			break;
		case 2:
			for (auto card : inHoldCardContainer)
			{
				if (!blueCards.contains(card))
				{
					return false;
				}
			}
			break;
		case 3:
			for (auto card : inHoldCardContainer)
			{
				if (!greenCards.contains(card))
				{
					return false;
				}
			}
			break;
		}
		if (mode == 1)
		{
			Card* cardTemp = inHoldCardContainer.at(0);
			for (auto card : inHoldCardContainer)
			{
				if (card->index >= cardTemp->index)
				{
					cardTemp = card;
				}
				else{
					return false;
				}
			}
		}
		//return false;
	}

	return true;
}

bool DragScene::checkCardsCollision(cocos2d::Sprite* sp1, cocos2d::Sprite* sp2)
{
	CCRect r1 = CCRectMake(sp1->getPositionX() - (sp1->getTextureRect().size.width / 2)*0.45, sp1->getPositionY() - (sp1->getTextureRect().size.height / 2)*0.45, sp1->getTextureRect().size.width*0.45, sp1->getTextureRect().size.height*0.45);
	CCRect r2 = CCRectMake(sp2->getPositionX() - (sp2->getTextureRect().size.width / 2)*0.45, sp2->getPositionY() - (sp2->getTextureRect().size.height / 2)*0.45, sp2->getTextureRect().size.width*0.45, sp2->getTextureRect().size.height*0.45);
	//if (CollisionDetection::GetInstance()->areTheSpritesColliding(holder, card, false, _rt)) {   //android deprecated
	if (r1.intersectsRect(r2))
	{
		return true;
	}
	return false;
}
void DragScene::stateBarUpdate()
{
	CCString* s = CCString::createWithFormat("%d", (int)score);
	scoreLabel->setString(s->getCString());

	s = CCString::createWithFormat("%d", (int)stage);
	stageLabel->setString(s->getCString());

	s = CCString::createWithFormat("%d", (int)target);
	targetLabel->setString(s->getCString());
}
void DragScene::prepareNextGroupCards()
{
	/*CCLOG("into prepareNextGroupCards");*/
	////////////////////////////////////////////clear the cards and other stuff///////////////////////////////////////
	if (!cardContainer.empty())
	{
		for (auto card : cardContainer)
		{
			this->removeChild(card,true);
		}
		cardContainer.clear();
	}
	if (!holdCardContainer.empty())
	{
		for (auto card : holdCardContainer)
		{
			card->setVisible(false);
			this->removeChild(card, true);
		}
		holdCardContainer.clear();
	}
	
	

	mode = static_cast<int>(CCRANDOM_0_1() * 2);//the answer`s mode 
	CCString* xmlName = CCString::createWithFormat("question%d.xml", (int)(mode+1));

	questionIndex = static_cast<int>(CCRANDOM_0_1() * 3+1);//the question index, which color of the card is the righr answer
	CCString* question_sr = CCString::createWithFormat("question_%02d",questionIndex);//define the qustion key string to get qustion string

	
	CCString* answerNumber_key = CCString::createWithFormat("answerNumber_%02d", stage);
	CCString answerCount_sr = CXmlStream::GetStringByKeyFromFile(xmlName->getCString(), answerNumber_key->getCString());
	
	int answerCount = answerCount_sr.intValue();//the numbers that card player should place to the answer area(scope) 

	CCString num1_sr = CXmlStream::GetStringByKeyFromFile(xmlName->getCString(), CCString::createWithFormat("maxNumber_%02d", stage)->getCString());
	CCString num2_sr = CXmlStream::GetStringByKeyFromFile("question1.xml", CCString::createWithFormat("minNumber_%02d", stage)->getCString());
	int cardNumber = static_cast<int>(CCRANDOM_0_1()*(num1_sr.intValue()-num2_sr.intValue()+1)+num2_sr.intValue());

	questionLabel->setString(CXmlStream::GetStringByKeyFromFile(xmlName->getCString(), question_sr->getCString()));

	////////////////////////////prepare the card hold area//////////////////////////// 	
	for (int i=0; i < answerCount; i++)
	{
		holdCards.at(i)->setPosition(ccp(500+i*150,420));
		holdCardContainer.pushBack(holdCards.at(i));
		this->addChild(holdCards.at(i),10);
		holdCards.at(i)->setVisible(true);
	}



	std::vector<int> indexContainer;
	std::vector<int> cardIndexContainer;
	std::vector<int> cardIndexContainer2;
	std::vector<int> cardIndexContainer3;


		

		for (int i = 0; i < cardNumber; i++)
		{
			CCInteger* index = 0;
			CCInteger* cardIndex = 0;
			int counter = 0;

			while (true)
			{
				index = CCInteger::create(CCRANDOM_0_1() * 10);
				CCString* ns = CCString::createWithFormat("the index:%d", (int)index->getValue());
				//CCLOG(ns->getCString());
				counter++;
				if (counter >= 100)
				{
					counter = 0;
					//break;
				}
				if (std::find(indexContainer.begin(), indexContainer.end(), index->getValue()) == indexContainer.end())
				{
					/*CCString* ns = CCString::createWithFormat("the index:%d", (int)index->getValue());
					CCLog("///////////////////////////////");
					CCLog(ns->getCString());*/
					indexContainer.push_back(index->getValue());
					break;
				}
			}
			if (i < answerCount)
			{
				
				while (true)
				{
					 cardIndex = CCInteger::create(CCRANDOM_0_1() * 5);
					 if (std::find(cardIndexContainer.begin(), cardIndexContainer.end(), cardIndex->getValue()) == cardIndexContainer.end())
					{
						 cardIndexContainer.push_back(cardIndex->getValue());
						break;
					}
				}
				cards[questionIndex - 1].at(cardIndex->getValue())->setPosition_once(cardPositions[index->getValue()]);
				cardContainer.pushBack(cards[questionIndex - 1].at(cardIndex->getValue()));
				
				this->addChild(cards[questionIndex - 1].at(cardIndex->getValue()), 2);
			}
			else{
				
				if (i % 2 == 0)
				{
					
					while (true)
					{
						 cardIndex = CCInteger::create(CCRANDOM_0_1() * 5);
						 if (std::find(cardIndexContainer2.begin(), cardIndexContainer2.end(), cardIndex->getValue()) == cardIndexContainer2.end())
						 {
							 cardIndexContainer2.push_back(cardIndex->getValue());
							 break;
						 }
					}
					cards[(questionIndex - 1 + 1) % 3].at(cardIndex->getValue())->setPosition_once(cardPositions[index->getValue()]);
					cardContainer.pushBack(cards[(questionIndex - 1 + 1) % 3].at(cardIndex->getValue()));
					
					this->addChild(cards[(questionIndex - 1 + 1) % 3].at(cardIndex->getValue()), 2);

				}
				else
				{
					CCInteger* cardIndex;
					while (true)
					{
						cardIndex = CCInteger::create(CCRANDOM_0_1() * 5);
						if (std::find(cardIndexContainer3.begin(), cardIndexContainer3.end(), cardIndex->getValue()) == cardIndexContainer3.end())
						{
							cardIndexContainer3.push_back(cardIndex->getValue());
							break;
						}
					}
					cards[(questionIndex - 1 + 2) % 3].at(cardIndex->getValue())->setPosition_once(cardPositions[index->getValue()]);
					cardContainer.pushBack(cards[(questionIndex - 1 + 2) % 3].at(cardIndex->getValue()));
					this->addChild(cards[(questionIndex - 1 + 2) % 3].at(cardIndex->getValue()), 2);

				}

			}

		}
		/*CCLOG("into prepareNextGroupCards");*/
}
void DragScene::collideDetect()
{
	
		if (!cardContainer.empty())
		{
			for (auto card : cardContainer)
			{
				//Sprite* sp = (Sprite*)card;
				if (card->isHolded==true)
				{
					for (auto holder : holdCardContainer)
					{
						CCRect r1 = CCRectMake(holder->getPositionX() - (holder->getTextureRect().size.width / 2)*0.45, holder->getPositionY() - (holder->getTextureRect().size.height / 2)*0.45, holder->getTextureRect().size.width*0.45, holder->getTextureRect().size.height*0.45);
						CCRect r2 = CCRectMake(card->getPositionX() - (card->getTextureRect().size.width / 2)*0.45, card->getPositionY() - (card->getTextureRect().size.height / 2)*0.45, card->getTextureRect().size.width*0.45, card->getTextureRect().size.height*0.45);
						//if (CollisionDetection::GetInstance()->areTheSpritesColliding(holder, card, false, _rt)) {   //android deprecated
						if (r1.intersectsRect(r2))
							{
							
							//Code here
							//card->isCollision = true;
							//card->runAction(MoveTo::create(0.2, holder->getPosition()));	     
							card->targetPosition = holder->getPosition();
							break;
						}
						else
						{
							card->targetPosition = card->oldPosition;
						}
				    }


					for (auto card_static : cardContainer)
					{
						if (card_static->isHolded == false)
						{
							CCRect r1 = CCRectMake(card_static->getPositionX() - (card_static->getTextureRect().size.width / 2)*0.45, card_static->getPositionY() - (card_static->getTextureRect().size.height / 2)*0.45, card_static->getTextureRect().size.width*0.45, card_static->getTextureRect().size.height*0.45);
							CCRect r2 = CCRectMake(card->getPositionX() - (card->getTextureRect().size.width / 2)*0.45, card->getPositionY() - (card->getTextureRect().size.height / 2)*0.45, card->getTextureRect().size.width*0.45, card->getTextureRect().size.height*0.45);
							//if (CollisionDetection::GetInstance()->areTheSpritesColliding(card_static, card, false, _rt)) {   //android deprecated
							if (r1.intersectsRect(r2))
							{
							   card->targetPosition = card_static->getPosition();
								card_static->targetPosition = card->oldPosition;
								for (auto card_ : cardContainer)
								{
									if(card_->isRequiredToChangePlace==true)card_->isRequiredToChangePlace = false;
								}
								card_static->isRequiredToChangePlace = true;
								return;
							}
							else
							{
								card_static->isRequiredToChangePlace = false;
							}
						}
					}
				
			     }		
		   }	
		
	   }
	
}
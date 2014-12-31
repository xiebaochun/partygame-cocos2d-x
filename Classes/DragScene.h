#ifndef __DRAG_SCENE_H__
#define __DRAG_SCENE_H__

#include "cocos2d.h"
#include "TimeBar.h"
#include "Card.h"
#include "CXmlStream.h"

USING_NS_CC;

class DragScene : public cocos2d::Layer
{
	friend class Card;
public:
	
	static cocos2d::Scene* createScene();
	virtual bool init();

	void menuCallBack(cocos2d::Ref* pSender);

	void answerShowCallBack(cocos2d::Ref* pSender);

	 void collideDetect();

	void prepareNextGroupCards();

	void stateBarUpdate();

	bool checkAnswer();

	bool checkCardsCollision(cocos2d::Sprite* sp1, cocos2d::Sprite* sp2);

	TimeBar* _timeBar;

	CCMenu* exitMenu;

	static int score;

	int target = 5;

	int stage = 3;

	int menulayerIndex = 20;

	int mode = 0;//0 represent disorder,1 represent order

	int questionIndex = 1;//the questionIdex means the qustion`s index,normally is which color of the card is the answer

	bool isPrepareNext = false;
    
	int timer = 0;

	int showAnswerTextTureWidth;

	int showAnswerTextTureHeight;

	//label to present game score
	cocos2d::CCLabelTTF* scoreLabel;

	//label to present game stage
	cocos2d::CCLabelTTF* stageLabel;

	//label to present game target
	cocos2d::CCLabelTTF* targetLabel;

	//question label
	cocos2d::CCLabelTTF* questionLabel;

	//easyQuestion
	CXmlStream* easyQuestion;

	//sortQuestion
	CXmlStream* sortQuestion;

	enum GameState{start,playing,over};

	static GameState gameState;

	CCMenu* passMenu;

	CCMenu* replayMenu;

	CCMenu* startMenu;

	CCMenu* confirmMenu;

	Sprite* answerShow;

	Vector<HoldCard*> holdCards;

	Vector<Card*> redCards;

	Vector<Card*> blueCards;

	Vector<Card*> greenCards;

	Vector<Card*> cardContainer;

	Vector<HoldCard*> holdCardContainer;

	Vector<Card*> cards[3];

	Point cardPositions[10];

	RenderTexture* _rt;

	CREATE_FUNC(DragScene);


private:
	void update(float dt);
};
#endif
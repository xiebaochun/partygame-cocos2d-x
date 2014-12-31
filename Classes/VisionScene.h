#ifndef __VISION_SCENE_H__
#define __VISION_SCENE_H__

#include "cocos2d.h"
#include "TimeBar.h"
#include "Animal.h"

USING_NS_CC;

class VisionScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void menuCallBack(cocos2d::Ref* pSender);

	void answerShowCallBack(cocos2d::Ref* pSender);

	void GameInfoMenuCallBack(cocos2d::Ref* pSender);

	void update(float dt);

	void stateBarUpdate();

	void prepareNextGroupAnimal();

	virtual ~VisionScene();

	TimeBar* _timeBar;
	
	

	enum GameState{ start, playing, over };

	static GameState gameState;

	CCMenu* passMenu;

	CCMenu* replayMenu;

	CCMenu* startMenu;

	CCMenu* exitMenu;

	CCMenu* helpMenu;

	CCMenu* gameInfoMenu;

	Sprite* answerShow;

	static int score;

	int target = 40;

	int stage = 1;

	 int showAnswerTextTureWidth;

	 int showAnswerTextTureHeight;

	Size visibleSize;
    
	static bool isPrepareNext;

	static bool isAnswerRight;

	Animal* animal;

	Vector<Animal*> animals;

	//label to present game score
	cocos2d::CCLabelTTF* scoreLabel;

	//label to present game stage
	cocos2d::CCLabelTTF* stageLabel;

	//label to present game target
	cocos2d::CCLabelTTF* targetLabel;

	CREATE_FUNC(VisionScene);
};
#endif
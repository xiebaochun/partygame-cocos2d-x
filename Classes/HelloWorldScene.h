#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include  "TimeBar.h"
#include  "Mole.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:

    static int score;

	int target = 40;

	int stage = 1;

	int iCount = 0;

	int holeCount = 6;

	float generate_alta_time = 1;
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
	//schedule update
	virtual void update(float dt);


	bool checkPosition(CCPoint p);
	// a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
	void menuCallBack(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
	//keyBoard press function
	void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

	//keyBoard released function
	void keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

	void stateBarUpdate();

	CCSprite* spBackground_02;
	CCSprite* spBackground_03;

	TimeBar* _timeBar;

	CCMenu* startMenu;
	CCMenu* passMenu;
	CCMenu* replayMenu;
	CCMenu* exitMenu;
	//use to test 
	cocos2d::CCLabelTTF* pLabel;

	//label to present game score
	cocos2d::CCLabelTTF* scoreLabel;

	//label to present game stage
	cocos2d::CCLabelTTF* stageLabel;

	//label to present game target
	cocos2d::CCLabelTTF* targetLabel;

	Mole* mole;

	Vector<Mole*> moles;

	Mole* mole_cutes[9];

	Mole* mole_crabs[9];

	PointArray* molePositions;
	enum keyState{
		pressed,
		released
	};
	keyState KeyState_Up;
	keyState currentKeyState_Up;
	keyState preKeyState_Up;
	enum GameState{
		start,
		playing,
		over
	};
	static GameState gameState;
};

#endif // __HELLOWORLD_SCENE_H__

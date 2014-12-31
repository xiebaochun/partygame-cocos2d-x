#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class StartScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	void menuCallBack(cocos2d::Ref* pSender);

	CCMenu* game_a_menu;
	CCMenu* game_b_menu;
	CCMenu* game_c_menu;
	CCMenu* game_start_menu;

	CREATE_FUNC(StartScene);
};
#endif
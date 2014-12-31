#include "StartScene.h"
#include "DragScene.h"
#include "VisionScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* StartScene::createScene()
{
	auto scene=Scene::create();
	auto layer=StartScene::create();
	scene->addChild(layer);
	//scene->autorelease();
	return scene;
}
bool StartScene::init()
{
	if(!Layer::init())
	{
		return false;
	}
	Size visibleSize=Director::getInstance()->getVisibleSize();
	Point origin=Director::getInstance()->getVisibleOrigin();

	//CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bg_start.wav", true);
	

	CCSprite* spBackground_01 = CCSprite::create("bg_cover_1.png");
	spBackground_01->setAnchorPoint(ccp(0, 0));
	spBackground_01->setPosition(ccp(origin.x, origin.y));
	//spBackground_01->setScale(1);
	//spBackground_01->setVisible(false);
	this->addChild(spBackground_01, 0);

	auto game_a_item = MenuItemImage::create("game_a_item.png", "game_a_item.png", CC_CALLBACK_1(StartScene::menuCallBack, this));
	game_a_menu = Menu::create(game_a_item, NULL);
	game_a_item->setAnchorPoint(ccp(0, 0));
	game_a_menu->setPosition(81,478);
	this->addChild(game_a_menu, 2);

	auto game_b_item = MenuItemImage::create("game_b_item.png", "game_b_item.png", CC_CALLBACK_1(StartScene::menuCallBack, this));
	game_b_menu = Menu::create(game_b_item, NULL);
	game_b_item->setAnchorPoint(ccp(0, 0));
	game_b_menu->setPosition(662,478);
	game_b_menu->setVisible(true);
	this->addChild(game_b_menu, 2);

	auto game_c_item = MenuItemImage::create("game_c_item.png", "game_c_item.png", CC_CALLBACK_1(StartScene::menuCallBack, this));
	game_c_menu = Menu::create(game_c_item, NULL);
	game_c_item->setAnchorPoint(ccp(0, 0));
	game_c_menu->setPosition(112,114);
	game_c_menu->setVisible(true);
	this->addChild(game_c_menu, 2);

	auto game_start_item = MenuItemImage::create("game_start_item.png", "game_start_item.png", CC_CALLBACK_1(StartScene::menuCallBack,this));
	game_start_menu = Menu::create(game_start_item, NULL);
	//game_start_item->setAnchorPoint(ccp(0, 0));
	game_start_menu->setPosition(506,432);
	this->addChild(game_start_menu, 2);

	return true;
}
void StartScene::menuCallBack(cocos2d::Ref* pSender)
{
	CCNode* node = (CCNode*)pSender;
	if (node->getParent() == game_b_menu)
	{
		//CCScene* scene = HelloWorld::createScene();
		//CCDirector::sharedDirector()->replaceScene(scene);
		//CCTransitionScene* transition = CCTransitionProgressRadialCCW::create(1.5f, HelloWorld::createScene());//扇形旋转
		//CCTransitionScene* transition = CCTransitionProgressHorizontal::create(1.2f, HelloWorld::createScene());//水平进度条
		//CCTransitionScene* transition = CCTransitionProgressInOut::create(1.2f, HelloWorld::createScene());//由里到外扩展 
		//    //逐渐透明  
		//CCTransitionScene* transition = CCTransitionCrossFade::create(4.5f, HelloWorld::createScene());
		//翻页  
		//CCTransitionScene* transition = CCTransitionPageTurn::create(0.5f, HelloWorld::createScene(), false);
		//跳动  
		//CCTransitionScene* transition = CCTransitionJumpZoom::create(2.0f, HelloWorld::createScene());
		//部落格过度  
	    //CCTransitionScene* transition = CCTransitionFadeTR::create(3.5f, HelloWorld::createScene());
		//条形折叠  
		//CCTransitionScene* transition = CCTransitionFadeUp::create(1.2f, HelloWorld::createScene());
		//随机方格消失   
		//CCTransitionScene* transition = CCTransitionTurnOffTiles::create(1.2f, HelloWorld::createScene());
		//分行划分切换  
		//CCTransitionScene* transition = CCTransitionSplitRows::create(1.2f, HelloWorld::createScene());
		//分列  
		//CCTransitionScene* transition = CCTransitionSplitCols::create(1.2f, HelloWorld::createScene());
		//颜色过渡  
		//CCTransitionScene* transition = CCTransitionFade::create(12.f, HelloWorld::createScene(), ccc3(120, 25, 100));
		//X轴反转切换画面  
		//CCTransitionScene* transition = CCTransitionFlipX::create(1.2f, HelloWorld::createScene());
		//Y轴  
		  //CCTransitionScene* transition = CCTransitionFlipY::create(1.2f, HelloWorld::createScene());  
		//反转角的反转切换直动画  
		CCTransitionScene* transition = CCTransitionFlipAngular::create(1.2f, HelloWorld::createScene());
		//CCTransitionScene* transition = CCTransitionZoomFlipX::create(1.2f, HelloWorld::createScene());
		//缩放交替  
		//CCTransitionScene* transition = CCTransitionShrinkGrow::create(1.2f, HelloWorld::createScene());
		//旋转绽放
		//CCTransitionScene* transition = CCTransitionRotoZoom::create(1.2f, HelloWorld::createScene());
	    CCDirector::sharedDirector()->replaceScene(transition); 
	}
	if (node->getParent() == game_a_menu)
	{
		CCTransitionScene* transition = CCTransitionFlipAngular::create(1.2f, VisionScene::createScene());
		CCDirector::sharedDirector()->replaceScene(transition);
	}
	if (node->getParent() == game_c_menu)
	{
		CCTransitionScene* transition = CCTransitionFlipAngular::create(1.2f, DragScene::createScene());
		CCDirector::sharedDirector()->replaceScene(transition);
	}
}
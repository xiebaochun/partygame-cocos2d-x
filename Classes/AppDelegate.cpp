#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "StartScene.h"
#include "VisionScene.h"
#include "DragScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
		glview->setFrameSize(640,384);
        director->setOpenGLView(glview);
    }
	glview->setDesignResolutionSize(1280,768,kResolutionExactFit);
    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
   // auto scene = HelloWorld::createScene();
	//auto scene = VisionScene::createScene();
	auto scene = StartScene::createScene();
	//auto scene = DragScene::createScene();
    // run
    director->runWithScene(scene);
	
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

//#if(CC_TARGET_PLATFORM==CC_PLATFORM_WIN32)
//HelloWorld *g_layer;
//
//void Win32SetKeyLayer(HelloWorld* layer)
//{
//	g_layer = layer;
//}
//
//void Win32KeyHool(UINT message,WPARAM wParam,LPARAM lParameter)
//{
//	CCLog("Win32KeyHook message %d wParam %d lParam %d", message,wParam,lParameter);
//	if (g_layer)
//	{
//		g_layer->onWin32KeyEvent(message, wParam, lParameter);
//	}
//}
//
//#endif
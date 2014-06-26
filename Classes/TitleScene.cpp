//
//  TitleScene.cpp
//  Cocod2dxHipTap
//
//  Created by masakishinohara on 2014/06/12.
//
//

#include "TitleScene.h"
#include "GameScene.h"
#include "InfoScene.h"
#include "QuestionScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;//using namespace cocos2d;の略。cocos2dの名前空間を利用
using namespace std;

Scene* TitleScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TitleScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool TitleScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size winSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    //背景画像
    auto backgroundImage = Sprite::create("background.png");
    
    backgroundImage->setPosition(Vec2(winSize.width/2, winSize.height/2));
    
    this->addChild(backgroundImage,1);
    
    //背景画像２
    auto nextBackgroundImage = Sprite::create("nextbackground.png");
    
    nextBackgroundImage->setPosition(Vec2(winSize.width/2, winSize.height/2));
    
    this->addChild(nextBackgroundImage,2);
    
    /////gamestartpageレイヤーstart/////
    //auto *gameStartPage = Layer::create();
    
    auto label = LabelTTF::create("HIPTAP", "Arial", 60);
    
    label->setColor(Color3B(0, 0, 0));
    
    label->setPosition(Vec2(winSize.width/2, winSize.height / 2));
    
    this->addChild(label, 3);
    
    //サウンド設定
    auto soundOn = MenuItemImage::create("soundon.png", "soundon.png", CC_CALLBACK_0(TitleScene::setSoundOn,this));
    
    auto soundOff = MenuItemImage::create("soundoff.png", "soundoff.png", CC_CALLBACK_0(TitleScene::setSoundOff, this));
    
    
    auto question = MenuItemImage::create("question.png","question.png", CC_CALLBACK_0(TitleScene::toQuestionScene, this));
     
    auto gamecenter = MenuItemImage::create("gamecenter.png", "gamecenter.png", CC_CALLBACK_0(TitleScene::goToRanking, this));
    
     
     auto Menu = Menu::create(soundOn,soundOff,question,gamecenter, NULL);
     Menu->setScale(1.0);
     Menu->setPosition(Vec2(winSize.width /3, winSize.height -50 ));
     //Menu->alignItemsHorizontallyWithPadding:15;
     Menu->alignItemsHorizontallyWithPadding(15);
     this->addChild(Menu,3);
    
     //インフォ設定
    auto info = MenuItemImage::create("info.png","info.png",CC_CALLBACK_0(TitleScene::toInfoScene, this));
     
     auto infoMenu = Menu::create(info, NULL);
     infoMenu->setScale(1.0);
     infoMenu->setPosition(Vec2(winSize.width / 1.1, winSize.height - 50 ));
     this->addChild(infoMenu,3);
    
    //ゲームスタートボタン設定
    auto gs_menu_item = Label::createWithSystemFont("gamestart", "Helvetica-BoldOblique", 60.0);
    gs_menu_item->setColor(Color3B(0, 0, 0));
    auto gameStartItem = MenuItemLabel::create(gs_menu_item, CC_CALLBACK_0(TitleScene::toGameScene, this));
    
    auto gameStartMenu = Menu::create(gameStartItem, NULL);
    gameStartMenu->setScale(1.0);
    gameStartMenu->setPosition(Vec2(winSize.width / 2, 60));
    this->addChild(gameStartMenu,3);
    /////gamestartpageレイヤーend/////
    
    return true;
    
}


//////////////////////画面遷移処理start///////////////////////////
void TitleScene::toGameScene()
{
    //auto scene = GameScene::createScene();
    //Director::getInstance()->pushScene(scene);
    
    Director::getInstance()->replaceScene(TransitionFadeDown::create(1, GameScene::createScene()));

}
void TitleScene::toQuestionScene()
{
    Director::getInstance()->replaceScene(QuestionScene::scene());
    
}
void TitleScene::toInfoScene()
{
    Director::getInstance()->replaceScene(InfoScene::scene());
    
}
//////////////////////画面遷移処理end///////////////////////////


//////////////////////サウンド設定start///////////////////////////
void TitleScene::setSoundOn(){
    // This will unmute <span id="IL_AD1" class="IL_AD">the sound</span>
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0);
}

void TitleScene::setSoundOff(){
    //This will mute the sound
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(1);
}
//////////////////////サウンド設定end///////////////////////////


//////////////////////ゲームセンターstart///////////////////////////
//リーダーボードを立ち上げる
void TitleScene::goToRanking() {
    /*
     GKLeaderboardViewController *leaderboardController =
     [[GKLeaderboardViewController alloc] init];
     
     if (leaderboardController != nil)
     {
     leaderboardController.leaderboardDelegate = self;
     [[CCDirector sharedDirector]
     presentModalViewController:leaderboardController animated:YES];
     }
     */
}
//リーダーボードで完了を押した時に呼ばれる
/*
 void TitleScene::leaderboardViewControllerDidFinish(GKLeaderboardViewController *)viewController
 {
 [[CCDirector sharedDirector] dismissModalViewControllerAnimated:YES];
 }
 //////////////////////ゲームセンターend///////////////////////////
 */
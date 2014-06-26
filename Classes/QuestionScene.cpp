//
//  QuestionScene.cpp
//  Cocod2dxHipTap
//
//  Created by masakishinohara on 2014/06/13.
//
//

#include "QuestionScene.h"


using namespace cocos2d;
using namespace std;



Scene* QuestionScene::scene()
{
    auto scene = CCScene::create();
    QuestionScene* layer = QuestionScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool QuestionScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    //タッチ可設定
    this->setTouchEnabled(true);
    
    //タッチ処理
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(QuestionScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(QuestionScene::onTouchMoved,this);
    listener->onTouchEnded = CC_CALLBACK_2(QuestionScene::onTouchEnded, this);
    
    auto dip = Director::getInstance()->getEventDispatcher();
    dip->addEventListenerWithSceneGraphPriority(listener, this);
    
    //スクリーンサイズ保持
    Size winSize = Director::getInstance()->getVisibleSize();
    
    //背景画像
    auto backgroundImage = Sprite::create("background.png");
    
    backgroundImage->setPosition(Vec2(winSize.width/2, winSize.height/2));
    
    this->addChild(backgroundImage,1);
    
    //背景画像２
    auto nextBackgroundImage = Sprite::create("nextbackground.png");
    
    nextBackgroundImage->setPosition(Vec2(winSize.width/2, winSize.height/2));
    
    this->addChild(nextBackgroundImage,2);
    
    //遊び方説明
    auto titleLabel = LabelTTF::create("遊び方", "Helvetica-BoldOblique", 25);
    titleLabel->setColor(Color3B(0, 0, 0));
    titleLabel->setPosition(Vec2(winSize.width / 2, winSize.height/ 1.3 ));
    this->addChild(titleLabel,3);
    
    auto howToPlayLabel = LabelTTF::create("男のケツと女のケツが落ちてくる順番通りに\n\nボタンを押していこう。\n\n落ちるスピードはどんどん速くなるよ。\n\n間違って押したらゲームオーバだよ。", "Helvetica-BoldOblique", 25);
    howToPlayLabel->setColor(Color3B(0, 0, 0));
    howToPlayLabel->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    this->addChild(howToPlayLabel,3);

    return true;
    
}

bool QuestionScene::onTouchBegan(cocos2d::Touch* touch,cocos2d::Event* event){
    
    //画面をタッチした時の処理
    
    return true;
    
}

void QuestionScene::onTouchMoved(cocos2d::Touch* touch,cocos2d::Event* event) {
    
    //タッチ中の処理
    
}

void QuestionScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){
    
    //タッチが終わった時の処理
    Director::getInstance()->replaceScene(TitleScene::createScene());
    
}
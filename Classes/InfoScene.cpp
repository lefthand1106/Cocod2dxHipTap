//
//  InfoScene.cpp
//  Cocod2dxHipTap
//
//  Created by masakishinohara on 2014/06/13.
//
//

#include "InfoScene.h"


using namespace std;

USING_NS_CC;

Scene* InfoScene::scene()
{
    auto scene = CCScene::create();
    InfoScene* layer = InfoScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool InfoScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    //タッチ可設定
    //this->setTouchEnabled(true);
    
    //タッチ処理
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(InfoScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(InfoScene::onTouchMoved,this);
    listener->onTouchEnded = CC_CALLBACK_2(InfoScene::onTouchEnded, this);
    
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
    
    //クレジット設定
    Sprite* credits = Sprite::create("credits.png");
    credits->setPosition(Vec2(winSize.width /2, winSize.height));
    this->addChild(credits,3);
    JumpTo* jumpTo = JumpTo::create(3, Vec2(winSize.width / 2, winSize.height / 3), 60, 3);
    credits->runAction(jumpTo);
    
    //提供元設定
    Sprite*	presentedBy = Sprite::create("lefthandmakerco.png");
    presentedBy->setPosition(Vec2(winSize.width /2, winSize.height +100));
    this->addChild(presentedBy,3);
    DelayTime * delayM = DelayTime::create(5);
    JumpTo* jumpTo2 = JumpTo::create(3, Vec2(winSize.width / 2, winSize.height /3 + credits->getContentSize().height + 10), 60, 3);
    presentedBy->runAction(Sequence::create(delayM,jumpTo2, NULL));
    
    return true;
    
}

bool InfoScene::onTouchBegan(Touch* touch, Event* event){
    
    //画面をタッチした時の処理
    
    return true;
    
}

void InfoScene::onTouchMoved(Touch* touch, Event* event) {
    
    //タッチ中の処理
    
}

void InfoScene::onTouchEnded(Touch *touch, Event *event){
    
    //タッチが終わった時の処理
    Director::getInstance()->replaceScene(TitleScene::createScene());
    
}
//
//  GameScene.cpp
//  Cocod2dxHipTap
//
//  Created by masakishinohara on 2014/06/12.
//
//

#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "TitleScene.h"

USING_NS_CC;//using namespace cocos2d;の略。cocos2dの名前空間を利用
using namespace std;
using namespace CocosDenshion;


Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    GameScene* layer = GameScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool GameScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    Size winSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    //背景レイヤー
    LayerColor *colorLayer = LayerColor::create(Color4B(255,255,255,255));
    colorLayer->setContentSize(Size(winSize.width, winSize.height));
    colorLayer->setPosition(Vec2( 0, 0));
    this->addChild(colorLayer,0);
    
    //タッチ可にする
    this->setTouchEnabled(true);
    
    // カウンター画像配置start//
    //srand((unsigned)time(NULL));
    int counter = 0;
    auto stringCount = String::create(to_string(counter));
    countLabel = Label::create(stringCount->getCString(), "Chalkduster", 20);
    countLabel->setColor(Color3B(255,255,255));
    countLabel->setPosition(Vec2(winSize.width / 1.15, winSize.height / 1.2));
    this->addChild(countLabel,1);
    // カウンターを生成end//
    
    //line配置start//
    line = Sprite::create("line.png");
    line->setPosition(Vec2(winSize.width / 2, winSize.height / 7 ));
    this->addChild(line,2);
    //line配置end//
    
    //落下画像配置--start//
    
   // _men = Array::create();
   // _women = Array::create();
   // _menWomen = Array::create();
    
    for (int i = 0; i < 100; i++) {
        auto manIcon = Sprite::create("manhip.png");
        manIcon->setScale(2);
        manIcon->setScale(2);
        _men.pushBack(manIcon);
        manIcon->setTag(1);
        _menWomen.pushBack(manIcon);
        
    }
    
    for (int i = 0; i < 100; i++) {
        auto womanIcon = Sprite::create("womanhip.png");
        womanIcon->setScale(2);
        _women.pushBack(womanIcon);
        womanIcon->setTag(2);
        _menWomen.pushBack(womanIcon);
    }
    //落下画像をシャッフル
      std::random_shuffle(_menWomen.begin(), _menWomen.end());
 
    //落下画像配置--end//
    
    
    //タップ画像配置--start//
    
    auto menu_item_man = MenuItemImage::create("manhip.png", "manhip.png", CC_CALLBACK_1(GameScene::touchMan, this));
    auto menu_item_woman = MenuItemImage::create("womanhip.png", "womanhip.png", CC_CALLBACK_1(GameScene::touchWoman, this));
    
    
    auto *tapMenu = Menu::create(menu_item_man, menu_item_woman, NULL);
    tapMenu->setPosition(Point(winSize.width, winSize.height / 1.5));
    tapMenu->setScale(2);
    tapMenu->alignItemsHorizontallyWithPadding(40);
    this->addChild(tapMenu,3);
    
    //タップ画像配置--end//
    
    //配列(menwomen)の要素値の初期値を設定
    IndexCount = 0;
    
    //soundをプレロード
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("wrong.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("correct.mp3");
    
    //画像落下スピード初期値
     dmSpeed = 0.1f;
    
    //画像落下メソッド呼び出し
    dropImages();
    
    //衝突判定メソッド呼び出し
    this->scheduleUpdate();
    
    
    //ゲーむ時間をカウントアップする関数を毎フレーム呼び出す
   // this->schedule(schedule_selector(GameScene::mesureGametime));
    
    // 3秒毎に落下スピードを上げる
    this->schedule(schedule_selector(GameScene::changeSpeed),1.0f);
    
    //soundreload
    //あらかじめ、音楽データを読み込む
    SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);
    SimpleAudioEngine::getInstance()->preloadEffect("correct.mp3");
    
    log("menWomen:%zd",_menWomen.size());
    
    return true;
    
}

///////////////////カウントアップ処理start///////////////////
void GameScene::countUp()
{
    counter = mancount + womancount;
    //intから文字に変換
    String* score = String::createWithFormat("%d",counter);
    //スコアラベルを生成する
    countLabel->setString(score->getCString());
    
}
///////////////////カウントアップ処理end///////////////////


///////////////////タッチ処理start///////////////////
void GameScene::touchMan(cocos2d::Ref * pSender)
{
    if(_menWomen.at(IndexCount)){
        //正しい場合
        Sprite* tempSprite;
        tempSprite =_menWomen.at(IndexCount);
    
        if (tempSprite->getTag() == 1 ) {
            this->removeChildByTag(1);
            int soundID;
            soundID = SimpleAudioEngine::getInstance()->playEffect("correct.mp3");
            mancount++;
            countUp();
        }
        //間違えた場合
        else if (tempSprite->getTag() == 2){
            int soundID;
            soundID = SimpleAudioEngine::getInstance()->playEffect("wrong.mp3");
            gameover();
        }
        IndexCount++;
    }
}

void GameScene::touchWoman(cocos2d::Ref* pSender)
{
    if ((Sprite*)_menWomen.at(IndexCount)) {
        //正しい場合
        Sprite * tempSprite;
        tempSprite =_menWomen.at(IndexCount);
        
        if (tempSprite->getTag() == 2 ) {
            this->removeChildByTag(2);
            int soundID;
            soundID = SimpleAudioEngine::getInstance()->playEffect("correct.mp3");
            womancount++;
            countUp();
        }
        //間違えた場合
        else if (tempSprite->getTag() == 1){
            int soundID;
            soundID = SimpleAudioEngine::getInstance()->playEffect("worng.mp3");
            gameover();
        }
        IndexCount++;
    }
}
///////////////////タッチ処理end///////////////////


///////////////////画面落下処理start///////////////////
void GameScene::dropImages()
{
    //配列から順に画像を取得
    log("menWomen:%zd",_menWomen.size());
    Size winSize =Director::getInstance()->getVisibleSize();
    float delay = 0;
    //CCObject *obj = NULL;
    //CCARRAY_FOREACH(_menWomen, obj){
    for (int i = 0; i < _menWomen.size(); i++) {
       
       // cocos2d::Sprite * dropImage;
        dropImage = _menWomen.at(i);
        dropImage->setPosition(Vec2(winSize.width / 2, winSize.height + 100));
        this->addChild(dropImage, 4);
        
        auto delayM = DelayTime::create(delay);
        delayM->setTag(10);
        
        auto moveTo = MoveTo::create(15.0f, Point(winSize.width / 2, 60));
        moveTo->setTag(20);
      
        //Speed* speed = Speed::create((Sequence::create(delayM, moveTo, NULL)), dmSpeed);
        auto sequence = Sequence::create(delayM, moveTo, NULL);
        
        auto action = Speed::create(sequence, dmSpeed);
        action->setTag(30);
        
        dropImage->runAction(action);
        delay += 1;
        
        //CCSpeed *speed = [CCSpeed actionWithAction:[CCSequence actions: delayM, moveTo, nil] speed:dmSpeed];
    }
}
///////////////////画面落下処理end///////////////////

///////////////////アップロード処理start///////////////////
void GameScene::update(float delta)
{
    checkForCollision();
    //log("dropimage.dmSpeed:%f", static_cast<Speed*>(Speed->dropImage)));


}
///////////////////アップロード処理start///////////////////


///////////////////衝突処理start///////////////////

void GameScene::checkForCollision()
{
    float lineIconSize = line->getContentSize().width;
    float manWomanImageSize =_menWomen.at(199)->getContentSize().width;
   
    float lineCollisionRadius = lineIconSize * 0.1f;
    float manWomanIconCollisionRadius = manWomanImageSize * 0.4f;
   
    float maxCollisionDistance = lineCollisionRadius + manWomanIconCollisionRadius;
    
    int numMenWomen = sizeof(_menWomen);
    for (int i = 0; i < numMenWomen; i++) {
        dropImage = _menWomen.at(i);
        if (dropImage->getNumberOfRunningActions() == 0)
        {
            continue;
        }
        
        float actualDistance = ccpDistance(line->getPosition(), dropImage->getPosition());
        
        if (actualDistance < maxCollisionDistance) {
            SimpleAudioEngine::getInstance()->playEffect("wrong.mp3");
            
            gameover();
        }
    
    }
}

///////////////////衝突処理end///////////////////


///////////////////ゲームオーバー処理start///////////////////
void GameScene::gameover()
{
    this->removeAllChildren();
    this->unscheduleAllSelectors();
    
    //gameover画面
    Size winSize =Director::getInstance()->getVisibleSize();
    Sprite *gameover = Sprite::create("gameover.png");
    gameover->setPosition(Vec2(winSize.width /2, 0));
    this->addChild(gameover,4);
    
    //結果表示
    auto numberString = String::createWithFormat("男が：%d、女が%d。", mancount,womancount);
    auto resultLabel = LabelTTF::create(numberString->getCString(), "Arial Rounded MT Bold", 40.0);
    resultLabel->setColor(Color3B(0, 0, 0));
    resultLabel->setPosition(Vec2(winSize.width /2 , winSize.height/2 ));
    gameover->addChild(resultLabel);
    
    //結果表示アクション
    ActionInterval* moveTo = MoveTo::create(0.5f, Point(winSize.width / 2, winSize.height/2));
    gameover->runAction(moveTo);
    
    //menu設定
    auto goTitle = MenuItemImage::create("title.png", "title.png", CC_CALLBACK_0(GameScene::goTitleButton, this));
    
    auto reStart = MenuItemImage::create("restart.png", "restart.png", CC_CALLBACK_0(GameScene::tapRetryButton, this));
    
    auto resultMenu = Menu::create(goTitle,reStart, NULL);
    resultMenu->setScale(1.0);
    resultMenu->setPosition(Vec2(winSize.width /2, winSize.height / 2 - resultLabel->getContentSize().height * 7));
    resultMenu->alignItemsHorizontallyWithPadding(40);
    gameover->addChild(resultMenu);

}
///////////////////ゲームオーバー処理end///////////////////


///////////////////遷移処理start///////////////////
void GameScene::goTitleButton()
{
    Director::getInstance()->replaceScene(TitleScene::createScene());
   // Director::getInstance()->popScene();
}

void GameScene::tapRetryButton()
{
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFlipX::create(2,scene));
    
    Director::getInstance()->replaceScene(GameScene::createScene());
    
}

///////////////////遷移処理end///////////////////


///////////////////落下画像スピード変更処理start///////////////////
void GameScene::changeSpeed(float delta)
{
    for (auto dropImage : _menWomen) {
        auto speed = static_cast<Speed*>(dropImage->getActionByTag(30));
    speed->setSpeed(dmSpeed);
      }
    dmSpeed = dmSpeed + 0.2f;
    log("dmSpeed:%f",dmSpeed);
   // log("dmSpeed:%f",Speed( dropImage->getSpriteFrame());
    
}
///////////////////落下画像スピード変更処理end///////////////////


/*
///////////////////落下画像スピード変更処理start///////////////////
- (void)changeSpeed
{
    for (dropImage in menWomen) {
        CCSpeed *speed = (CCSpeed*)[dropImage getActionByTag:30];
        speed.speed = dmSpeed;
    }
    dmSpeed = dmSpeed + 0.2f;
}
///////////////////落下画像スピード変更処理end///////////////////
*/


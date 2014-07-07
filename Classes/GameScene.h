//
//  GameScene.h
//  Cocod2dxHipTap
//
//  Created by masakishinohara on 2014/06/12.
//
//

#ifndef __Cocod2dxHipTap__GameScene__
#define __Cocod2dxHipTap__GameScene__

#include "cocos2d.h"
#include "TitleScene.h"

USING_NS_CC;

class GameScene : public Layer
{
    
private:
    int counter;                  //男女タップ回数保持
    int mancount;               //男尻タップ回数保持
    int womancount;             //女尻タップ回数保持
    Label* countLabel;     //カウンター用ラベル
    Vector<Sprite*> _menWomen;         //落下画像(men,women)格納配列
    int IndexCount;             //配列(menwomen)の要素値を保持
    
    
    Sprite * line;            //衝突先画像
    Sprite * manIcon;         //落下画像
    Sprite * womanIcon;       //落下画像
    Vector<Sprite*>  _men;              //落下画像(manIcon)格納配列
    Vector<Sprite*>  _women;            //落下画像(womanIcon)格納配列
    Sprite* dropImage;       //落下処理画像、落下スピード処理画像、衝突処理画像
    
    float dmSpeed;              //落下画像スピード設定変数
    
    void mesureGametime(float fDelta);
    
public:
    virtual bool init();
    static Scene* createScene();
    CREATE_FUNC(GameScene);
    void countUp();
    void touchMan(Ref* pSender);
    void touchWoman(Ref* pSender);
    void dropImages();
    void checkForCollision();
    void update(float delta);
    void gameover();
    void goTitleButton();
    void tapRetryButton();
    void changeSpeed(float delta);
    
};

#endif /* defined(__Cocod2dxHipTap__GameScene__) */

//
//  TitleScene.h
//  Cocod2dxHipTap
//
//  Created by masakishinohara on 2014/06/12.
//
//

#ifndef __Cocod2dxHipTap__TitleScene__
#define __Cocod2dxHipTap__TitleScene__

#include "cocos2d.h"
USING_NS_CC;

class TitleScene : public Layer
{
private:
    
    // void changeScene();
    
    
    
public:
    virtual bool init();
    static Scene* createScene();
    CREATE_FUNC(TitleScene);
    //void setSoundOn();
    //void setSoundOff();
    void setSoundEffect();
    void goToRanking();
    void toGameScene();
    void toQuestionScene();
    void toInfoScene();
    //virtual void leaderboardViewControllerDidFinish();
   
    MenuItem * soundOn;
    MenuItem * soundOff;
    MenuItemToggle *toggleItem;
    int soundEffect;

    
};


#endif /* defined(__Cocod2dxHipTap__TitleScene__) */

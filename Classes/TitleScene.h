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


class TitleScene : public cocos2d::Layer
{
private:
    
    // void changeScene();
    
    
    
public:
    virtual bool init();
    static cocos2d::Scene* createScene();
    CREATE_FUNC(TitleScene);
    void setSoundOn();
    void setSoundOff();
    void goToRanking();
    void toGameScene();
    void toQuestionScene();
    void toInfoScene();
    //virtual void leaderboardViewControllerDidFinish();
    
    
};


#endif /* defined(__Cocod2dxHipTap__TitleScene__) */

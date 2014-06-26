//
//  InfoScene.h
//  Cocod2dxHipTap
//
//  Created by masakishinohara on 2014/06/13.
//
//

#ifndef __Cocod2dxHipTap__InfoScene__
#define __Cocod2dxHipTap__InfoScene__

#include "cocos2d.h"
#include "TitleScene.h"

class InfoScene : public cocos2d::Layer
{
    
private:
    
public:
    virtual bool init();
    static cocos2d::Scene* scene();
    CREATE_FUNC(InfoScene);
    bool onTouchBegan(cocos2d::Touch* touch,cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    
};

#endif /* defined(__Cocod2dxHipTap__QuestionScene__) */

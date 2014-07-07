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
USING_NS_CC;

class InfoScene : public Layer
{
    
private:
    
public:
    virtual bool init();
    static Scene* scene();
    CREATE_FUNC(InfoScene);
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);

    
};

#endif /* defined(__Cocod2dxHipTap__QuestionScene__) */

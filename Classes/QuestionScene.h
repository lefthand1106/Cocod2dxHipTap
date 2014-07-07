//
//  QuestionScene.h
//  Cocod2dxHipTap
//
//  Created by masakishinohara on 2014/06/13.
//
//

#ifndef __Cocod2dxHipTap__QuestionScene__
#define __Cocod2dxHipTap__QuestionScene__

#include "cocos2d.h"
#include "TitleScene.h"

USING_NS_CC;

class QuestionScene : public Layer
{
    
private:
    
public:
    virtual bool init();
    static Scene* scene();
    CREATE_FUNC(QuestionScene);
    bool onTouchBegan(Touch* touch,Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    

};

#endif /* defined(__Cocod2dxHipTap__QuestionScene__) */

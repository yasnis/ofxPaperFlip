//
//  ofxPaperFlip.h
//  ofApp
//
//  Created by cameura.com on 2014/12/10.
//
//

#ifndef __ofApp__ofxPaperFlip__
#define __ofApp__ofxPaperFlip__

#include "ofMain.h"

class ofxPaperFlip {
    public:
        enum FlipType {
            TYPE_HORIZONTAL,
            TYPE_VERTICAL
        };
    
        enum FlipDirection {
            FLIP_FORWARD,
            FLIP_REVERSE
        };
    
        ofxPaperFlip();
        ~ofxPaperFlip();
    
        void setup();
        void setup(ofImage *prevImg, ofImage *nextImg, FlipType type = TYPE_HORIZONTAL, float speed = 0.1, float offset = 0.5);
        void update();
        void update(float value);
        void draw();
        void draw(int x, int y);
        void draw(int x, int y, int w, int h);
        void reset();
    
        void setImage(ofImage *prevImg, ofImage *nextImg);
    
        void setSpeed(float s);
        float getSpeed();
    
        void setOffset(float o);
        float getOffset();
    
        void setType(FlipType t);
        FlipType getType();
    
        void setDirection(FlipDirection d);
        FlipDirection getDirection();
    
    private:
        ofImage *image0,*image1;
        ofFbo fbo;
        ofMesh mesh;
    
        FlipType type;
        FlipDirection direction;
        int imgW, imgH;
        float v,offset,speed;
    
        void updateMesh();
        void drawVertical();
        void drawHorizontal();
    
};


#endif /* defined(__ofApp__ofxPaperFlip__) */

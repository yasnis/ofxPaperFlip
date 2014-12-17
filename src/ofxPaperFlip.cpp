//
//  ofxPaperFlip.cpp
//  ofApp
//
//  Created by cameura.com on 2014/12/10.
//
//

#include "ofxPaperFlip.h"



ofxPaperFlip::ofxPaperFlip() {
    
}
ofxPaperFlip::~ofxPaperFlip(){
    
}

void ofxPaperFlip::setup() {
}

void ofxPaperFlip::setup(ofImage *prevImg, ofImage *nextImg, FlipType type, float speed, float offset) {
    setImage(prevImg, nextImg);
    updateMesh();
    setType(type);
    setSpeed(speed);
    setOffset(offset);
    v = 0;
}

void ofxPaperFlip::update() {
    v+=(direction==FLIP_FORWARD)?speed:-speed;
    
    if(v > 1+offset) v = 1+offset;
    else if(v < -1) v = -1;
}
void ofxPaperFlip::update(float value){
    v = value*(2+offset)-1;
    
    if(v > 1+offset) v = 1+offset;
    else if(v < -1) v = -1;
}

void ofxPaperFlip::draw() {
    draw(0, 0, imgW, imgH);
}
void ofxPaperFlip::draw(int x, int y) {
    draw(x, y, imgW, imgH);
}

void ofxPaperFlip::draw(int x, int y, int w, int h) {
    if (type == TYPE_VERTICAL) drawVertical();
    else if(type == TYPE_HORIZONTAL) drawHorizontal();
    ofPushMatrix();
    ofTranslate(x, y);
    ofScale((float)w/imgW, (float)h/imgH);
    fbo.getTextureReference().bind();
    mesh.draw();
    fbo.getTextureReference().unbind();
    ofPopMatrix();
}

void ofxPaperFlip::drawVertical(){
    int flip = 0;
    for (int x = 0; x < imgW; x++) {
        float p = (v-offset*(float)x/imgW);
        float t = MIN(1, MAX(-1, p))*PI/2;
        int topY = (int)(sin(t)*(-imgH/2)+imgH/2);
        int bottomY =(int)(sin(t)*imgH/2+imgH/2);
        if(topY<bottomY){
            flip = x;
        }
        
        mesh.setVertex(2*x, ofPoint(x,topY));
        mesh.setVertex(2*x+1, ofPoint(x,bottomY));
    }
    
    fbo.begin();
    image1->drawSubsection(0, 0, flip, imgH, 0, 0);
    ofPushMatrix();
    ofScale(1, -1);
    ofTranslate(0, -imgH);
    image0->drawSubsection(flip, 0, imgW, imgH, flip, 0);
    ofPopMatrix();
    fbo.end();
}

void ofxPaperFlip::drawHorizontal(){
    int flip = 0;
    for (int y = 0; y < imgH; y++) {
        float p = (v-offset*(float)y/imgH);
        float t = MIN(1, MAX(-1, p))*PI/2;
        int leftX = (int)(sin(t)*(-imgW/2)+imgW/2);
        int rightX =(int)(sin(t)*imgW/2+imgW/2);
        if(leftX<rightX){
            flip = y;
        }
        
        mesh.setVertex(2*y, ofPoint(leftX,y));
        mesh.setVertex(2*y+1, ofPoint(rightX,y));
    }
    
    fbo.begin();
    image1->drawSubsection(0, 0, imgW, flip, 0, 0);
    ofPushMatrix();
    ofScale(-1, 1);
    ofTranslate(-imgW, 0);
    image0->drawSubsection(0, flip, imgW, imgH, 0, flip);
    ofPopMatrix();
    fbo.end();
}

void ofxPaperFlip::updateMesh() {
    mesh.clear();
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    if (type == TYPE_VERTICAL) {
        for (int x = 0; x < imgW; x++) {
            mesh.addVertex(ofPoint(x,0));
            mesh.addVertex(ofPoint(x,imgH));
            
            mesh.addTexCoord(ofPoint(x,0));
            mesh.addTexCoord(ofPoint(x,imgH));
        }
    } else if(type == TYPE_HORIZONTAL) {
        for (int y = 0; y < imgH; y++) {
            mesh.addVertex(ofPoint(0,y));
            mesh.addVertex(ofPoint(imgW,y));
            
            mesh.addTexCoord(ofPoint(0,y));
            mesh.addTexCoord(ofPoint(imgW,y));
        }
    }
}

void ofxPaperFlip::setImage(ofImage *prevImg, ofImage *nextImg){
    image0 = prevImg;
    image1 = nextImg;
    imgW = image0->getWidth();
    imgH = image0->getHeight();
    
    fbo.allocate(imgW, imgH);
}

void ofxPaperFlip::setSpeed(float s){
    speed = s;
}

float ofxPaperFlip::getSpeed(){
    return speed;
}


void ofxPaperFlip::setOffset(float o){
    offset = o;
}

float ofxPaperFlip::getOffset(){
    return offset;
}

void ofxPaperFlip::setType(FlipType t) {
    if(type != t){
        type = t;
        updateMesh();
    }
}
ofxPaperFlip::FlipType ofxPaperFlip::getType(){
    return type;
}

void ofxPaperFlip::setDirection(FlipDirection d) {
    direction = d;
}

ofxPaperFlip::FlipDirection ofxPaperFlip::getDirection(){
    return direction;
}

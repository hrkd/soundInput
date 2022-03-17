//
//  testClass.cpp
//  soundInputBase
//
//  Created by @_hrkd on 2022/03/10.
//  
//

#include "testClass.hpp"
#include <random>

testClass::testClass(){
    color[0] = ofColor(254,218,132);
    color[1] = ofColor(255,155,131);
    color[2] = ofColor(151,99,147);
    color[3] = ofColor(104,84,137);
}

void testClass::setup(){
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distr(0,MAX);
    std::uniform_int_distribution<float> distr2(0,1);
    ofEnableDepthTest();
    ofBackground(color[colorIndex%color.size()]);

    light.setPosition(0, -100, 500);
    light.enable();

    light.setAmbientColor(ofColor(100,100,100));

    for(int i=0;i<boxis.size();i++){
        boxis[i].setPosition(distr(eng)-MAX/2, distr(eng)-MAX/2, distr(eng)-MAX/2);
        int rand = random() % 360;
        int rand2 = random() % 3;
        if(rand2 == 0){
            boxis[i].rotateDeg(rand, 1,0,0);
        }
        if(rand2 == 1){
            boxis[i].rotateDeg(rand, 0,1,0);
        }
        if(rand2 == 2){
            boxis[i].rotateDeg(rand, 0,0,1);
        }
        boxis[i].set(30);
        boxis[i].setParent(parentNode);
    }

    midiIn.listInPorts();

    midiIn.openPort(0);

    midiIn.ignoreTypes(false, false, false);
    midiIn.addListener(this);
    midiIn.setVerbose(true);
}
void testClass::update(){
    parentNode.rotateDeg(0.1, 0,1,0);
    for(unsigned int i = 0; i < midiMessages.size(); ++i) {
        ofxMidiMessage &message = midiMessages[i];
    }
}
void testClass::draw(){
    ofBackground(color[colorIndex%color.size()]);
    cam.begin();
        for(int i=0;i<boxis.size();i++){
            boxis[i].draw();
        }
    cam.end();
}

void testClass::setAnalyzed(vector<float> fft){
    for(int i=0;i<boxis.size();i++){
        boxis[i].set(50 + 20*fft[0]);
    }
}

void testClass::newMidiMessage(ofxMidiMessage& msg) {
    // add the latest message to the message queue
    if(msg.pitch == 40 && msg.status == 144) {
        colorIndex ++;
    }
    midiMessages.push_back(msg);

    // remove any old messages if we have too many
    while(midiMessages.size() > maxMessages) {
        midiMessages.erase(midiMessages.begin());
    }
}

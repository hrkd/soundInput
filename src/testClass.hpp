//
//  testClass.hpp
//  soundInputBase
//
//  Created by @_hrkd on 2022/03/10.
//  
//

#ifndef testClass_hpp
#define testClass_hpp

#include "ofMain.h"
#include "ofxMidi.h"
#include <iostream>
#include <random>

class testClass: public ofBaseApp, public ofxMidiListener {
public:
    testClass();
    ~testClass(){}

    void setup();
    void update();
    void draw();
    void setAnalyzed(vector<float> fft);
    std::random_device rd;
    void newMidiMessage(ofxMidiMessage& eventArgs);

    ofxMidiIn midiIn;
    std::vector<ofxMidiMessage> midiMessages;
    std::size_t maxMessages = 10; //< max number of messages to keep track of
private:

    array<ofBoxPrimitive,50> boxis;
    ofNode parentNode;
    ofEasyCam cam;
    ofLight light;
    ofLight ambientLight;
    ofMaterial material;
    array<ofColor,4> color;

    int colorIndex = 0;
    int MAX = 1000;
};

#endif /* testClass_hpp */

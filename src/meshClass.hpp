//
//  meshClass.hpp
//  soundInputBase
//
//  Created by @_hrkd on 2022/03/17.
//  
//

#ifndef meshClass_hpp
#define meshClass_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxMidi.h"
#include <iostream>
#include <math.h>

class meshClass: public ofBaseApp, public ofxMidiListener {
public:
    meshClass();
    ~meshClass(){}

    void setup();
    void update();
    void draw();
    void setAnalyzed(vector<float> fft);
    void newMidiMessage(ofxMidiMessage& eventArgs);

    ofxMidiIn midiIn;
    std::vector<ofxMidiMessage> midiMessages;
    std::size_t maxMessages = 10; //< max number of messages to keep track of
private:
    ofNode parentNode;
    ofEasyCam cam;
    ofMesh mesh;
    ofPlanePrimitive plane;
    ofSpherePrimitive sphere;

    vector<glm::vec3> vertices;
    float fftMemo[100][100];
};
#endif /* meshClass_hpp */

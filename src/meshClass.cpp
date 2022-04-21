//
//  meshClass.cpp
//  soundInputBase
//
//  Created by @_hrkd on 2022/03/17.
//  
//

#include "meshClass.hpp"

meshClass::meshClass(){
}

void meshClass::setup(){
    plane.set(1000,1000,100,100);
    plane.rotateDeg(45, 1,1,1);
    mesh = plane.getMesh();
    vertices = mesh.getVertices();
    for(int r=0;r<100;r++){
        for(int c=0;c<100;c++){
            fftMemo[r][c] = 0;
        }
    }
    ofEnableDepthTest();
}

void meshClass::draw(){
    ofBackground(0,0,0);
    cam.begin();

    ofSetColor(30);
    mesh.draw();
    ofSetColor(200);
    mesh.drawWireframe();
    cam.end();
}

void meshClass::setAnalyzed(vector<float> fft){
    //shift to right
    for(int i=100-1;i>=0;i--){
        for(int j=0;j<100;j++){
            fftMemo[i][j] = fftMemo[i-1][j];
        }
    }

    //new value
    for(int i=0;i<100;i++){
        fftMemo[0][i] = fft[i];
    }

    for(int i=0;i<vertices.size();i++){
        float x = vertices[i].x;
        float y = vertices[i].y;
        float z = fftMemo[(int)floor(i/100)][i%100] * 300;
        mesh.setVertex(i, glm::vec3(x,y,z));
    }
}

void meshClass::newMidiMessage(ofxMidiMessage& msg) {
    // add the latest message to the message queue
    midiMessages.push_back(msg);

    // remove any old messages if we have too many
    while(midiMessages.size() > maxMessages) {
        midiMessages.erase(midiMessages.begin());
    }
}

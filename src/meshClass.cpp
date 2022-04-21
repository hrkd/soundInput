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
//    sphere.set(500,100);
//    mesh = sphere.getMesh();
    mesh = plane.getMesh();
    vertices = mesh.getVertices();
    for(int r=0;r<100;r++){
        for(int c=0;c<100;c++){
            fftMemo[r][c] = 0;
        }
    }
    ofEnableDepthTest();
}

void meshClass::update(){
    ofTranslate(0, 0, 10);
}

void meshClass::draw(){
    ofBackground(0,0,0);
    cam.begin();
//    float div = 200.0;
//    float height = 50.0;
//    float freq = 0.02;
//    float speed = 0.25;
//    for(int i=0;i<vertices.size();i++){
//        float x = vertices[i].x;
//        float y = vertices[i].y;
//        float z = vertices[i].z;

        //forth demention noise
//        float z = ofNoise(
//            vertices[i].x / div,
//            vertices[i].y / div,
//            0,
//            ofGetElapsedTimef() * speed
//        );
//        z = ofMap(
//          z,
//          0, 1,
//          0, height
//        );

        //sin
//        float zx = sin(x * freq + ofGetElapsedTimef()) * height;
//        float zy = sin(y * freq + ofGetElapsedTimef()) * height;
//        float zy = 0;
//        float z = zx + zy;
//        mesh.setVertex(i, glm::vec3(x,y,z));
//    }

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

//    for(int i=0;i<100;i++){
//        for(int j=0;j<100;j++){
//            float x = vertices[i].x;
//            float y = vertices[i].y;
//        }
//    }
}

void meshClass::newMidiMessage(ofxMidiMessage& msg) {
//    if(msg.pitch == 40 && msg.status == 144) {
//        colorIndex ++;
//    }

    // add the latest message to the message queue
    midiMessages.push_back(msg);

    // remove any old messages if we have too many
    while(midiMessages.size() > maxMessages) {
        midiMessages.erase(midiMessages.begin());
    }
}

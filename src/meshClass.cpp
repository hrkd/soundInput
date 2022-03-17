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
    sphere.set(500,100);
//    mesh = sphere.getMesh();
    mesh = plane.getMesh();
}

void meshClass::update(){
}

void meshClass::draw(){
    ofBackground(0,0,0);
    cam.begin();
    vector<glm::vec3> vertices = mesh.getVertices();
    float div = 200.0;
    float height = 50.0;
    float freq = 0.02;
    float speed = 0.25;
    for(int i=0;i<vertices.size();i++){
        float x = vertices[i].x;
        float y = vertices[i].y;

        //forth demention noise
        float z = ofNoise(
            vertices[i].x / div,
            vertices[i].y / div,
            0,
            ofGetElapsedTimef() * speed
        );
        z = ofMap(
          z,
          0, 1,
          0, height
        );

        //sin
//        float zx = sin(x * freq + ofGetElapsedTimef()) * height;
//        float zy = sin(y * freq + ofGetElapsedTimef()) * height;
//        float zy = 0;
//        float z = zx + zy;
        mesh.setVertex(i, glm::vec3(x,y,z));
    }
    mesh.drawVertices();
    cam.end();
}

void meshClass::setAnalyzed(vector<float> fft){
//    for(int i=0;i<boxis.size();i++){
//        boxis[i].set(50 + 20*fft[0]);
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

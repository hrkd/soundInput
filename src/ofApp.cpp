#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    mSoundInput.setup();
    mTestClass.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    mSoundInput.update();
    fftVal = mSoundInput.getAnalyzed();
    mTestClass.setAnalyzed(fftVal);
    mTestClass.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    if(isDebug){
        mSoundInput.draw();
    }
    mTestClass.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    //D key
    if(key == 100){
        isDebug = !isDebug;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

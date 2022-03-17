#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    mSoundInput.setup();
    mTestClass.setup();
    mMeshClass.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    mSoundInput.update();
    fftVal = mSoundInput.getAnalyzed();

    if(switchDraw%2 == 0){
        mMeshClass.setAnalyzed(fftVal);
        mMeshClass.update();
    }else{
        mTestClass.setAnalyzed(fftVal);
        mTestClass.update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    if(isDebug){
        mSoundInput.draw();
    }
    if(switchDraw%2 == 0){
        mMeshClass.draw();
    }else{
        mTestClass.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    std::cout << key << std::endl;

    //A key
    if(key == 97){
        switchDraw++;
    }

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

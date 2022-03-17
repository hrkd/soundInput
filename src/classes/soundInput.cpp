//
//  soundInput.cpp
//  soundInputBase
//
//  Created by YOHEI KAJIWARA on 2022/03/10.
//

#include "soundInput.hpp"
void soundInput::setup() {
    // SoundIn
    bufferSize = 2048;
    
    ofSoundStreamSettings settings;
    auto devices = ofSoundStreamListDevices();
    string deviceName = "Existential Audio Inc.: BlackHole 2ch";
    int targetDeviceId = 0;
    for (int i = 0; i < devices.size(); i++) {
        std::cout << devices[i].name << std::endl;
        if (devices[i].name == deviceName) {
            targetDeviceId = i;
        }
    }

    if(!devices.empty()){
        settings.setInDevice(devices[targetDeviceId]);
    }

    settings.setInListener(this);
    settings.sampleRate = 44100;
    settings.numOutputChannels = 0;
    settings.numInputChannels = 2;
    settings.bufferSize = bufferSize;
    ofSoundStreamSetup(settings);

    // FFT
    plotHeight = 128;

    fft = ofxFft::create(bufferSize, OF_FFT_WINDOW_HAMMING);

    drawBins.resize(fft->getBinSize());
    middleBins.resize(fft->getBinSize());
    audioBins.resize(fft->getBinSize());
}

void soundInput::update() {
    soundMutex.lock();
    drawBins = middleBins;
    soundMutex.unlock();
}

void soundInput::draw() {
    ofSetColor(255);
    ofPushMatrix();
    ofTranslate(16, 16);
    
    ofDrawBitmapString("Frequency Domain", 0, 0);
    plot(drawBins, -plotHeight, plotHeight / 2);
    ofPopMatrix();
    string msg = ofToString((int) ofGetFrameRate()) + " fps";
    ofDrawBitmapString(msg, ofGetWidth() - 80, ofGetHeight() - 20);
}

void soundInput::plot(vector<float>& buffer, float scale, float offset) {
    ofNoFill();
    int n = buffer.size();
    ofDrawRectangle(0, 0, n, plotHeight);
    glPushMatrix();
    glTranslatef(0, plotHeight / 2 + offset, 0);
    ofBeginShape();
    for (int i = 0; i < n; i++) {
        ofVertex(i, sqrt(buffer[i]) * scale);
    }
    ofEndShape();
    glPopMatrix();
}

void soundInput::audioReceived(float* input, int bufferSize, int nChannels) {
    // Max value
    float maxValue = 0;
    std::vector<float> inputbuf;
    for(int i = 0; i < bufferSize; i++) {
        if(abs(input[i]) > maxValue) {
            maxValue = abs(input[i]);
        }
        inputbuf.push_back(input[i]);
    }
    for(int i = 0; i < bufferSize; i++) {
        input[i] /= maxValue;
    }
    
    // Input
    fft->setSignal(input);
    
    float* curFft = fft->getAmplitude();
    memcpy(&audioBins[0], curFft, sizeof(float) * fft->getBinSize());
    
    maxValue = 0;
    for(int i = 0; i < fft->getBinSize(); i++) {
        if(abs(audioBins[i]) > maxValue) {
            maxValue = abs(audioBins[i]);
        }
    }
    for(int i = 0; i < fft->getBinSize(); i++) {
        audioBins[i] /= maxValue;
    }
    
    soundMutex.lock();
    middleBins = audioBins;
    soundMutex.unlock();
}

vector<float> soundInput::getAnalyzed(){
    return drawBins;
}

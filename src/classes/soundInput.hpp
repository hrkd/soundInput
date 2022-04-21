//
//  soundInput.hpp
//  soundInputBase
//
//  Created by YOHEI KAJIWARA on 2022/03/10.
//

#ifndef soundInput_hpp
#define soundInput_hpp

#include "ofMain.h"
#include "ofxFft.h"

class soundInput : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    vector<float> getAnalyzed();
private:
    void audioReceived(float* input, int bufferSize, int nChannels);
    void plot(vector<float>& buffer, float scale, float offset);

    // FFT
    ofxFft* fft;
    ofMutex soundMutex;
    vector<float> drawBins, middleBins, audioBins;
    int plotHeight, bufferSize;
};

#endif /* soundInput_hpp */

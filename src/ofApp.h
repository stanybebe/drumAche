#pragma once

#include "ofMain.h"
#include "oscillator.hpp"
#include "biquadFilter.hpp"
#include "knob.h"
#include "panner.hpp"
#include "lerp.hpp"
#include "adsr.hpp"
#include "envUI.hpp"
#include "toggle.h"
#include "pad.h"
#include "ofxMidi.h"
#include "delay.hpp"
#include "xy.h"

class Steps : public ofBaseApp{
    
public:
    
    vector<toggle> vecSteps;
    int numSteps = 0;
    void setup(){
        vecSteps.reserve(numSteps);
        for (int i = 0; i<numSteps; i++) {
            vecSteps.push_back(toggle());
        }
    }
    
    
};

class voice : public ofBaseApp {
public:
    
    
    //      void setup(float freq_, double phase_, int sampleRate_, float amp_,
    //                 float freq_2, double phase_2,float amp_2,int type, double Fc, double Q, double peakGainDB
    //                 );
    //
    void process();
    oscillator osc;
    oscillator op1;
    Biquad* filter;
    adsr* ADSR;
    adsr* ADSR_2;
    delayIn* d_in1;
    delayOut* d_out1;
    
    void setup(float freq_, double phase_, int sampleRate_, float amp_,
               float freq_2, double phase_2, float amp_2, int type, double Fc,
               double Q){
        
        osc.setup(440, 0, sampleRate_, .02);
        filter = new Biquad(bq_type_lowpass, 0/(float)sampleRate_,2,-3);
        ADSR = new adsr(0,10,0,30,sampleRate_);
        ADSR_2 = new adsr(0,10,0,30,sampleRate_);
        d_in1 = new delayIn(10000, sampleRate_);
        d_out1 = new delayOut(d_in1, 800);
    }
    
};

class sequencer: public ofBaseApp {
public:
    pad plusStepA;
    pad minusStepA;
    Steps vS;
    voice drumA;
    Biquad* drumASmoothSample;
    Biquad* smootherD;
    Biquad* smootherG;
    Biquad* smootherH;
    Biquad* smootherI;
    Biquad* smootherJ;
    Biquad* smootherK;
    Biquad* smootherL;
    Biquad* smootherM;
    Biquad* smootherN;
    Biquad* smootherO;
    Biquad* smootherP;
    knob knobA, knobB;
    int stepi;
    int aPadCounter = 20;
    bool apadTrig = false;
    int bPadCounter = 20;
    bool bpadTrig = false;
    bool bangA = false;
    int bangAcounter = 0;
    int currentStep = 0;
    adsr* ADSR;
    envui env1;
    adsr* ADSR_2;
    envui env2;
    float output=0;
    float t = 0;
    
    void setup(int sampleRate, int x, int y){
        plusStepA.setup(440);
        minusStepA.setup(440);
        vS.setup();
        drumA.setup(440, 0, sampleRate, .1, 50, 0, .1, bq_type_lowpass, 2000, .35);
        smootherG = new Biquad(bq_type_lowpass, 1/(float)sampleRate,1,-3);
        smootherD = new Biquad(bq_type_lowpass, 5000/(float)sampleRate,1,-3);
        smootherH = new Biquad(bq_type_lowpass, 5000/(float)sampleRate,1,-3);
        smootherI = new Biquad(bq_type_lowpass, 5000/(float)sampleRate,1,-3);
        smootherJ = new Biquad(bq_type_lowpass, 500/(float)sampleRate,1,-3);
        smootherK = new Biquad(bq_type_lowpass, 500/(float)sampleRate,1,-3);
        smootherL = new Biquad(bq_type_lowpass, 500/(float)sampleRate,1,-3);
        smootherM = new Biquad(bq_type_lowpass, 500/(float)sampleRate,1,-3);
        smootherN = new Biquad(bq_type_lowpass, 500/(float)sampleRate,1,-3);
        smootherO = new Biquad(bq_type_lowpass, 500/(float)sampleRate,1,-3);
        smootherP = new Biquad(bq_type_lowpass, 500/(float)sampleRate,1,-3);
        drumASmoothSample = new Biquad(bq_type_lowpass, 1000/(float)sampleRate,1,-3);
        env1.setup(x,y);
        env2.setup(x,y+120);
        knobA.setup();
        knobA.value=1;
        knobB.setup();
        drumA.d_out1->setTime((.1));
        
        
        
    };
    
    void draw(int pad_x, int pad_y,int step_x, int step_y, int knob_x, int knob_y, float clock_in){
        plusStepA.draw(pad_x, pad_y);
        if (plusStepA.value ==1) {
            apadTrig= true;
        }
        if(apadTrig == true){
            aPadCounter=aPadCounter-1;
        }
        if(aPadCounter==0){
            aPadCounter = 20;
            apadTrig = false;
            stepi = stepi+ 1;
            if (stepi>8){
                stepi=8;
            }
            
            vS.numSteps = stepi;
            
            vS.setup();
            
            for (int i=0; i<vS.numSteps; i++) {
                vS.vecSteps[i].toggle::setup();
            }
        }
        if (vS.numSteps != 0){
            minusStepA.draw(pad_x-60,pad_y);
            for (int i=0; i<vS.numSteps; i++) {
                vS.vecSteps[i].toggle::draw(step_x+(i*50), step_y);
            }
        }
        
        if(minusStepA.value==1){
            bpadTrig= true;
        }
        if(bpadTrig == true){
            bPadCounter=bPadCounter-1;
        }
        if(bPadCounter==0){
            bPadCounter=20;
            bpadTrig=false;
            stepi = stepi-1;
            vS.numSteps = stepi;
            if (vS.numSteps != 0){
                vS.setup();
                for (int i=0; i<vS.numSteps; i++) {
                    vS.vecSteps[i].toggle::setup();
                }
            }
        }
        t++;
        if(t>=clock_in){
            t=0;
            drumA.ADSR->setGate(0);
            drumA.ADSR_2->setGate(0);
            currentStep = currentStep+1;
            if (vS.vecSteps.size() != 0){
                if (vS.vecSteps[currentStep-1].toggle::value == 1) {
                    drumA.ADSR->setGate(1);
                    drumA.ADSR_2->setGate(1);
                }
                else{
                    drumA.ADSR->setGate(0);
                    drumA.ADSR_2->setGate(0);
                    
                }
            }
        }
        
        if(currentStep > vS.numSteps){
            currentStep = 0;
        }
        
        ofPushMatrix();
        env1.draw(10,1000,2,500,1,500);
        env2.draw(10,1000,2,500,1,500);
        knobA.draw(knob_x, knob_y, 1000, 10);
        knobB.draw(knob_x, knob_y+150, .08, 0);
        
        ofPopMatrix();
        
        drumA.osc.setAmp(smootherD->process(knobB.value));
        
    }
    
    void processBlock(int type){
        drumA.d_out1->setTime(smootherG->process(knobA.value));
        float currentS = 0;
        switch (type) {
            case 0:
                currentS += drumASmoothSample->process(drumA.osc.getSine());
                break;
            case 1:
                currentS += drumASmoothSample->process(drumA.osc.getNoise());
            case 2:
                currentS += drumASmoothSample->process(drumA.osc.getSaw());
                
            default:
                currentS += drumASmoothSample->process(drumA.osc.getSine());
                break;
        }
        currentS += drumASmoothSample->process(drumA.osc.getSine());
        
        drumA.ADSR->aTime = smootherL->process(env1.attackV);
        drumA.ADSR->dTime = smootherM->process(env1.decayV);
        drumA.ADSR->sTime = smootherN->process(env1.susV);
        drumA.ADSR->rTime = smootherO->process(env1.relV);
        
        drumA.ADSR_2->aTime = smootherH->process(env2.attackV);
        drumA.ADSR_2->dTime = smootherI->process(env2.decayV);
        drumA.ADSR_2->sTime = smootherJ->process(env2.susV);
        drumA.ADSR_2->rTime = smootherK->process(env2.relV);
        
        float fRamp = ofMap(drumA.ADSR_2->getVal(), 0, 1, 390, 100);
        drumA.osc.setFreq(fRamp);
        
        
        drumA.ADSR -> process();
        drumA.ADSR_2 -> process();
        
        
        currentS *= drumA.ADSR->getVal();
        
        //        filter->setFc(smoother->process(fRamp/float(sampleRate)+(clock.value/float(sampleRate))));
        //        currentS = filter->process(currentS);
        //        currentS = HighPass->process(currentS);
        float dOutSample = drumA.d_out1->getSample();
        
        drumA.d_in1->feed(currentS+(dOutSample*.7));
        output = currentS + dOutSample;
        return output;
    }
};







class ofApp : public ofBaseApp, public ofxMidiListener  {
    
public:
    void setup();
    void update();
    void draw();
    void exit();
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void audioOut(ofSoundBuffer & buffer);
    void newMidiMessage(ofxMidiMessage& eventArgs);
    
    int sampleRate;
    
    ofSoundStream soundStream;
    
    vector <float> lAudio;
    vector <float> rAudio;
    static const int numOsc = 12;
//
//    Steps vS,vSb;
//    voice drumA, drumB;
    
    //    oscillator osc;
    //    oscillator oscB;
    //    oscillator oscC;
    //    oscillator oscD;
    
//
//    vector <int> queueDaddy;
    //    oscillator autoPan;
    //    oscillator vib;
    //    oscillator vib2;
    //
    //    oscillator op1;
    //    Biquad* filter;
//    Biquad* smoother;
//    Biquad* smootherB;
//    Biquad* smootherC;
//    Biquad* smootherD;
//    Biquad* smootherF;
//    Biquad* smootherG;
//    Biquad* smootherH;
//    Biquad* smootherI;
//    Biquad* smootherJ;
//    Biquad* smootherK;
//    Biquad* smootherL;
//    Biquad* smootherM;
//    Biquad* smootherN;
//    Biquad* smootherO;
//    Biquad* smootherP;
//    Biquad* smootherQ;
//    Biquad* smootherR;
//    Biquad* smootherS;
//    Biquad* smootherT;
//    Biquad* smootherU;
//    Biquad* smootherV;
//    Biquad* drumASmoothSample;
//    Biquad* drumBSmoothSample;
//    Biquad* HighPass;
    
//    bool noteOn =false;
//
    knob clock;
//    pad padA;
//    pad plusStepA;
//    pad minusStepA;
//    pad plusStepB;
//    pad minusStepB;
//
//    Panner pans;
    
    //lerpVal smooth;
//    stereoFrame currentPanFrame;
//    int stepi;
//    float t = 0;
//    int aPadCounter = 20;
//    bool apadTrig = false;
//    int bPadCounter = 20;
//    bool bpadTrig = false;
//    bool bangA = false;
//    int bangAcounter = 0;
//    int currentStep = 0;
//
//    adsr* ADSR;
//    envui env1;
//    adsr* ADSR_2;
//    envui env2;
//    adsr* ADSR_3;
//    envui env3;
//    adsr* ADSR_4;
//    envui env4;
    
    xy XY;
    
    
    
    ofxMidiIn midiIn;
    std::vector<ofxMidiMessage> midiMessages;
    std::size_t maxMessages = 10; //< max number of messages to keep track of
//
//    delayIn* d_in1;
//    delayOut* d_out1;
//    delayIn* d_in2;
//    delayOut* d_out2;
//    int v , vo;
//
    sequencer SeqA, SeqB;
    
    double mtofarray[129]={0, 8.661957, 9.177024, 9.722718, 10.3, 10.913383, 11.562325, 12.25, 12.978271, 13.75, 14.567617, 15.433853, 16.351599, 17.323914, 18.354048, 19.445436, 20.601723, 21.826765, 23.124651, 24.5, 25.956543, 27.5, 29.135235, 30.867706, 32.703197, 34.647827, 36.708096, 38.890873, 41.203445, 43.65353, 46.249302, 49., 51.913086, 55., 58.27047, 61.735413, 65.406395, 69.295654, 73.416191, 77.781746, 82.406891, 87.30706, 92.498604, 97.998856, 103.826172, 110., 116.540939, 123.470825, 130.81279, 138.591309, 146.832382, 155.563492, 164.813782, 174.61412, 184.997208, 195.997711, 207.652344, 220., 233.081879, 246.94165, 261.62558, 277.182617,293.664764, 311.126984, 329.627563, 349.228241, 369.994415, 391.995422, 415.304688, 440., 466.163757, 493.883301, 523.25116, 554.365234, 587.329529, 622.253967, 659.255127, 698.456482, 739.988831, 783.990845, 830.609375, 880., 932.327515, 987.766602, 1046.502319, 1108.730469, 1174.659058, 1244.507935, 1318.510254, 1396.912964, 1479.977661, 1567.981689, 1661.21875, 1760., 1864.655029, 1975.533203, 2093.004639, 2217.460938, 2349.318115, 2489.015869, 2637.020508, 2793.825928, 2959.955322, 3135.963379, 3322.4375, 3520., 3729.31, 3951.066406, 4186.009277, 4434.921875, 4698.63623, 4978.031738, 5274.041016, 5587.651855, 5919.910645, 6271.926758, 6644.875, 7040., 7458.620117, 7902.132812, 8372.018555, 8869.84375, 9397.272461, 9956.063477, 10548.082031, 11175.303711, 11839.821289, 12543.853516, 13289.75};
    
    int voiceCounter(bool is_on){
        
        int counter=0;
        bool isOn = false;
        isOn = is_on;
        
        if (isOn ==true){
            counter++;
        }else {counter = 0;}
        
        return counter;
    }
    
    
    int largest(int arr[], int n)
    {
        int i;
        
        // Initialize maximum element
        int max = arr[0];
        
        // Traverse array elements
        // from second and compare
        // every element with current max
        for (i = 1; i < n; i++)
            if (arr[i] > max)
                max = arr[i];
        
        return max;
    }
};





#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    midiIn.listInPorts();
    midiIn.openPort(4);
    
    midiIn.ignoreTypes(false, false, false);
    
    // add ofApp as a listener
    midiIn.addListener(this);
    
    // print received messages to the console
    midiIn.setVerbose(true);
    sampleRate = 48000;
    //channels out / in/ sampleRate/ block size/ buffer#
    int bufferSize= 512;
    ofSoundStreamSettings settings;
    settings.setOutListener(this);
    settings.sampleRate = sampleRate;
    settings.numOutputChannels = 2;
    settings.numInputChannels = 0;
    settings.bufferSize = 512;
    soundStream.setup(settings);
    soundStream.printDeviceList();
    auto devices = soundStream.getDeviceList();
    settings.setOutDevice(devices[4]);
    lAudio.assign(bufferSize, 0.0);
    rAudio.assign(bufferSize, 0.0);
    
//    drumA.setup(440, 0, sampleRate, .1, 50, 0, .1, bq_type_lowpass, 2000, .35);
//
//
//    smoother = new Biquad(bq_type_lowpass, 5000/(float)sampleRate,2,-3);
//    smootherB = new Biquad(bq_type_lowpass, 1000/(float)sampleRate,1,-3);
//    smootherC = new Biquad(bq_type_lowpass, 10000/(float)sampleRate,1,-3);
//    smootherD = new Biquad(bq_type_lowpass, 5000/(float)sampleRate,1,-3);
//    smootherF = new Biquad(bq_type_lowpass, 1000/(float)sampleRate,1,-3);
//    smootherG = new Biquad(bq_type_lowpass, 1/(float)sampleRate,1,-3);
//    smootherH = new Biquad(bq_type_lowpass, 5000/(float)sampleRate,1,-3);
//    smootherI = new Biquad(bq_type_lowpass, 5000/(float)sampleRate,1,-3);
//    smootherJ = new Biquad(bq_type_lowpass, 500/(float)sampleRate,1,-3);
//    smootherK = new Biquad(bq_type_lowpass, 500/(float)sampleRate,1,-3);
//    smootherL = new Biquad(bq_type_lowpass, 500/(float)sampleRate,1,-3);
//    smootherM = new Biquad(bq_type_lowpass, 500/(float)sampleRate,1,-3);
//    smootherN = new Biquad(bq_type_lowpass, 500/(float)sampleRate,1,-3);
//    smootherO = new Biquad(bq_type_lowpass, 500/(float)sampleRate,1,-3);
//    smootherP = new Biquad(bq_type_lowpass, 500/(float)sampleRate,1,-3);
//    smootherQ = new Biquad(bq_type_lowpass, 500/(float)sampleRate,1,-3);
//    smootherR = new Biquad(bq_type_lowpass, 500/(float)sampleRate,1,-3);
//    smootherS = new Biquad(bq_type_lowpass, 500/(float)sampleRate,1,-3);
//    smootherT = new Biquad(bq_type_lowpass, 500/(float)sampleRate,1,-3);
//    smootherU = new Biquad(bq_type_lowpass, 500/(float)sampleRate,1,-3);
//    smootherV = new Biquad(bq_type_lowpass, 500/(float)sampleRate,1,-3);
//    drumASmoothSample = new Biquad(bq_type_lowpass, 1000/(float)sampleRate,1,-3);
//    drumBSmoothSample = new Biquad(bq_type_lowpass, 1000/(float)sampleRate,1,-3);
//    HighPass = new Biquad(bq_type_highpass, 20/(float)sampleRate,1,-3);
//
//    knobA.setup();
//    knobA.value=1;
//
    clock.setup();
//
//    knobC.setup();
//    knobD.setup();
//
//    knobD.value=1;
//    knobE.setup();
//    //
//    //
//    //
//    //    autoPan.setup(1, 0, sampleRate, 1);
//    //    vib.setup(1, 0, sampleRate, 1);
//    //    op1.setup(0,0,sampleRate, 1);
//    //    ADSR = new adsr(0,10,0,30,sampleRate);
//    env1.setup(110,10);
//    env2.setup(110,130);
//
//
//    //      padA.setup(440);
//    plusStepA.setup(440);
//    minusStepA.setup(440);
//
//    //
//    //    d_in1 = new delayIn(10000, sampleRate);
//    //    d_out1 = new delayOut(d_in1, 800);
//    //
//    //    XY.setup(100, 600);
//    drumA.d_out1->setTime((.1));
//
//
//    vS.setup();
//
//    //    for (int i=0; i<4; i++) {
//    //        vS.vecSteps[i].toggle::setup();
//    //    }
//
    SeqA.setup(sampleRate, 110, 10);
    SeqB.setup(sampleRate, 110, 410);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    XY.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(34, 69, 78);
//    plusStepA.draw(200, 240);
    clock.draw(450, 50, 100, 1);
//
//    if (plusStepA.value ==1) {
//        apadTrig= true;
//    }
//    if(apadTrig == true){
//        aPadCounter=aPadCounter-1;
//    }
//    if(aPadCounter==0){
//        aPadCounter = 20;
//        apadTrig = false;
//        stepi = stepi+ 1;
//        if (stepi>8){
//            stepi=8;
//        }
//
//        vS.numSteps = stepi;
//
//        vS.setup();
//
//        for (int i=0; i<vS.numSteps; i++) {
//            vS.vecSteps[i].toggle::setup();
//        }
//    }
//    if (vS.numSteps != 0){
//        minusStepA.draw(140,240);
//        for (int i=0; i<vS.numSteps; i++) {
//            vS.vecSteps[i].toggle::draw(30+(i*50), 380);
//        }
//    }
//
//    if(minusStepA.value==1){
//        bpadTrig= true;
//    }
//    if(bpadTrig == true){
//        bPadCounter=bPadCounter-1;
//    }
//    if(bPadCounter==0){
//        bPadCounter=20;
//        bpadTrig=false;
//        stepi = stepi-1;
//        vS.numSteps = stepi;
//        if (vS.numSteps != 0){
//            vS.setup();
//            for (int i=0; i<vS.numSteps; i++) {
//                vS.vecSteps[i].toggle::setup();
//            }
//        }
//    }
//
//

//
//    if(t>=clock.value){
//        t=0;
//        drumA.ADSR->setGate(0);
//        drumA.ADSR_2->setGate(0);
//        currentStep = currentStep+1;
//        if (vS.numSteps != 0){
//            if (vS.vecSteps[currentStep].toggle::value == 1) {
//                drumA.ADSR->setGate(1);
//                drumA.ADSR_2->setGate(1);
//            }
//            else{
//                drumA.ADSR->setGate(0);
//                drumA.ADSR_2->setGate(0);
//
//            }
//        }
//    }
//
//    if(currentStep >= vS.numSteps){
//        currentStep = 0;
//    }
//
//
//
//
//
//    cout << currentStep<<endl;
//    ofPushMatrix();
//    env1.draw(10,1000,20,500,10,500);
//    env2.draw(10,1000,20,500,10,500);
//    knobA.draw(50, 50, 1000, 10);
//    knobC.draw(50, 150, .8, 0);
//    ofPopMatrix();
//
//    drumA.osc.setAmp(smootherD->process(knobC.value));
//    //    padA.draw(10, 220);
//
//    //    if (padA.value == true){
//    //
//    //        drumA.ADSR->setGate(1);
//    //        drumA.ADSR_2->setGate(1);
//    //
//    //    }else{drumA.ADSR->setGate(0); drumA.ADSR_2->setGate(0);}
    
    SeqA.draw(200, 240,30,380, 50, 50, clock.value);
    SeqB.draw(200, 640,30,780, 50, 450, clock.value);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
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

void ofApp::newMidiMessage(ofxMidiMessage& msg) {
    
    // add the latest message to the message queue
    midiMessages.push_back(msg);
    
    // remove any old messages if we have too many
    while(midiMessages.size() > maxMessages) {
        midiMessages.erase(midiMessages.begin());
    }
}

void ofApp::audioOut(ofSoundBuffer & buffer){
    
    for (int i = 0; i<buffer.getNumFrames();i++){
//        drumA.d_out1->setTime(smootherG->process(knobA.value));
//        float currentS = 0;
//
//        currentS += drumASmoothSample->process(drumA.osc.getSine());
//
//        drumA.ADSR->aTime = smootherL->process(env1.attackV);
//        drumA.ADSR->dTime = smootherM->process(env1.decayV);
//        drumA.ADSR->sTime = smootherN->process(env1.susV);
//        drumA.ADSR->rTime = smootherO->process(env1.relV);
//
//        drumA.ADSR_2->aTime = smootherH->process(env2.attackV);
//        drumA.ADSR_2->dTime = smootherI->process(env2.decayV);
//        drumA.ADSR_2->sTime = smootherJ->process(env2.susV);
//        drumA.ADSR_2->rTime = smootherK->process(env2.relV);
//
//        float fRamp = ofMap(drumA.ADSR_2->getVal(), 0, 1, 390, 100);
//        drumA.osc.setFreq(fRamp);
//
//
//        drumA.ADSR -> process();
//        drumA.ADSR_2 -> process();
//
//
//
//        currentS *= drumA.ADSR->getVal();
        
        //        filter->setFc(smoother->process(fRamp/float(sampleRate)+(clock.value/float(sampleRate))));
        //        currentS = filter->process(currentS);
//        //        currentS = HighPass->process(currentS);
//        float dOutSample = drumA.d_out1->getSample();
//
//        drumA.d_in1->feed(currentS+(dOutSample*.7));
        //        dOutSample = HighPass->process(dOutSample);
        //        currentPanFrame = pans.pan(currentS + dOutSample, autoPan.getSine());
        
        
//
//        lAudio[i] =buffer[i*buffer.getNumChannels()+0] =currentS + dOutSample;
//        rAudio[i] = buffer[i*buffer.getNumChannels()+1] =currentS + dOutSample;
        
        SeqA.processBlock(0);
        SeqB.processBlock(1);
        lAudio[i] =buffer[i*buffer.getNumChannels()+0] =SeqA.output+SeqB.output;
        rAudio[i] = buffer[i*buffer.getNumChannels()+1] =SeqA.output+SeqB.output;
    }
    
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

void ofApp::exit(){
    ofSoundStream().close();
    midiIn.closePort();
    midiIn.removeListener(this);
}



#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    midiIn.listInPorts();
    midiIn.openPort(4);
    //midiIn.openPort("IAC Pure Data In");    // by name
    //midiIn.openVirtualPort("ofxMidiIn Input"); // open a virtual port
    
    // don't ignore sysex, timing, & active sense messages,
    // these are ignored by default
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
    
    osc.setup(440, 0, sampleRate, .02);
    oscB.setup(440, 0, sampleRate, .02);
    oscC.setup(440, 0, sampleRate, .02);
    oscD.setup(440, 0, sampleRate, .02);
//    for (int i =0; i < numOsc; i++){
//        osc[i].setup(440*(i+.5), 0, sampleRate, 1/ (float)(i+1));
//        oscB[i].setup(440*(i+.5), 0, sampleRate, 1/ (float)(i+1));
//        oscC[i].setup(440*(i+.5), 0, sampleRate, 1/ (float)(i+1));
//        oscD[i].setup(440*(i+.5), 0, sampleRate, 1/ (float)(i+1));
//
//    }
//
    filter = new Biquad(bq_type_lowpass, 0/(float)sampleRate,2,-3);
    smoother = new Biquad(bq_type_lowpass, 5000/(float)sampleRate,2,-3);
    smootherB = new Biquad(bq_type_lowpass, 1000/(float)sampleRate,1,-3);
    smootherC = new Biquad(bq_type_lowpass, 10000/(float)sampleRate,1,-3);
    smootherD = new Biquad(bq_type_lowpass, 5000/(float)sampleRate,1,-3);
    smootherF = new Biquad(bq_type_lowpass, 1000/(float)sampleRate,1,-3);
    smootherG = new Biquad(bq_type_lowpass, 1/(float)sampleRate,1,-3);
    smootherH = new Biquad(bq_type_lowpass, 5000/(float)sampleRate,1,-3);
    smootherI = new Biquad(bq_type_lowpass, 5000/(float)sampleRate,1,-3);
    smootherJ = new Biquad(bq_type_lowpass, 500/(float)sampleRate,1,-3);
    smootherK = new Biquad(bq_type_lowpass, 500/(float)sampleRate,1,-3);
     smootherL = new Biquad(bq_type_lowpass, 500/(float)sampleRate,1,-3);
     smootherM = new Biquad(bq_type_lowpass, 500/(float)sampleRate,1,-3);
     smootherN = new Biquad(bq_type_lowpass, 500/(float)sampleRate,1,-3);
     smootherO = new Biquad(bq_type_lowpass, 500/(float)sampleRate,1,-3);
     smootherP = new Biquad(bq_type_lowpass, 500/(float)sampleRate,1,-3);
     smootherQ = new Biquad(bq_type_lowpass, 500/(float)sampleRate,1,-3);
     smootherR = new Biquad(bq_type_lowpass, 500/(float)sampleRate,1,-3);
     smootherS = new Biquad(bq_type_lowpass, 500/(float)sampleRate,1,-3);
    smootherT = new Biquad(bq_type_lowpass, 1000/(float)sampleRate,1,-3);
    HighPass = new Biquad(bq_type_highpass, 20/(float)sampleRate,1,-3);
  
    knobA.setup();
    knobB.setup();
    knobC.setup();
    knobD.setup();
    knobE.setup();
    knobF.setup();


 
    autoPan.setup(1, 0, sampleRate, 1);
    vib.setup(1, 0, sampleRate, 1);
    vib2.setup(1, 0, sampleRate, 1);
    op1.setup(0,0,sampleRate, 1);
    ADSR = new adsr(0,10,0,30,sampleRate);
    ADSR_2 = new adsr(0,10,0,30,sampleRate);
    env1.setup(300,550);
    env2.setup(300,680);
   // padA.setup(440);
    
    d_in1 = new delayIn(10000, sampleRate);
    d_out1 = new delayOut(d_in1, 800);
    
    knobC.value = .01;
    knobA.value = 100;
    XY.setup(100, 600);
    for (int i = 0; i < 4; i++){
   
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    XY.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(34, 69, 78);
   for( int i = 0; i < midiMessages.size(); i++) {
   
        ofxMidiMessage &message = midiMessages[i];
       if (message.status == MIDI_NOTE_ON){
           noteOn = true;
          
           cout << "midiComingOut"<<endl;
           
       }
       
       if (noteOn ==true){
         ADSR->setGate(1);
         ADSR_2->setGate(1);
        
           
           queueDaddy.push_back(message.pitch);
          
           if(queueDaddy.size() >= 5){
                queueDaddy.erase(queueDaddy.begin());
           }

       }
       
       if (message.status == MIDI_NOTE_OFF){
           ADSR->setGate(0);
           ADSR_2->setGate(0);
           noteOn = false;
           std::cout << message.pitch<< "_____PITCH/n";
           
           std::cout << "queueDaddy:before \n";
           for (unsigned int i=0; i<queueDaddy.size() ;i++){
               
               cout << queueDaddy[i]<<" ";
               
               
           }
           std::cout << "new-------------------\n";
//           std::remove(queueDaddy.begin(),queueDaddy.end(),message.pitch);
           
           if ( !queueDaddy.empty()){
           for (int i = int(queueDaddy.size())-1; i >= 0 ; i--){
               cout << queueDaddy.size() << " " << i <<" size/n";
               if (queueDaddy[i]==message.pitch&&message.status==MIDI_NOTE_OFF){
                  queueDaddy.erase(queueDaddy.begin()+i);
               }
               
           }
           }
           
           std::cout << "queueDaddy:after \n";
           for (unsigned int i=0; i<queueDaddy.size() ;i++){
               
               cout << queueDaddy[i]<<" ";
               
               
           }
           std::cout << "new-------------------\n";

       }


     
   }

    

    std::cout << "queueDaddy: \n";
    for (unsigned int i=0; i<queueDaddy.size() ;i++){
        
        cout << queueDaddy[i]<<" ";
        
        
    }
    std::cout << "new-------------------\n";
    

    ofPushMatrix();
    env1.draw(10,1000,20,500,10,500);
    env2.draw(10,1000,20,500,10,500);
    ofPopMatrix();
    // draw the left channel:
  
    
    ofPushStyle();
    ofNoFill();
        ofPushMatrix();
        ofTranslate(50, 150, 0);
            

       

        ofSetColor(206, 247, 214);
        ofSetLineWidth(3);
                    
            
            for (unsigned int i = 0; i < lAudio.size(); i++){
                float x =  ofMap(i, 0, lAudio.size(), 0, 500, true);
                ofVertex(x, 100 -lAudio[i]*100.0f);
            }
           
            
        ofPopMatrix();
        ofPushMatrix();
           ofTranslate(50, 225, 0);
               
        
           
       

           ofSetColor(206, 247, 214);
           ofSetLineWidth(3);
     
               ofBeginShape();
               for (unsigned int i = 0; i < rAudio.size(); i++){
                   float x =  ofMap(i, 0, rAudio.size(), 0, 500, true);
                   ofVertex(x, 100 -rAudio[i]*100.0f);
               }
               ofEndShape(false);
               
           ofPopMatrix();
    ofPopStyle();


     ofPushMatrix();
    knobA.draw(150, 150, 1000, 10);
    knobB.draw(450, 150, 7000, 1);
    knobC.draw(150, 450, .2, .01);
    knobD.draw(450, 450, 12, 0);
    knobE.draw(300, 150, 10, 0);
    knobF.draw(300, 450, 1, .001);
    ofPopMatrix();
    
    t++;
    tempo= XY.valueX;
   

    if ( t > tempo) {
     ran = ofRandom(0, XY.valueY);
      t = 0;
    }
//
//    if (t > tempo - len) {
//      Note = 0;
//    }

//    if (timer == true) {
//         yep = round(ofRandom(0, 8));
//        stepi = stepi + 1;
//        timer = false;
//      if (stepi > 7) {
//        stepi = 0;
//      }
//    }
//
  
    
  
    op1.setFreq(smootherF->process((knobF.value)));
    
    op1.setAmp(.5);
    
    autoPan.setFreq(smootherB->process(knobE.value));
    
//    vib.setFreq(smootherJ->process(XY.valueX+ran));
//    vib.setFreq(smootherK->process(XY.valueY+ran));
//    for (int j = 0; j<voices.size();j++){
   
  

    
   
         
            if(queueDaddy.size()> 0){
              osc.setFreq(mtofarray[queueDaddy[0]]);
              osc.setAmp(smootherD->process(knobC.value));
            }
            
            if(queueDaddy.size()> 1){
              oscB.setFreq(mtofarray[queueDaddy[1]]);
              oscB.setAmp(smootherD->process(knobC.value));
            }
//
            if(queueDaddy.size()> 2){
              oscC.setFreq(mtofarray[queueDaddy[2]]);
              oscC.setAmp(smootherD->process(knobC.value));
            }

            if(queueDaddy.size()> 3){
              oscD.setFreq(mtofarray[queueDaddy[3]]);
              oscD.setAmp(smootherD->process(knobC.value));
            }
//
//              oscB[k].setFreq(smootherG->process(mtofarray[voices[1]])*(k+round(knobD.value)));
//              oscB[k].setAmp(smootherD->process(knobC.value));
//              oscC[k].setFreq(smootherH->process(mtofarray[voices[2]])*(k+round(knobD.value)));
//              oscC[k].setAmp(smootherD->process(knobC.value));
//              oscD[k].setFreq(smootherI->process(mtofarray[voices[3]])*(k+round(knobD.value)));
//              oscD[k].setAmp(smootherD->process(knobC.value));
//
         
                                                          
    
    
    
   // padA.draw(100, 540);
    
//    if (padA.value == true){
//
//        ADSR->setGate(1);
//
//    }else{ADSR->setGate(0);}
//
  
    
    
//   cout << ADSR->aTime<<"aTIME"<<endl;
//    cout << ADSR->dTime<<"dTIME"<<endl;
//    cout << ADSR->sTime<<"sTIME"<<endl;
//    cout << ADSR->rTime<<"rTIME"<<endl;
    XY.draw(100, 600);


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
      
        d_out1->setTime(smootherG->process(knobA.value));
        float currentS = 0;
//        for(int j = 0; j < numOsc; j++){
            currentS += smootherT->process((osc.getSaw()
                         + oscB.getSaw()
                         + oscC.getSaw()
                         + oscD.getSaw()) * op1.getSine());
//                         * op1.getSine() * vib.getSine();
        
//        }
        
       

        ADSR->aTime = smootherL->process(env1.attackV);
        ADSR->dTime = smootherM->process(env1.decayV);
        ADSR->sTime = smootherN->process(env1.susV);
        ADSR->rTime = smootherO->process(env1.relV);
//        std::cout << env1.susV<<"env1.susV/n";
        
        ADSR_2->aTime = smootherP->process(env2.attackV);
        ADSR_2->dTime = smootherQ->process(env2.decayV);
        ADSR_2->sTime = smootherR->process(env2.susV);
        ADSR_2->rTime = smootherS->process(env2.relV);
//        std::cout << env2.susV<<"env2.susV/n";
        
        
        ADSR -> process();
        ADSR_2 -> process();
        
        
        currentS *= ADSR->getVal();
        float fRamp = ofMap(ADSR_2->getVal(), 0, 1, 10, 2000);
        filter->setFc(smoother->process(fRamp/float(sampleRate)+(knobB.value/float(sampleRate))));
        currentS = filter->process(currentS);
//        currentS = HighPass->process(currentS);
        float dOutSample = d_out1->getSample();
     
        d_in1->feed(currentS+(dOutSample*.7));
        dOutSample = HighPass->process(dOutSample);
        
       
        currentPanFrame = pans.pan(currentS + dOutSample, autoPan.getSine());
        
        lAudio[i] =buffer[i*buffer.getNumChannels()+0] = currentPanFrame.leftSamp ;
        rAudio[i] = buffer[i*buffer.getNumChannels()+1] = currentPanFrame.rightSamp ;
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


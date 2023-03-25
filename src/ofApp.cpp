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
    
    clock.setup();
    
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



#include "ofApp.h"

ofImage currentFrame;
ofImage currentFrameCopy;
int histogram[256];
int histogramMax = 0;
int maxIndex = 0;
int threshold;


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(15);
	
    ofBackground(255);
	
	camWidth 		= 640;	// try to grab at this size. 
	camHeight 		= 480;
    
    currentFrame.allocate(camWidth, camHeight, OF_IMAGE_GRAYSCALE);
	
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(camWidth,camHeight);

    font.loadFont("Courier New Bold.ttf", 9);
    
    ofEnableAlphaBlending();
    
}


//--------------------------------------------------------------
void ofApp::update(){
	vidGrabber.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //Merci Ludo pour ton aide
	
    currentFrame = vidGrabber.getPixelsRef();
    currentFrameCopy.allocate(currentFrame.getWidth(), currentFrame.getHeight(), OF_IMAGE_GRAYSCALE);


    for(int x=0 ; x < 256 ; x++) {
        histogram[x] = 0;
    }

    
    for (int i = 0; i < camWidth; i++){
        for (int j = 0; j < camHeight; j++){
            int lightness = currentFrame.getColor(i,j).getLightness();
            histogram[lightness] = histogram[lightness]+1;
            ofColor pixel;
            pixel.set(lightness, lightness, lightness);
            currentFrame.setColor(i, j, pixel);

        }
    }
    
    ofSetHexColor(0xffffff);
    currentFrame.reloadTexture();
    currentFrame.draw(0,0);
    
    ofFill();
	ofSetHexColor(0x000000);
	ofSetPolyMode(OF_POLY_WINDING_ODD);
    
    ofLine(770, 400, 770, 400-255);
    ofLine(770, 400, 770+255, 400);
    
    histogramMax = 0;
    maxIndex = 0;
    for(int x = 0 ; x < 256 ; x++) {
        if (histogram[x]>histogramMax) {
            histogramMax = histogram[x];
            maxIndex = x;
            }
        histogram[x] = histogram[x]/100;
        //cout << x << " : " << histogram[x] << "\n";
        ofLine(x+770, 400-histogram[x], x+770, 400);
    }

    ofSetColor(255,0,0);
    ofLine(maxIndex+770, 400-histogram[maxIndex], maxIndex+770, 400);
    
    ofSetColor(0);
	ofDrawBitmapString("Histogram : ", 770, 100);
	ofDrawBitmapString("0                             255 ", 770, 415);
	ofDrawBitmapString("0", 755, 400);
	ofDrawBitmapString("???", 773, 150);

    threshold = 128;
    for(int y = 0; y < camHeight; y++) {
        for(int x = 0; x < camWidth; x++) {
            ofColor cur = currentFrame.getColor(x, y);
            int lightness = cur.getLightness();
            ofColor pixel;
            if (lightness<threshold) pixel.set(0, 0, 0);
            else pixel.set(255, 255, 255);
            currentFrameCopy.setColor(x, y, pixel);
        }
    }
    
    ofSetColor(255);
    currentFrameCopy.reloadTexture();
    currentFrameCopy.draw(0, 480);


    

}


//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
	
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofxCease(2019, 5, 14, 3, "You have # days left, please contact somemail@somedomain.com for more info.", "Your licence to use this software has ceased. Please contact somemail@somedomain.com for more info.", ofToDataPath("somethingToRemove"));
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofDrawBitmapString("Thank you for paying!", 20, 20);
}

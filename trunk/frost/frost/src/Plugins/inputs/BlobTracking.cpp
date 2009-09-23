#include "PluginController.h"
#include "ProjectionSurfaces.h"
#include "BlobTracking.h"
#include "Cameras.h"
#include "CameraCalibration.h"


Tracker::Tracker(ofxVideoGrabber * _grabber){
	int cw = 1024; int ch=768;
	grabber = _grabber;		
	//	int w = grabber->getWidth();//grabber->width; 
	//	int h = grabber->getHeight();//grabber->height;
	grayImageBlured.allocate(cw,ch);
	grayImage.allocate(cw,ch);
	grayBg.allocate(cw,ch);
	grayDiff.allocate(cw,ch);
	bLearnBakground = true;
}

void Tracker::update(){ 
	bool bNewFrame = false;
	bNewFrame = grabber->isFrameNew();
	if (bNewFrame && active){
		
		grayImage.setFromPixels(grabber->getPixels(), grabber->getWidth(),grabber->getHeight());
		grayImageBlured = grayImage;
		grayImageBlured.blur(blur);
		
		if (bLearnBakground == true){
			grayBg = grayImageBlured;		
			bLearnBakground = false;
		}
		
		grayDiff.absDiff(grayBg, grayImageBlured);
		grayDiff.threshold(threshold);
		
		contourFinder.findContours(grayDiff, 20, (grabber->getWidth()*grabber->getHeight())/3, 10, false, true);	
		
	}
}

void Tracker::findContours(){
}



BlobTracking::BlobTracking(){
	type = INPUT;
	drawDebug = false;
}
void BlobTracking::setup(){
	for(int i=0;i<3;i++){
		trackers.push_back(new Tracker(getPlugin<Cameras*>(controller)->vidGrabber[i]));
		trackers[i]->threshold = initThreshold[i];
		trackers[i]->blur = initBlur[i];
		trackers[i]->active = initActive[i];
	}
}
void BlobTracking::update(){
	//#pragma omp parallel for
	for(int i=0;i<trackers.size();i++){
		trackers[i]->update();		
	}	
	for(int i=0;i<trackers.size();i++){
		trackers[i]->findContours();		
	}	
	
}

void BlobTracking::drawSettings(){
	
	for(int i=0;i<trackers.size();i++){
		ofSetColor(255, 255, 255);
		
		int w = 250;
		float a = 480.0/640.0;
		trackers[i]->grabber->draw(0,w*a*i,w,w*a);
		trackers[i]->grayImageBlured.draw(w,w*a*i,w,w*a);
		trackers[i]->grayBg.draw(w*2,w*a*i, w,w*a);
		trackers[i]->grayDiff.draw(w*3,w*a*i,w,w*a);
		trackers[i]->contourFinder.draw(w*3,w*a*i,w,w*a);
	}
}

void BlobTracking::draw(){
	if(drawDebug){
		ofEnableAlphaBlending();
		glBlendFunc (GL_SRC_COLOR, GL_ONE);	
		
		for(int i=0;i<trackers.size();i++){
			ofSetColor(255, 255, 255);
			glPushMatrix();
			getPlugin<CameraCalibration*>(controller)->applyWarp(i);
			trackers[i]->grayDiff.draw(0,0,1,1);
			
			glPopMatrix();
		}
	}
}

void BlobTracking::setThreshold(int n, float v){
	if(trackers.size() < 1){
		initThreshold[n] = v;
	} else 
		trackers[n]->threshold = v;;
	
}
void BlobTracking::setBlur(int n, int v){
	if(v % 2 == 0){
		v += 1;
	}
	if(trackers.size() < 1){
		initBlur[n] = v;
	} else { 		
		trackers[n]->blur = v;;
	}
	
}

void setActive(int n, bool b);

void BlobTracking::grab(int n){
	if(trackers.size() > n){
		trackers[n]->bLearnBakground = true;
	}
}
void BlobTracking::setActive(int n, bool b){
	if(trackers.size() < 1){
		initActive[n] = b;
	} else 
		trackers[n]->active = b;;
}


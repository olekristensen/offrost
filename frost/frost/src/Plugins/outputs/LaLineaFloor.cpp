
#include "PluginController.h"
#include "PluginIncludes.h"


LaLineaFloor::LaLineaFloor(){
	type = OUTPUT;
	cam = 0;
	time = 0;
	lastTime = 0;

}

void LaLineaFloor::setup(){
	dir = ofxVec2f(1,0);
	reset();
	
}

void LaLineaFloor::update(){
	//cout<<width<<endl;
	time += ofGetFrameRate()/100.0;
	if(blob(cam)->numPersistentBlobs() > 0){
		
		bool itIsClose = false;
		
		ofxPoint2f goal = projection()->convertToFloorCoordinate(blob(cam)->persistentBlobs[0].getLowestPoint());
		if(goal.distance(pos) < 0.10 && time - lastTime > 3.0){
			if(goal.distance(pos) < 0.05) itIsClose = true;
			goal = goal += curlValue*ofxVec2f(ofRandom(-0.5,0.75), ofRandom(-2.0,0.5));
			lastTime = time;
		}
		
		ofxVec2f v = goal - pos;
		v.normalize();
		
		dir += v*(itIsClose?0.01:ofRandom(0.001,0.003));
		dir.normalize();
		if(itIsClose){
			dir *= 2;
		}
		dir *= 0.005;
		
		pos += dir*100.0/ofGetFrameRate()*speed;
		pnts.push_back(pos);

	}
}
void LaLineaFloor::draw(){
	
}

void LaLineaFloor::reset(){
	pnts.clear();
	ofxPoint2f p = projection()->getColumnCoordinate(0);

	pos = p;
	dir = ofxVec2f(-1,0);

}

void LaLineaFloor::drawOnFloor(){
	ofPushStyle();
	glColor4f(1.0, 1.0,1.0, masterAlpha);
	ofEnableSmoothing();
	if(pnts.size() > 1){
		glBegin(GL_QUAD_STRIP);
		
		for(int i=0;i<pnts.size()-1;i++){
			ofxVec2f v = pnts[i+1] - pnts[i];
			ofxVec2f hat;
			hat.x = -v.y;
			hat.y = v.x;
			hat.normalize();
			hat *= 0.02*width;
			glVertex2f(pnts[i].x-hat.x, pnts[i].y-hat.y);
			glVertex2f(pnts[i].x+hat.x, pnts[i].y+hat.y);
		}
		glEnd();
	}
	ofPopStyle();
	
	glPopMatrix();
	
	for(int i=0;i<3;i++){
		projection()->applyProjection(projection()->getColumn(i));
		ofSetColor(0, 0, 0,255)	;
		ofRect(0.0, 0, projection()->getColumn(i)->aspect, 1);
		glPopMatrix();
		
	}
	
}

#pragma once
#include "ofMain.h"
#include "Output.h"
#include "ofxVectorMath.h"
#include "ofxMSASpline.h"
#include "contourSimplify.h"
#include "contourNormals.h"
#include "FrostMotor.h"


class Frostscape : public Output{
public:
	
	Frostscape();
	
	void setup();
	void draw();
	void drawOnFloor();
	void update();
	
	FrostMotor motor;
	
	bool debug;
	int cam;
	
	static float randomFactor;
	static float slider1, slider2, slider3, slider4, slider5, slider6;
	static bool applyToOther;
	
	void setslider1(float val);
	void setslider2(float val);
	void setslider3(float val);
	void setslider4(float val);
	void setslider5(float val);
	void setslider6(float val);
	
	void fillIce();
	void emptyIce();
	
	float sideFreeze;
	float columnFreeze[3];
	float freezeColumns;
	
	bool invert;
	
	float whiteBackground;
	
	float columnParticlePos[3];
	float columnParticleX[3];
	
	bool addingLines;
	float linesAlpha;
	float linesSpeed;
	bool resetLines;
	float freezeLines;
	vector<ofxVec2f> lines[2];
	vector<ofxVec2f> linesOffset[2];
	vector<ofxPoint2f> linesFreezePoints;

	ofImage iceMask;
	ofImage columnTexture;
	
};
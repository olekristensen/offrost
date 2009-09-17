#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"

#include "PluginIncludes.h"
#include "PluginController.h"
//#include "ofxOsc.h"
//#include "guiController.h"

class CustomGLViewDelegate;


typedef struct
{
	float 	x;
	float 	y;
	bool 	bBeingDragged;
	bool 	bOver;
	float 	radius;
	
}	draggableVertex;




class testApp : public ofBaseApp
{
	
private:
	
	CustomGLViewDelegate* otherWindow;
	CustomGLViewDelegate* projectionSurfaceWindow;
	
public:
	
	testApp( ) ;	
	
	void setup();
	
	void update();
	void draw();
	
	void drawCameraView();
	void drawProjectionSurfaceView();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	PluginController * pluginController;

	void setReferenceToOtherWindow( CustomGLViewDelegate* delegate, int i );
	
	ofVideoGrabber * vidGrabber;
	
	
	bool setupCalled;
	
};

#endif

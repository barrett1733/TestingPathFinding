#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "GraphicsGrid.h"
#include "ObstructionMap.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class pathfindingApp : public AppBasic {
	//GraphicsTile* test;
	ObstructionMap* test;
	Rectf gridRect;
	ColorA gridColor;
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void pathfindingApp::setup()
{
	//test = new GraphicsTile(Rectf(100, 200, 400, 400), ColorA(0.5, 0.2, 0.2), 10, ColorA(0, 0, 0.5));
	test = new ObstructionMap(20, 20);
	//console() << getWindowSize() << std::endl;
	gridRect.set(200, 0, getWindowWidth(), getWindowHeight());
	gridColor.set(1, 1, 1, 1);
}

void pathfindingApp::mouseDown( MouseEvent event )
{
}

void pathfindingApp::update()
{
}

void pathfindingApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
	GraphicsGrid::draw(*test, gridRect, gridColor);
}

void pathfindingApp::shutdown()
{

}

CINDER_APP_BASIC( pathfindingApp, RendererGl )

#pragma once
#include "flagObject.h"

#define DEFAULT_SCALE 0
#define DEFAULT_HEIGHT 0
#define DEFAULT_ANGLE 0
#define DEFAULT_CENTER_X 0
#define DEFAULT_CENTER_Y 0

class flagLayer : public flagObject {
public:
	flagLayer();
	void setup(ofxDatGui* gui, int _index);
	void draw();
	void drawGuideLines();
	void resetGui();
	void resetVars();

	//Setters
	void setScale(float _scale);
	void setHeight(float _height);
	void setCenter(ofPoint _center);
	void setAngle(float _angle);

	//Getters
	float getScale();
	float getHeight();
	ofPoint getCenter();
	float getAngle();

private:
	void drawPrimitives();
	void setupGui(ofxDatGui* gui);

	//Gui events
	void on2dPadEvent(ofxDatGui2dPadEvent e);
	void onSliderEvent(ofxDatGuiSliderEvent e);

	ofxDatGuiSlider* scaleSlider;
	ofxDatGuiSlider* angleSlider;
	ofxDatGuiSlider* heightSlider;
	ofxDatGui2dPad* positionPad;

	float scale;
	float height;
	ofPoint center;
	float angle;
};
#pragma once
#include "flagBackground.h"
#include "flagLayer.h"
#include "ofxSvg.h"
#include "ofxDatGui.h"

class flag {
public:
	flag(int _numLayers, ofxDatGui* _gui);
	void setup();
	void update();
	void draw();
	void resetFlag();

	void setCountry(string _country);

	flagBackground* getBackground();
	vector<flagLayer*> getLayers();
	ofxSVG getMotif();
	string getCountry();

private:
	flagBackground* background;
	vector<flagLayer*> layers;
	ofxSVG motif;
	ofxDatGui* gui;
	ofFbo canvas;
	string country;
};
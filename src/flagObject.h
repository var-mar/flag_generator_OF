#pragma once
#include "ofMain.h"
#include "ofxDatGui.h"
#include "helper.h"
#include "settings.h"

#define DEFAULT_STROKE 0
#define DEFAULT_TYPE 0
const ofColor DEFAULT_COLOR = ofColor::grey;

class flagObject {
public:
	flagObject();
	void setup();

	//Gui events
	void onDropdownEvent(ofxDatGuiDropdownEvent e);
	void onColorPickerEvent(ofxDatGuiColorPickerEvent e);
	void onButtonEvent(ofxDatGuiButtonEvent e);
	void onSliderEvent(ofxDatGuiSliderEvent e);

	//Setters
	void setTypes(map<string, int> _stringTypes);
	void setType(int _type);
	void setStrokeWeight(int _strokeWeight);
	void setStrokeColor(ofColor _strokeColor);
	void setColor(int _index, ofColor _color);
	void setColors(vector<ofColor> _colors);
	void addGuiColor(ofColor _color);
	void removeAllGuiColors();

	//Getters
	int getType();
	int getStrokeWeight();
	ofColor getStrokeColor();
	vector<ofColor>  getColors();
	
protected:
	void setupGui(ofxDatGui* gui);
	void removeGuiColor();
	void addPalette();
	void setMaxColors(int _maxColors);
	void resetGui();
	void resetVars();

	map<string,int> types;
	int type;
	int strokeWeight;
	ofColor strokeColor;
	vector<ofColor> colors;
	int index = -1;
	int maxColors = 0;
	
	vector<ofxDatGuiColorPicker*> guiColors;
	ofxDatGui* gui;
	ofxDatGuiFolder*  optionsFolder;

	ofxDatGuiDropdown* typeDropdown;
	ofxDatGuiSlider* strokeWeightSlider;
	ofxDatGuiColorPicker* strokeColorColorPicker;
};



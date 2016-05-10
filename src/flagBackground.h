#pragma once
#include "flagObject.h"

#define DEFAULT_SYMMETRY 100

class flagBackground : public flagObject {
public:
	flagBackground();
	void setup(ofxDatGui* gui);
	void draw();
	void resetVars();
	void resetGui();
	
	//Setters
	void setSymmetry(vector<int> _symmetry);

	//Getters
	vector<int> getSymmetry();

	//Gui events
	void onTextInputEvent(ofxDatGuiTextInputEvent e);

private:
	void setupGui(ofxDatGui* gui);
	void drawStrips();
	void drawStroke();
	vector<int> symmetry;
	ofxDatGuiTextInput* symmetryGui;
};
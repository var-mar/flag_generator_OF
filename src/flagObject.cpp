#include "flagObject.h"

flagObject::flagObject() {}
 
void flagObject::setup() {
	resetVars();
}

void flagObject::setupGui(ofxDatGui* _gui) {
	gui = _gui;
	vector<string> guiTypes;
	guiTypes.assign(4, "");
	for (std::map<string, int>::iterator it = types.begin(); it != types.end(); ++it) {
		guiTypes[it->second] = it->first;
	}
	typeDropdown = gui->addDropdown("TYPE",guiTypes);
	typeDropdown->onDropdownEvent(this, &flagObject::onDropdownEvent);
	optionsFolder = gui->addFolder("OPTIONS", ofColor::white);
	strokeWeightSlider = optionsFolder->addSlider("STROKE WEIGHT", 0, 500, DEFAULT_STROKE);
	strokeWeightSlider->onSliderEvent(this, &flagObject::onSliderEvent);
	strokeColorColorPicker = optionsFolder->addColorPicker((index != -1 ? "LY-" + ofToString(index) + "-" : "BG-")+"STKCOL", DEFAULT_COLOR);
	strokeColorColorPicker->onColorPickerEvent(this, &flagObject::onColorPickerEvent);
	addPalette();
}

void flagObject::addPalette() {
	ofxDatGuiFolder*  paletteFolder = gui->addFolder("PALETTE"+(index!=-1?ofToString(index):""), ofColor::white);
	if (maxColors > 1) {
		ofxDatGuiButton* addColorButton = paletteFolder->addButton("ADD COLOR");
		addColorButton->onButtonEvent(this, &flagObject::onButtonEvent);
		ofxDatGuiButton* removeColorButton = paletteFolder->addButton("REMOVE COLOR");
		removeColorButton->onButtonEvent(this, &flagObject::onButtonEvent);
	}
	addGuiColor(DEFAULT_COLOR);
}

void flagObject::addGuiColor(ofColor _color) {
	if (colors.size() < maxColors) {
		colors.push_back(_color);
		if (colors.size() > guiColors.size()) {
			ofxDatGuiFolder*  paletteFolder = gui->getFolder("PALETTE" + (index != -1 ? ofToString(index) : ""));
			ofxDatGuiColorPicker* newColor = paletteFolder->addColorPicker((index != -1 ? "LY-"+ofToString(index)+"-" : "BG-")+ofToString(colors.size() - 1));
			newColor->onColorPickerEvent(this, &flagObject::onColorPickerEvent);
			newColor->setColor(_color);
			newColor->setVisible(true);
			guiColors.push_back(newColor);
		}
		else {
			guiColors[colors.size() - 1]->setColor(_color);
			guiColors[colors.size() - 1]->setVisible(true);
		}
	}
}

void flagObject::removeAllGuiColors() {
	if (colors.size() > 0) {
		while (colors.size() > 0) {
			removeGuiColor();
		}
	}
}

void flagObject::removeGuiColor() {
	guiColors[colors.size() - 1]->setVisible(false);
	guiColors[colors.size() - 1]->setColor(DEFAULT_COLOR);
	colors.pop_back();
}

void flagObject::resetVars() {
	setStrokeColor(DEFAULT_COLOR);
	setStrokeWeight(DEFAULT_STROKE);
	setType(DEFAULT_TYPE);
}

void flagObject::resetGui() {
	typeDropdown->setIndex(DEFAULT_TYPE);
	strokeWeightSlider->setValue(DEFAULT_STROKE);
	removeAllGuiColors();
	addGuiColor(DEFAULT_COLOR);
	strokeColorColorPicker->setColor(DEFAULT_COLOR);
}

//GUI EVENTS
void flagObject::onDropdownEvent(ofxDatGuiDropdownEvent e)
{
		type = e.child;
}

void flagObject::onColorPickerEvent(ofxDatGuiColorPickerEvent e)
{
	if(e.target->is((index != -1 ? "LY-" + ofToString(index) + "-" : "BG-") + "STKCOL")) {
		strokeColor = e.color;
	}
	else {
			int colorIndex = ofStringTimesInString(e.target->getLabel(), "LY") > 0 ? ofToInt(ofSplitString(e.target->getLabel(), "-")[2]) : ofToInt(ofSplitString(e.target->getLabel(), "-")[1]);
			if (colorIndex >= 0 && colorIndex < colors.size()) {
				colors[colorIndex] = e.color;
			}
	}
}

void flagObject::onButtonEvent(ofxDatGuiButtonEvent e)
{
	if (e.target->is("ADD COLOR")) {
		addGuiColor(DEFAULT_COLOR);
	}
	else if (e.target->is("REMOVE COLOR")) {
		if(colors.size()>1)
			removeGuiColor();
	}
}

void flagObject::onSliderEvent(ofxDatGuiSliderEvent e) {
	if (e.target->is("STROKE WEIGHT")) {
		strokeWeight = e.value;
	}
}

//SETTERS

void flagObject::setTypes(map<string, int> _types) {
	types = _types;
}
void flagObject::setType(int  _type) {
	type = _type;
}
void flagObject::setStrokeWeight(int _strokeWeight) {
	strokeWeight = _strokeWeight;
}
void flagObject::setStrokeColor(ofColor _strokeColor) {
	strokeColor = _strokeColor;
}
void flagObject::setColors(vector<ofColor> _colors) {
	colors = _colors;
}

void flagObject::setColor(int _index, ofColor _color) {
	colors[_index] = _color;
}

void flagObject::setMaxColors(int _maxColors) {
	maxColors = _maxColors;
}

//GETTERS
int flagObject::getType() {
	return type;
}
int flagObject::getStrokeWeight(){
	return strokeWeight;
}
ofColor flagObject::getStrokeColor(){
	return strokeColor;
}
vector<ofColor>  flagObject::getColors(){
	return colors;
}
#include "flagBackground.h"

flagBackground::flagBackground() {
	flagObject::flagObject();
	types["HORIZONTAL"] = 0;
	types["VERTICAL"] = 1;
	types["DIAGONAL_A"] = 2;
	types["DIAGONAL_B"] = 3;
}

void flagBackground::setup(ofxDatGui* gui) {
	flagObject::setup();
	resetVars();
	setupGui(gui);
}



void flagBackground::setupGui(ofxDatGui* gui) {
	flagObject::setupGui(gui);
	symmetryGui = optionsFolder->addTextInput("SYMMETRY", ofToString(DEFAULT_SYMMETRY));
	symmetryGui->onTextInputEvent(this, &flagBackground::onTextInputEvent);
}

void flagBackground::draw() {
	drawStrips();
	if (strokeWeight > 0)drawStroke();
}

void flagBackground::drawStrips() {
	ofFill();
	int numStrips = symmetry.size();
	for (int i = 0; i < numStrips; i++) {
		static float step = 0;
		switch (type) {
		case 0: //HORIZONTAL
			if (i == 0) step = 0;
			ofSetColor(colors[i%colors.size()]);
			ofDrawRectangle(0, step, FLAG_WIDTH, FLAG_HEIGHT*(float)symmetry[i%symmetry.size()] / 100);
			step += FLAG_HEIGHT*(float)symmetry[i%symmetry.size()] / 100;
			break;
		case 1: //VERTICAL
			if (i == 0) step = 0;
			ofSetColor(colors[i%colors.size()]);
			ofDrawRectangle(step, 0, FLAG_WIDTH*(float)symmetry[i%symmetry.size()] / 100, FLAG_HEIGHT);
			step += FLAG_WIDTH*(float)symmetry[i%symmetry.size()] / 100;
			break;
		case 2: //DIAGONAL_A
		{
			ofSetColor(colors[(colors.size() - 1 - i) % colors.size()]);
			if (i == 0) step = 1;
			ofPoint a = ofPoint(0, FLAG_HEIGHT);
			ofPoint b = ofPoint(0, (float)FLAG_HEIGHT - 2 * FLAG_HEIGHT*step);
			ofPoint c = ofPoint((float)FLAG_WIDTH * 2 * step, FLAG_HEIGHT);
			ofDrawTriangle(a, b, c);
			step -= (float)symmetry[(symmetry.size() - 1 - i) % symmetry.size()] / 100;
			break;
		}
		case 3: //DIAGONAL_B
		{
			ofSetColor(colors[(colors.size() - 1 - i) % colors.size()]);
			if (i == 0) step = 1;
			ofPoint a = ofPoint(FLAG_WIDTH, FLAG_HEIGHT);
			ofPoint b = ofPoint(FLAG_WIDTH, (float)FLAG_HEIGHT - 2 * FLAG_HEIGHT*step);
			ofPoint c = ofPoint(FLAG_WIDTH - (float)FLAG_WIDTH * 2 * step, FLAG_HEIGHT);
			ofDrawTriangle(a, b, c);
			step -= (float)symmetry[(symmetry.size() - 1 - i) % symmetry.size()] / 100;
			break;
		}
		}
	}
}

void flagBackground::drawStroke() {
	ofFill();
	ofSetColor(strokeColor);
	ofDrawRectangle(0,0,FLAG_WIDTH,strokeWeight); //Up border
	ofDrawRectangle(0, FLAG_HEIGHT-strokeWeight, FLAG_WIDTH, strokeWeight); //Down border
	ofDrawRectangle(0, 0, strokeWeight, FLAG_HEIGHT); //Left border
	ofDrawRectangle(FLAG_WIDTH - strokeWeight, 0, strokeWeight, FLAG_HEIGHT);
}

void flagBackground::resetVars() {
	flagObject::resetVars();
	setMaxColors(10);
	symmetry.clear();
	symmetry.push_back(DEFAULT_SYMMETRY);
}

void flagBackground::resetGui() {
	flagObject::resetGui();
	symmetryGui->setText(ofToString(DEFAULT_SYMMETRY));
}

void flagBackground::onTextInputEvent(ofxDatGuiTextInputEvent e)
{
	setSymmetry(helper::getInstance()->getSymmetryFromString(e.text));
}

void flagBackground::setSymmetry(vector<int> _symmetry) {
	symmetry = _symmetry;
}

vector<int> flagBackground::getSymmetry() {
	return symmetry;
}
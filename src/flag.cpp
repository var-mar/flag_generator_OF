#include "flag.h"

flag::flag(int _numLayers, ofxDatGui* _gui) {
	gui = _gui;
	canvas.allocate(FLAG_WIDTH, FLAG_HEIGHT, GL_RGB);
	background = new flagBackground();
	for (int i = 0; i < _numLayers;i++)
		layers.push_back(new flagLayer());
	setupGui();
}

void flag::setup() {
	background->setup(gui);
	for (int i = 0; i < layers.size(); i++)
		layers[i]->setup(gui,i);
}

void flag::setupGui() {
	ofxDatGuiButton* motifButton = gui->addToggle("SHOW MOTIF", true);
	motifButton->onButtonEvent(this, &flag::onButtonEvent);
}

void flag::update() {
}

void flag::draw() {
	canvas.begin();
		ofClear(255, 255, 255);
		background->draw();
		for (int i = 0; i < layers.size(); i++)
			layers[i]->draw();
		if(drawMotif)motif.draw();
	canvas.end();
	canvas.draw(0, 0);
	for (int i = 0; i < layers.size(); i++)
		layers[i]->drawGuideLines();
}

void flag::resetFlag() {
	background->resetVars();
	background->resetGui();
	for (int i = 0; i < layers.size(); i++) {
		layers[i]->resetVars();
		layers[i]->resetGui();
	}
}

void flag::onButtonEvent(ofxDatGuiButtonEvent e){
	drawMotif = e.enabled;
}

void flag::setCountry(string _country) {
	country = _country;
	motif.load(MOTIF_DIR + _country + ".svg");
}

flagBackground* flag::getBackground() {
	return background;
}

vector<flagLayer*> flag::getLayers() {
	return layers;
}

ofxSVG flag::getMotif() {
	return motif;
}

string flag::getCountry() {
	return country;
}
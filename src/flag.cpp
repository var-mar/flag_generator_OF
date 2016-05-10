#include "flag.h"

flag::flag(int _numLayers, ofxDatGui* _gui) {
	gui = _gui;
	canvas.allocate(FLAG_WIDTH, FLAG_HEIGHT, GL_RGB);
	background = new flagBackground();
	layers.push_back(new flagLayer());
	layers.push_back(new flagLayer());
	//layers.assign(_numLayers, new flagLayer());
}

void flag::setup() {
	background->setup(gui);
	for (int i = 0; i < layers.size(); i++)
		layers[i]->setup(gui,i);
}

void flag::update() {
}

void flag::draw() {
	canvas.begin();
		ofClear(255, 255, 255);
		background->draw();
		for (int i = 0; i < layers.size(); i++)
			layers[i]->draw();
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

void flag::setCountry(string _country) {
	country = _country;
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
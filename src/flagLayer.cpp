#include "flagLayer.h"

flagLayer::flagLayer() {
	types["SQUARE"] = 0;
	types["TRIANGLE"] = 1;
	types["CIRCLE"] = 2;
	types["CROSS"] = 3;
}

void flagLayer::setup(ofxDatGui* gui, int _index) {
	index = _index;
	flagObject::setup();
	resetVars();
	setupGui(gui);
}


void flagLayer::setupGui(ofxDatGui* gui) {
	flagObject::setupGui(gui);
	scaleSlider = optionsFolder->addSlider("SCALE", 0, FLAG_WIDTH, DEFAULT_SCALE);
	scaleSlider->onSliderEvent(this, &flagLayer::onSliderEvent);
	angleSlider = optionsFolder->addSlider("ANGLE", 0, 360, DEFAULT_ANGLE);
	angleSlider->onSliderEvent(this, &flagLayer::onSliderEvent);
	heightSlider = optionsFolder->addSlider("HEIGHT", 0, 1000, DEFAULT_HEIGHT);
	heightSlider->onSliderEvent(this, &flagLayer::onSliderEvent);
	positionPad = optionsFolder->add2dPad("POSITION");
	positionPad->setBounds(ofRectangle(-FLAG_WIDTH, -FLAG_HEIGHT, 3 * FLAG_WIDTH, 3 * FLAG_HEIGHT));
	positionPad->on2dPadEvent(this, &flagLayer::on2dPadEvent);
	positionPad->setPoint(ofPoint(DEFAULT_CENTER_X, DEFAULT_CENTER_Y));
}

void flagLayer::draw() {
	ofFill();
	ofPushMatrix();
		ofTranslate(center.x, center.y, 0);
		ofRotate(angle);
		ofPushMatrix();
			ofTranslate(-center.x, -center.y, 0);
			drawPrimitives();
		ofPopMatrix();
	ofPopMatrix();
}

void flagLayer::drawPrimitives() {
	switch (type) {
	case 0: //SQUARE
		ofSetColor(strokeWeight > 0 ? strokeColor : colors[0]);
		ofRect(center.x - scale*.5f, center.y - (scale + height)*.5f, scale, scale + height);
		if (strokeWeight > 0) {
			ofSetColor(colors[0]);
			ofRect(center.x - scale*.5f + strokeWeight, center.y - (scale + height)*.5f + strokeWeight, scale - strokeWeight * 2, scale + height - strokeWeight * 2);
		}
		break;
	case 1: //TRIANGLE
	{
		ofPoint v1 = ofPoint(0, 1).normalize();
		float angle = (float)TWO_PI / 3; //120
		ofPoint v2 = ofPoint(v1.x*cos(angle) - v1.y*sin(angle), v1.x*sin(angle) + v1.y*cos(angle));
		angle = (float)(TWO_PI / 3) * 2; //240
		ofPoint v3 = ofPoint(v1.x*cos(angle) - v1.y*sin(angle), v1.x*sin(angle) + v1.y*cos(angle));
		ofPoint p1, p2, p3;
		p1 = v1; p2 = v2; p3 = v3;
		p1 *= scale + height; p2 *= scale; p3 *= scale;
		p1 += center; p2 += center; p3 += center;
		ofSetColor(strokeWeight > 0 ? strokeColor : colors[0]);
		ofDrawTriangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
		if (strokeWeight > 0) {
			ofSetColor(colors[0]);
			p1 = v1; p2 = v2; p3 = v3;
			p1 *= scale + height - strokeWeight; p2 *= scale - strokeWeight; p3 *= scale - strokeWeight;
			p1 += center; p2 += center; p3 += center;
			ofDrawTriangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
		}
		break;
	}
	case 2: //CIRCLE
		ofSetColor(strokeWeight > 0 ? strokeColor : colors[0]);
		ofEllipse(center, scale, scale + height);
		if (strokeWeight > 0) {
			ofSetColor(colors[0]);
			ofEllipse(center, scale-strokeWeight, scale + height-strokeWeight);
		}
		break;
	case 3: //CROSS
		ofSetColor(strokeWeight > 0 ? strokeColor : colors[0]);
		ofRect(center.x - scale*.5f, center.y - (scale + height)*.5f, scale, scale + height);
		ofPushMatrix();
		ofTranslate(center.x, center.y, 0);
		ofRotate(90);
		ofPushMatrix();
		ofTranslate(-center.x, -center.y, 0);
		ofSetColor(strokeWeight > 0 ? strokeColor : colors[0]);
		ofRect(center.x - scale*.5f, center.y - (scale + height)*.5f, scale, scale + height);
		ofPopMatrix();
		ofPopMatrix();
		if (strokeWeight > 0) {
			ofSetColor(colors[0]);
			ofRect(center.x - scale*.5f + strokeWeight, center.y - (scale + height)*.5f + strokeWeight, scale - strokeWeight * 2, scale + height - strokeWeight * 2);
		}
		ofPushMatrix();
		ofTranslate(center.x, center.y, 0);
		ofRotate(90);
		ofPushMatrix();
		ofTranslate(-center.x, -center.y, 0);
		if (strokeWeight > 0) {
			ofSetColor(colors[0]);
			ofRect(center.x - scale*.5f + strokeWeight, center.y - (scale + height)*.5f + strokeWeight, scale - strokeWeight * 2, scale + height - strokeWeight * 2);
		}
		ofPopMatrix();
		ofPopMatrix();
		break;
	}
}

void flagLayer::drawGuideLines() {
	ofSetColor(ofColor::green);
	if (center.y == FLAG_HEIGHT*.5f) {
		ofLine(0, center.y, FLAG_WIDTH, center.y);
	}
	if (center.x > (float)FLAG_WIDTH*.5f - 5 && center.x < (float)FLAG_WIDTH*.5f + 5) {
		ofLine(center.x, 0, center.x, FLAG_HEIGHT);
	}
	ofSetColor(ofColor::white);
}

void flagLayer::resetVars() {
	flagObject::resetVars();
	setScale(DEFAULT_SCALE);
	setMaxColors(1);
	setHeight(DEFAULT_HEIGHT);
	setAngle(DEFAULT_ANGLE);
	setCenter(ofPoint(DEFAULT_CENTER_X, DEFAULT_CENTER_Y));
}

void flagLayer::resetGui() {
	flagObject::resetGui();
	scaleSlider->setValue(DEFAULT_SCALE);
	angleSlider->setValue(DEFAULT_ANGLE);
	heightSlider->setValue(DEFAULT_HEIGHT);
	positionPad->setPoint(ofPoint(DEFAULT_CENTER_X, DEFAULT_CENTER_Y));
}

void flagLayer::onSliderEvent(ofxDatGuiSliderEvent e)
{
	if(e.target->is("ANGLE"))
		angle = e.value;
	else if (e.target->is("SCALE")) {
		scale = e.value;
		ofxDatGuiSlider* strokeSlider = gui->getSlider("STROKE WEIGHT");
		strokeSlider->setMax(scale);
	}
	else if (e.target->is("HEIGHT"))
		height = e.value;
}

void flagLayer::on2dPadEvent(ofxDatGui2dPadEvent e)
{
	center = ofPoint(e.x, e.y);
}

void flagLayer::setScale(float _scale) {
	scale = _scale;
}

void flagLayer::setHeight(float _height) {
	height = _height;
}

void flagLayer::setCenter(ofPoint _center) {
	center = _center;
}

void flagLayer::setAngle(float _angle) {
	angle = _angle;
}

float flagLayer::getScale(){
	return scale;
}
float flagLayer::getHeight(){
	return height;
}
ofPoint flagLayer::getCenter(){
	return center;
}
float flagLayer::getAngle(){
	return angle;
}
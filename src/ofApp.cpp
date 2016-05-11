#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	mainGui = new ofxDatGui(ofxDatGuiAnchor::TOP_RIGHT);
	setupGui();
	myFlag = new flag(3, mainGui);
	myFlag->setup();
	svgCanvas.allocate(FLAG_WIDTH, FLAG_HEIGHT, GL_RGBA);
}

//--------------------------------------------------------------
void ofApp::update(){
	countriesGui->setPosition(ofGetWidth() - mainGui->getWidth() - countriesGui->getWidth(), 0);
	countriesGui->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	myFlag->draw();
	svgCanvas.draw(FLAG_WIDTH, 0);
	countriesGui->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (ofStringTimesInString(lastHittedElement, "LY") > 0) {
		int numLayer = ofToInt(ofSplitString(lastHittedElement, "-")[1]);
		ofPoint pos = myFlag->getLayers()[numLayer]->getCenter();
		if (key == OF_KEY_UP) pos.y--;
		else if (key == OF_KEY_DOWN) pos.y++;
		else if (key == OF_KEY_LEFT) pos.x--;
		else if (key == OF_KEY_RIGHT) pos.x++;
		myFlag->getLayers()[numLayer]->setCenter(pos);
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	vector<ofColor> bgColors = myFlag->getBackground()->getColors();
	ofPixels px;
	ofxDatGuiColorPicker* picker;
	ofxDatGui2dPad* pad;
	svgCanvas.readToPixels(px);
	for (int i = 0; i < bgColors.size(); i++) {
		picker = mainGui->getColorPicker("BG-" + ofToString(i));
		if (picker->hitTest(ofPoint(x, y))) {
			lastHittedElement = "BG-" + ofToString(i);
		}
	}
	picker = mainGui->getColorPicker("BG-STKCOL");
	if (picker->hitTest(ofPoint(x, y))) {
		lastHittedElement = "BG-STKCOL";
	}

	vector<flagLayer*> layers = myFlag->getLayers();
	for (int i = 0; i < layers.size(); i++) {
		picker = mainGui->getColorPicker("LY-" + ofToString(i) + "-0");
		if (picker->hitTest(ofPoint(x, y))) {
			lastHittedElement = "LY-" + ofToString(i) + "-0";
		}
		picker = mainGui->getColorPicker("LY-" + ofToString(i) + "-STKCOL");
		if (picker->hitTest(ofPoint(x, y))) {
			lastHittedElement = "LY-" + ofToString(i) + "-STKCOL";
		}
	}
	cout << lastHittedElement << endl;

	if ((x > FLAG_WIDTH && x < FLAG_WIDTH + svgCanvas.getWidth())
		&&
	   (y > 0 && y <  svgCanvas.getHeight())){
		ofColor pickedColor = px.getColor(x, y);
		if (ofStringTimesInString(lastHittedElement, "BG") > 0) {
			if (ofStringTimesInString(lastHittedElement, "STKCOL") > 0) {
				myFlag->getBackground()->setStrokeColor(pickedColor);
			}
			else {
				int index = ofToInt(ofSplitString(lastHittedElement, "-")[1]);
				myFlag->getBackground()->setColor(index, pickedColor);
			}
		}
		if (ofStringTimesInString(lastHittedElement, "LY") > 0) {
			int numLayer = ofToInt(ofSplitString(lastHittedElement, "-")[1]);
			if (ofStringTimesInString(lastHittedElement, "STKCOL") > 0) {
				myFlag->getLayers()[numLayer]->setStrokeColor(pickedColor);
			}
			else {
				int index = ofToInt(ofSplitString(lastHittedElement, "-")[2]);
				myFlag->getLayers()[numLayer]->setColor(index, pickedColor);
			}
		}
		picker = mainGui->getColorPicker(lastHittedElement);
		picker->setColor(pickedColor);
		lastHittedElement = "";
	}

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::setupGui() {
	mainGui->addButton("SAVE FLAG");
	mainGui->onButtonEvent(this, &ofApp::onButtonEvent);
	mainGui->addTextInput("country", "");
	setCountriesList();
}

void ofApp::saveFlag() {
	data.saveFlag(myFlag);
}

void ofApp::setCountriesList() {
	ofDirectory dir;
	dir.listDir(MOTIF_DIR);
	countriesGui = new ofxDatGuiScrollView("countries");
	countriesGui->setHeight(ofGetHeight());
	countriesGui->setWidth(70);
	countriesGui->onScrollViewEvent(this, &ofApp::onScrollViewEvent);
	if (dir.size()) {
		countries.assign(dir.size(), string());
	}
	for (int i = 0; i < (int)dir.size(); i++) {
		//Each file in folder means one country
		//Remove extension and save name of country in array
		string name = dir.getFile(i).getFileName().substr(0, dir.getFile(i).getFileName().find("." + dir.getFile(i).getExtension()));
		countries[i] = name;
		countriesGui->add(name);

	}
	for (int i = 0; i < (int)countries.size(); i++) {
		cout << countries[i] << endl;
	}

}

void ofApp::onScrollViewEvent(ofxDatGuiScrollViewEvent e)
{
	ofxDatGuiButton* button = e.target;
	string country = ofToLower(button->getLabel());
	mainGui->getTextInput("country")->setText(country);
	ofImage png;
	png.load(IMG_DIR + country + ".png");
	svgCanvas.begin();
	ofClear(255, 255, 255, 0);
	png.draw(0, 0, 480, 360);
	svgCanvas.end();
	myFlag->setCountry(country);
	data.loadCountry(country, myFlag);
}

void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
	if (e.target->is("SAVE FLAG")) {
		saveFlag();
	}
}
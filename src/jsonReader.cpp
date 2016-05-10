#include "jsonReader.h"

jsonReader::jsonReader(){
	if (!data.open(JSON_FILE)) {
		cout << "Error while openning file: " + JSON_FILE << endl;
	}
}

bool jsonReader::loadCountry(string _country, flag* _dataFlag) {
	if (data.isMember(_country)) {
		flagBackground* bg = _dataFlag->getBackground();
		if (loadBackground(_country, _dataFlag->getBackground())) {
			cout << _country + " country:  background's data successfully loaded" << endl;
		}
		else {
			cout << _country + " country:  couldn't load background's data" << endl;
			return false;
		}
		vector<flagLayer*> layers = _dataFlag->getLayers();
		for (int i = 0; i < layers.size(); i++) {
			if (loadLayer(_country, layers[i], i)) {
				cout << _country + " country:  layer "+ofToString(i)+"'s data successfully loaded" << endl;
			}
			else {
				cout << _country + " country:  couldn't load layer " + ofToString(i) + "'s data" << endl;
				return false;
			}
		}
	}
	else {
		_dataFlag->resetFlag();
		cout << "country " + _country + " not found" << endl;
		return false;
	}

	return true;
}

bool jsonReader::saveFlag(flag* _dataFlag) {
	bool error = false;
	string country = _dataFlag->getCountry();
	if (!saveBackground(country, _dataFlag->getBackground())) {
		cout << country + " country:  couldn't load background's data" << endl;
		error = true;
	}

	vector<flagLayer*> layers = _dataFlag->getLayers();
	for (int i = 0; i < layers.size(); i++) {
		if (!saveLayer(country, layers[i], i)) {
			cout << country + " country:  couldn't save layer " + ofToString(i) + "'s data" << endl;
			error = true;
		}
	}

	if (!error) {
		ofFile jsonFile(ofToDataPath(JSON_FILE), ofFile::WriteOnly);
		jsonFile << data;
		cout << country + " country:  flag's data saved successfully" << endl;
	}

	return error;
}

bool jsonReader::loadBackground(string _country, flagBackground* _flagBackground) {
	if (!loadFlagObject(_country, _flagBackground)) return false;
	vector<int> symmetry;
	if (data[_country]["background"].isMember("symmetry")) {
		std::size_t symSize = data[_country]["background"]["symmetry"].size();
		for (Json::ArrayIndex i = 0; i < symSize; ++i) {
			symmetry.push_back(data[_country]["background"]["symmetry"][i].asInt());
		}
		_flagBackground->setSymmetry(symmetry);
	}
	else return false;

	return true;
}

bool jsonReader::loadLayer(string _country, flagLayer* _flagLayer, int _index) {
	if (!loadFlagObject(_country, _flagLayer, _index)) return false;
	if (data[_country]["layer"][_index].isMember("scale")) {
		_flagLayer->setScale(data[_country]["layer"][_index]["scale"].asInt());
	}
	else return false;
	if (data[_country]["layer"][_index].isMember("height")) {
		_flagLayer->setHeight(data[_country]["layer"][_index]["height"].asInt());
	}
	else return false;
	if (data[_country]["layer"][_index].isMember("center")) {
		std::size_t centerSize = data[_country]["layer"][_index]["center"].size();
		if (centerSize==2) {
			ofPoint center;
			center.x = data[_country]["layer"][_index]["center"][0].asInt();
			center.y = data[_country]["layer"][_index]["center"][1].asInt();
			_flagLayer->setCenter(center);
		}
		else return false;
	}
	else return false;
	if (data[_country]["layer"][_index].isMember("angle")) {
		_flagLayer->setAngle(data[_country]["layer"][_index]["angle"].asInt());
	}
	else return false;

	return true;
}

bool jsonReader::loadFlagObject(string _country, flagObject* _flagObject, int _index) {
	if (_index != -1 ? data[_country]["layer"][_index].isMember("type") : data[_country]["background"].isMember("type")) {
		_flagObject->setType(_index != -1 ? data[_country]["layer"][_index]["type"].asInt() :  data[_country]["background"]["type"].asInt());
	}
	else return false;
	if (_index != -1 ? data[_country]["layer"][_index].isMember("colors") : data[_country]["background"].isMember("colors")) {
		_flagObject->removeAllGuiColors();
		std::size_t colorsSize = _index != -1 ?  data[_country]["layer"][_index]["colors"].size() : data[_country]["background"]["colors"].size();
		for (Json::ArrayIndex i = 0; i < colorsSize; ++i) {
			_flagObject->addGuiColor(ofColor::fromHex(_index != -1 ? data[_country]["layer"][_index]["colors"][i].asInt() : data[_country]["background"]["colors"][i].asInt()));
		}
	}
	else return false;
	if (_index != -1 ? data[_country]["layer"][_index].isMember("strokeWeight") : data[_country]["background"].isMember("strokeWeight")) {
		_flagObject->setStrokeWeight(_index != -1 ? data[_country]["layer"][_index]["strokeWeight"].asInt() : data[_country]["background"]["strokeWeight"].asInt());
	}
	else return false;
	if (_index != -1 ? data[_country]["layer"][_index].isMember("strokeColor") : data[_country]["background"].isMember("strokeColor")) {
		_flagObject->setStrokeColor(ofColor::fromHex(_index != -1 ? data[_country]["layer"][_index]["strokeColor"].asInt() : data[_country]["background"]["strokeColor"].asInt()));
	}
	else return false;

	return true;
}

bool jsonReader::saveBackground(string _country, flagBackground* _flagBackground) {
	if (saveFlagObject(_country, _flagBackground)) {
		vector<int>symmetry = _flagBackground->getSymmetry();
		for (int i = 0; i < symmetry.size(); i++) {
			data[_country]["background"]["symmetry"][i] = symmetry[i];
		}
	}
	else return false;

	return true;
}

bool jsonReader::saveLayer(string _country, flagLayer* _flagLayer, int _index) {
	if (saveFlagObject(_country, _flagLayer, _index)) {
		ofPoint center = _flagLayer->getCenter();
		data[_country]["layer"][_index]["center"][0] = center.x;
		data[_country]["layer"][_index]["center"][1] = center.y;
		data[_country]["layer"][_index]["scale"] = _flagLayer->getScale();
		data[_country]["layer"][_index]["height"] = _flagLayer->getHeight();
		data[_country]["layer"][_index]["angle"] = _flagLayer->getAngle();
	}
	else return false;

	return true;
}

bool jsonReader::saveFlagObject(string _country, flagObject* _flagObject, int _index) {
	vector<ofColor>colors = _flagObject->getColors();
	if (_index != -1) {
		for (int i = 0; i < colors.size(); i++) {
			data[_country]["layer"][_index]["colors"][i] = colors[i].getHex();
		}
		data[_country]["layer"][_index]["type"] = (int)_flagObject->getType();
		data[_country]["layer"][_index]["strokeWeight"] = _flagObject->getStrokeWeight();
		data[_country]["layer"][_index]["strokeColor"] = _flagObject->getStrokeColor().getHex();
	}
	else {
		for (int i = 0; i < colors.size(); i++) {
			data[_country]["background"]["colors"][i] = colors[i].getHex();
		}
		data[_country]["background"]["type"] = _flagObject->getType();
		data[_country]["background"]["strokeWeight"] = _flagObject->getStrokeWeight();
		data[_country]["background"]["strokeColor"] = _flagObject->getStrokeColor().getHex();
	}
	
	return true;
}
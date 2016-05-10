#pragma once
#include "flag.h"
#include "ofMain.h"
#include "ofxJSON.h"

class jsonReader {
public:
	jsonReader();
	bool loadCountry(string _country, flag* _dataFlag);
	bool saveFlag(flag* _dataFlag);
private:
	ofxJSONElement data;
	bool loadBackground(string _country, flagBackground* _flagBackground);
	bool loadLayer(string _country, flagLayer* _flagLayer, int _index);
	bool loadFlagObject(string _country, flagObject* _flagObject, int _index = -1);

	bool saveBackground(string _country, flagBackground* _flagBackground);
	bool saveLayer(string _country, flagLayer* _flagLayer, int _index);
	bool saveFlagObject(string _country, flagObject* _flagObject, int _index = -1);

};
#pragma once
#include "ofMain.h"

class helper {
public:
	static helper* getInstance();
	vector<int> getSymmetryFromString(string _string);
	ofColor getColorFromInt(int _intColor);
private:
	helper() {};
	static helper* s_instance;
	helper(helper const&) {};
	helper& operator=(helper const&) {};
};
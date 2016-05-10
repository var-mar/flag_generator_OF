#include <stddef.h>
#include "helper.h"

helper* helper::s_instance = NULL;

helper* helper::getInstance() {
	if (!s_instance)
		s_instance = new helper;
	return s_instance;
}

vector<int> helper::getSymmetryFromString(string _string) {
	vector<string> patternArray = ofSplitString(_string, ",");
	vector<int> response;
	for (int i = 0; i < patternArray.size(); i++) {
		if (patternArray[i] != "")
			response.push_back(ofToInt(patternArray[i]));
	}
		return response;
}

ofColor helper::getColorFromInt(int _intColor) {
	return ofColor::fromHex(_intColor);
}
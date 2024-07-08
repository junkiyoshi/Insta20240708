#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);

	for (int i = 0; i < 8; i++) {

		this->noise_seed_list.push_back(glm::vec2(ofRandom(1000), ofRandom(1000)));
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	for (int i = this->location_list.size() - 1; i >= 0; i--) {

		if (this->radius_list[i] > 0) {

			this->radius_list[i] += this->speed_list[i] * 3;
		}
		else {

			this->radius_list[i] += this->speed_list[i] * 60;
		}

		if (this->radius_list[i] > this->max_radius_list[i]) {

			this->location_list.erase(this->location_list.begin() + i);
			this->radius_list.erase(this->radius_list.begin() + i);
			this->speed_list.erase(this->speed_list.begin() + i);
			this->max_radius_list.erase(this->max_radius_list.begin() + i);
			this->color_list.erase(this->color_list.begin() + i);
		}
	}


	ofColor color;
	for (int i = 0; i < this->noise_seed_list.size(); i++) {

		auto noise_location = glm::vec2(
			ofMap(ofNoise(this->noise_seed_list[i].x, ofGetFrameNum() * 0.005), 0, 1, -400, 400),
			ofMap(ofNoise(this->noise_seed_list[i].y, ofGetFrameNum() * 0.005), 0, 1, -400, 400));
		auto location = noise_location + glm::vec2(ofRandom(-30, 30), ofRandom(-30, 30));

		this->location_list.push_back(location);
		this->radius_list.push_back(ofRandom(-600, -300));
		this->speed_list.push_back(ofRandom(0.3, 0.5));
		this->max_radius_list.push_back(ofRandom(15, 40));

		color.setHsb(ofMap(i, 0, this->noise_seed_list.size(), 0, 255), 255, 200);
		this->color_list.push_back(color);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	for (int i = 0; i < this->location_list.size(); i++) {

		if (this->radius_list[i] > 0) {

			auto alpha = this->radius_list[i] < this->max_radius_list[i] * 0.8 ? 255 : ofMap(this->radius_list[i], this->max_radius_list[i] * 0.8, this->max_radius_list[i], 255, 64);
			ofSetColor(this->color_list[i], alpha);

			ofNoFill();
			ofDrawCircle(this->location_list[i], this->radius_list[i]);

			ofSetColor(this->color_list[i]);

			ofFill();
			ofDrawCircle(this->location_list[i], 2);
		}
		else {

			auto alpha = ofMap(this->radius_list[i], -600, 0, 64, 255);
			ofSetColor(this->color_list[i], alpha);

			ofNoFill();
			ofDrawLine(glm::vec3(this->location_list[i], this->radius_list[i]), glm::vec3(this->location_list[i], this->radius_list[i] - 60));
		}
	}

	/*
	int start = 500;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
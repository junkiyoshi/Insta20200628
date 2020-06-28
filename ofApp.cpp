#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	int radius = 100;
	float handle_len = radius * 0.5522;
	int number_of_location = 4;
	int deg_span = 360 / number_of_location;

	for (int x = 200; x <= ofGetWidth(); x += 320) {

		for (int y = 200; y <= ofGetHeight(); y += 320) {

			vector<glm::vec2> location_list;
			vector<float> deg_list;
			for (int deg = 0; deg < 360; deg += deg_span) {

				location_list.push_back(glm::vec2(x + radius * cos(deg * DEG_TO_RAD), y + radius * sin(deg * DEG_TO_RAD)));
				deg_list.push_back(deg + 90);
			}

			for (int i = 0; i < location_list.size(); i++) {

				deg_list[i] += ofMap(ofNoise(glm::vec3(location_list[i], ofGetFrameNum() * 0.01)), 0, 1, -180, 180);
			}

			ofNoFill();
			ofSetLineWidth(2);

			ofBeginShape();
			for (int i = 0; i < location_list.size(); i++) {

				int n = (i + 1) % location_list.size();

				ofVertex(location_list[i]);
				ofBezierVertex(
					location_list[i] + glm::vec2(handle_len * cos(deg_list[i] * DEG_TO_RAD), handle_len * sin(deg_list[i] * DEG_TO_RAD)),
					location_list[n] + glm::vec2(handle_len * cos((deg_list[n] + 180) * DEG_TO_RAD), handle_len * sin((deg_list[n] + 180) * DEG_TO_RAD)),
					location_list[n]);
			}
			ofEndShape();

			ofFill();
			ofSetLineWidth(0.5);

			for (int i = 0; i < location_list.size(); i++) {

				ofDrawCircle(location_list[i], 5);

				ofDrawCircle(location_list[i] + glm::vec2(handle_len * cos(deg_list[i] * DEG_TO_RAD), handle_len * sin(deg_list[i] * DEG_TO_RAD)), 3);
				ofDrawCircle(location_list[i] + glm::vec2(handle_len * cos((deg_list[i] + 180) * DEG_TO_RAD), handle_len * sin((deg_list[i] + 180) * DEG_TO_RAD)), 3);

				ofDrawLine(location_list[i], location_list[i] + glm::vec2(handle_len * cos(deg_list[i] * DEG_TO_RAD), handle_len * sin(deg_list[i] * DEG_TO_RAD)));
				ofDrawLine(location_list[i], location_list[i] + glm::vec2(handle_len * cos((deg_list[i] + 180) * DEG_TO_RAD), handle_len * sin((deg_list[i] + 180) * DEG_TO_RAD)));
			}
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
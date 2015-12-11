#include "ofMain.h"
#include "ofApp.h"
//#include <vector>
//#include <fstream>
//#include <sstream>  // ※istringstreamを使うために必要

bool GetContents(const string& filename, vector<vector<string>>& table, const char delimiter =',');

//========================================================================
int main( ){

    
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}

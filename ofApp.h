#pragma once

#include "ofMain.h"


class ofApp : public ofBaseApp{
    
private:
    
    // ファイルを開く
    //std::ifstream fname("/Users/shono/Desktop/of_v0.9.0_osx_release/apps/myApps/aisMapping/bin/data/2015_11_06_10_58_24_dec1.csv");
    

    
public:
    ofImage img;
    int winW,winH;//window size
    
    vector<vector<string>> values;
    string str;
    vector<string> inner;
    
    vector<int> Time;
    vector<int> mmsi;
    vector<double> londitude;
    vector<double> latitude;
    

    
    void setup();
    void update();
		void draw();
    


		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};

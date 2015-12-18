#include "ofApp.h"
#include "ofxOpenCv.h"
#include <GLUT/glut.h>
#include <fstream>
#include <string>
#include <vector>

//緯度経度の4隅（北緯東経のみを使用）
double lat0 = 35+1/3;//緯度上
double lat1 = 35.0;//緯度下
double lon0 = 130.5;//経度左
double lon1 = 140.0;//経度右端
string fname = "/Users/shono/Desktop/of_v0.9.0_osx_release/apps/myApps/aisMapping/bin/data/2015_11_06_10_58_24_dec1.csv" ;


float winW, winH, imgW, imgH, ratioMin;

float posX, posY;

ofImage img;

//プロトタイプ関数宣言
bool GetContents(const string& filename, vector<vector<string>>& table);



//--------------------------------------------------------------
void ofApp::setup(){
    
    winW = 700;
    winH = 700;
    //  600x700, 30 frames/sec
    ofSetWindowShape(winW, winH);
    ofSetFrameRate(60);
    
    //  set background
    //ofBackground(0, 80, 0);
    //  load image
    img.loadImage("kaizu.bmp");
    
    imgW = img.getWidth();
    imgH = img.getHeight();
    
    
    string fname = "/Users/shono/Desktop/of_v0.9.0_osx_release/apps/myApps/aisMapping/bin/data/2015_11_06_10_58_24_dec1.csv";
    
    // 変数を定義する
    bool status = false;    // メソッドのステータス
    vector<vector<string>> table;   // 読み込んだCSVファイルの内容
    
    // CSVファイルの内容を取得する
    status = GetContents(fname, table);
    
    if (!status) {
        // 取得に失敗した場合はエラー終了する
        return -1;
    }
    
    // 確認のためにコンソールに内容を出力する
    for (int row = 0; row < table.size(); row++)
    {
        vector<string> record;  // １行分の内容
        record = table[row];    // １行分読み込む
        // １セルずつ読み込んでコンソールに出力する
        for (int column = 0; column < record.size(); column++)
        {
            cout << record[column];
            // 末尾の列でない場合はカンマを出力する
            if (column < record.size() - 1)
            {
                cout << ",";
            }
        }
        cout << endl;
    }

    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    img.draw(winW/2, winH/2, ratioMin*imgW, ratioMin*imgH);
    
    ofSetColor(255, 255, 255);
    img.draw(0,0,700,600);
    
    //  red circle (filled)
    ofSetColor(215, 19, 69);
    ofCircle(posX, posY, 2);
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
    posX = x;  posY = y;
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
    //window size
    float winW = ofGetWidth(),
    winH = ofGetHeight(),
    //image size
    imgW = img.getWidth(),
    imgH = img.getHeight();
    //  fit it
    float ratioW = winW / imgW,
    ratioH = winH / imgH,
    ratioMin;
    if (ratioW < ratioH)
        ratioMin = ratioW;
    else
        ratioMin = ratioH;
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

//緯度経度を座標に変換
void lonlat(double lonX, double latY)//(経度,緯度)
{
    //1度ごとのピクセル数の変化量
    double pixperlat = img.getHeight()/(lat1-lat0);
    double pixperlon = img.getWidth()/(lon1-lon0);
    
    double x = (lonX - lon0) * pixperlon;
    double y = (latY - lat0) * pixperlat;
    
    
    
}



bool GetContents(const string& filename, vector<vector<string>>& table)
{
    ifstream file(fname);
    vector<vector<string>> values;
    string str;
    int p;
    
    if(file.fail()){
        cerr << "failed." << endl;
        exit(0);
    }
    
    while(getline(file, str)){

        vector<string> inner;
        
        //コンマがあるかを探し、そこまでをvaluesに格納
        while( (p = str.find(",")) != str.npos ){
            inner.push_back(str.substr(0, p));
            
            //strの中身は", "の2文字を飛ばす
            str = str.substr(p+1);
        }
        inner.push_back(str);
        values.push_back(inner);
    }
    
    for(unsigned int i = 0; i < values.size(); ++i){
        for(unsigned int j = 0; j < values[i].size(); ++j){
            cout << values[i][j] << ",";
        }
        cout << endl;
    }
    cout << "values[1]";
}



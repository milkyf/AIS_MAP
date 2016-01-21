#include "ofApp.h"
#include "ofxOpenCv.h"
#include <GLUT/glut.h>
#include <fstream>
#include <string>
#include <vector>

//////////////////////////////////////////////
////////////緯度経度の4隅（北緯東経のみを使用）
double lat0 = 35+1/3;//緯度上
double lat1 = 35.0;//緯度下
double lon0 = 130.5;//経度左
double lon1 = 140.0;//経度右端
//////////////////////////////////////////////
//////////////////////////////////////////////
string fname = "/Users/shono/Desktop/of_v0.9.0_osx_release/apps/myApps/aisMapping/bin/data/2015_11_06_10_58_24_dec1.csv" ;


float winW, winH, imgW, imgH, ratioMin;

float posX, posY;

ofImage img;

//プロトタイプ関数宣言
bool GetContents(const string& filename, vector<vector<string>>& table);
void lonlat_to_coordinates(double lonX, double latY);//(経度,緯度)


vector<vector<string>> values;
string str;
vector<string> inner;

vector<int> Time;
vector<int> mmsi;
vector<double> londitude;
vector<double> latitude;



//--------------------------------------------------------------
void ofApp::setup(){
    
    winW = 1458;
    winH = 1190;
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
    
}

//--------------------------------------------------------------
void ofApp::update(){
    winW = ofGetWindowWidth();
    winH = ofGetWindowHeight();
    //cout << winW;
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //画像描画
    ofSetColor(255, 255, 255);
    img.draw(0,0,winW,winH);
    
    //赤点表示
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
void lonlat_to_coordinates(double lonX, double latY)//(経度,緯度)
{
    //1度ごとのピクセル数の変化量
    double pixperlat = img.getHeight()/(lat1-lat0);
    double pixperlon = img.getWidth()/(lon1-lon0);
    
    double x = (lonX - lon0) * pixperlon;
    double y = (latY - lat0) * pixperlat;
    
    
}


//csvファイルの要素をvectorに入れている
bool GetContents(const string& filename, vector<vector<string>>& table)
{
    ifstream file(fname);
    vector<vector<string> > values;
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
    
/**********************************************************************************/
/*                  csvの緯度経度(8,9列目)の部分をvector型配列に格納              */
/**********************************************************************************/
    vector<double> londitude(values.size()-1);
    vector<double> latitude(values.size()-1);
    
    for(unsigned int i = 0; i < values.size(); ++i)
    {
        for(unsigned int j = 0; j < values[i].size(); ++j)
        {
            //cout << values[i][j] << ",";
            
            
            for(int k= 0; k < values.size()-1; k++)
            {
                
                
                //londitude
                if(i !=0 && j == 8)
                {
                    
                    londitude[k] = stod(values[i][j]);
                    

                }
                
                //latitude
                if(i !=0 && j == 9)
                {
                    
                    latitude[k] = stod(values[i][j]);
                    
                }

                
    
            }
            
            
        }
        
        
        
        
        
//////////確認のために緯度経度をコンソール画面に表示する部分///////
//        for(int i = 0;i < values.size()-1; i++)
//        {
//            cout << londitude[i] << "," << endl;
//        }
//////////////////////////////////////////////////////////
    }
    
    return true;
}

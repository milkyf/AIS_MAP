
//  Created by shono on 2015/11/12.
//  Copyright © 2015年 shono. All rights reserved.
//
#include <GLUT/GLUT.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>


using namespace std;
using namespace cv;

//window size
#define WIDTH 700
#define HEIGHT 600

//緯度経度の4隅
double lat0 = 35.5;
double lat1 = 35.0;
double lon0 = 135.0;
double lon1 = 135.5;




// 画像読み込み
//bmpファイルでないと崩れる
std::string imgFilename = "kagosima.bmp";
cv::Mat img = cv::imread(imgFilename);

/*
struct aivdm_type1 {
    int time;
    int messageType;
    int repeatIndicator;
    int mmsi;
    std::string navigationStatus;
    std::string rot;
    double sog;
    std::string positionAccuracy;
    double longitude;
    double latitude;
    double cog;
    int hdg;
    int timeStamp;
    std::string maneuverIndicator;
    std::string spare;
    std::string raimFlag;
    int radioStatus;
};

// AIVDM(Type1)のデータを読み込む, string型にsetする
aivdm_type1 readAivdmType1(std::string str) {
    aivdm_type1 nmea;
    
    int i = 0;
    std::string tmp[17];
    std::istringstream stream(str);
    while(getline(stream,tmp[i],','))
        ++i;
    
    nmea.time = std::atoi(tmp[0].c_str());
    nmea.messageType = std::atoi(tmp[1].c_str());
    nmea.repeatIndicator = std::atoi(tmp[2].c_str());
    nmea.mmsi = std::atoi(tmp[3].c_str());
    nmea.navigationStatus = tmp[4];
    nmea.rot = tmp[5];
    nmea.sog = std::atof(tmp[6].c_str());
    nmea.positionAccuracy = tmp[7];
    nmea.longitude = std::atof(tmp[8].c_str());
    nmea.latitude = std::atof(tmp[9].c_str());
    nmea.cog = std::atof(tmp[10].c_str());
    nmea.hdg = std::atoi(tmp[11].c_str());
    nmea.timeStamp = std::atoi(tmp[12].c_str());
    nmea.maneuverIndicator = tmp[13];
    nmea.spare = tmp[14];
    nmea.raimFlag = tmp[15];
    nmea.radioStatus = std::atoi(tmp[16].c_str());
    
    return nmea;
}

*/


static void display(void)
{
    cv::Mat img = cv::imread(imgFilename);
    //cv::resize(img,img,Size(),WIDTH/img.cols,HEIGHT/img.rows);
    cv::flip(img, img, 0);
    cv::cvtColor(img, img, CV_BGR2RGB);
    
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawPixels(img.cols,img.rows,
                 GL_RGB, GL_UNSIGNED_BYTE, img.data);
    glFlush();
    
}

/*!
 * 文字列描画
 * @param[in] str 文字列
 * @param[in] w,h ウィンドウサイズ
 * @param[in] x0,y0 文字列の位置(左上原点のスクリーン座標系,文字列の左下がこの位置になる)
 */
static void DrawString(string str, int w, int h, int x0, int y0)
{
    glDisable(GL_LIGHTING);
    // 平行投影にする
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, w, h, 0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    // 画面上にテキスト描画
    glRasterPos2f(x0, y0);
    int size = (int)str.size();
    for(int i = 0; i < size; ++i){
        char ic = str[i];
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ic);
    }
    
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void resize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, h, 0);
    glMatrixMode(GL_MODELVIEW);
    
    // 画像縮小拡大率
    double widthMagnification;
    double heightMagnification;
    // Calc Magnification

    widthMagnification = (double)w / (double)img.cols;
    heightMagnification = (double)h / (double)img.rows;
    glPixelZoom(widthMagnification, heightMagnification);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 'q':
        case 'Q':
        case '\033':
            exit(0);
            break;
            
        default:
            break;
    }
}

void mouse(int button, int state, int x, int y)
{
    
    //1ピクセルごとの角度の変化量
    double latperpix = (lat1-lat0)/img.rows;
    double lonperpix = (lon1-lon0)/img.cols;
    
    double lat = lat0 + y * latperpix;
    double lon = lon0 + x * lonperpix;
    
    switch (button) {
        case GLUT_LEFT_BUTTON:
            
            printf("(%d, %d)\n", x, y);
            printf("緯度 %f  ", lat);
            printf("経度 %f\n", lon);
            break;
        case GLUT_MIDDLE_BUTTON:
            printf("(%d, %d)\n", x, y);
            break;
        case GLUT_RIGHT_BUTTON:
            printf("(%d, %d)\n", x, y);
            break;
        default:
            break;
    }
}

//緯度経度を座標に
void lonlat(double lonX, double latY)
{
    //1度ごとのピクセル数の変化量
    double pixperlat = img.rows/(lat1-lat0);
    double pixperlon = img.cols/(lon1-lon0);
    
    double x = (lonX - lon0) * pixperlon;
    double y = (latY - lat0) * pixperlat;
    
    std::cout << "londitudeを入力してください" << endl;
    std:: cin >> lonX;
    std::cout << "latitudeを入力してください" << endl;
    std:: cin >> latY;
    
    printf("(X , Y) = (%f , %f)",x,y);
    
}

void motion(int x , int y) {
    //printf("X = %d : Y = %d\n" , x , y);
}


int main(int argc, char *argv[])
{
    printf("WIDTH = %d HEIGHT = %d" ,img.cols,img.rows);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    //glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowSize(img.cols, img.rows);
    glutCreateWindow("画像");
    glutInitWindowPosition(500, 100);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 0,0, 0.0);
    glViewport(0, 0, 0,0);
    
    //文字列描画
    glColor3d(0.0, 0.0, 1.0);
    DrawString("HelloWorld", img.cols, img.rows, 10, 100);
    
    
    glutDisplayFunc(display);
    //glutIdleFqunc(idle);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    
    glutMainLoop();
    return 0;
}


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


// 画像縮小拡大率
double widthMagnification;
double heightMagnification;

// 画像読み込み
std::string imgFilename = "snrn.bmp";
cv::Mat img = cv::imread(imgFilename);//読み込む画像***反転してしまう


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

void resize(int w, int h) {
    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, h, 0);
    glMatrixMode(GL_MODELVIEW);
    
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
    printf("x = %d y = %d" ,img.cols,img.rows);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    //glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowSize(img.cols, img.rows);
    glutCreateWindow("画像");
    glutInitWindowPosition(100, 100);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 0,0, 0.0);
    glViewport(0, 0, 0,0);

    glutDisplayFunc(display);
    //glutIdleFqunc(idle);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    
    glutMainLoop();
    return 0;
}

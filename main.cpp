//
//  main.cpp
//  AISMAP
//
//  Created by shono on 2015/11/06.
//  Copyright © 2015年 shono. All rights reserved.
//


//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/core/core.hpp>

#include <GLUT/glut.h>
#include <iostream>



void display()
{
    
//    cv::Mat img = cv::imread("earth.jpg");
//    cv::flip(img, img, 0);
//    cv::cvtColor(img, img, CV_BGR2RGB);
    
    
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawPixels(img.cols, img.rows,
                 GL_RGB, GL_UNSIGNED_BYTE, img.data);
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

struct mPoint
{
    int x;
    int y;
};

void mouse(int button, int state, int x, int y)
{
    switch (button) {
        case GLUT_LEFT_BUTTON:
            
            printf("(%d, %d)\n", x, y);
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

void motionCallback(int x, int y){
    printf("motion : %d %d\n", x, y);
}

int main(int argc, char** argv)
{
glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("AIS_MAP");
    
    
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluOrtho2D(0.0, 640, 640, 0.0);
//    glViewport(0, 0, 640, 640);
    
    
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motionCallback);
    
    glutMainLoop();
    return 0;
}

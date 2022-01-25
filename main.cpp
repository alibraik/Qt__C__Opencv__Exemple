
#include <QApplication>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv/cv.h"
#include<wind.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setStyle("fusion");
 WIND*w=new WIND();

 w->show();

/////;C:\Qt\Qt5.9.2\5.9.2\mingw53_32\bin;D:\cmake-3.21.4-windows-x86_64\bin;C:\Qt\Qt5.9.2\Tools\QtCreator\bin
 //C:\opencv\release\install\x86\mingw\bin
 return a.exec();
}

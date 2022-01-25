#ifndef WIND_H
#define WIND_H

#include <QWidget>
#include<QFileDialog>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<qdebug.h>
namespace Ui {
class WIND;
}

class WIND : public QWidget
{
    Q_OBJECT

public:
    explicit WIND(QWidget *parent = 0);
    ~WIND();
    cv::Mat img,img2;
private:
    Ui::WIND *ui;

private slots:
   void SlotLoad();
   void SlotGray();
   void SlotSave();
   void SlotRGB();
   void SlotErosion();
   void SlotDilate();
   void SlotClose();
   void SlotOpening();

   void on_horizontalSlider_sliderMoved(int position);
   void on_slid2_sliderMoved(int position);

};

#endif // WIND_H

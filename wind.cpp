#include "wind.h"
#include "ui_wind.h"



WIND::WIND(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WIND)
{
    ui->setupUi(this);

    this->setWindowTitle("Picture");
    this->setStyleSheet("background-color:white;");

    ui->BTNload->setIcon(QIcon("icons/load.png"));
    ui->BTNsave->setIcon(QIcon("icons/save.png"));
     ui->BTNrgb->setIcon(QIcon("icons/cancel.png"));

    ui->slid2->setValue(30);
    ui->sp2->setValue((30*255)/99);

    connect(ui->BTNload,SIGNAL(clicked(bool)),this,SLOT(SlotLoad()));
    connect(ui->BTNgray,SIGNAL(clicked(bool)),this,SLOT(SlotGray()));
    connect(ui->BTNsave,SIGNAL(clicked(bool)),this,SLOT(SlotSave()));
     connect(ui->BTNrgb,SIGNAL(clicked(bool)),this,SLOT(SlotRGB()));
    connect(ui->BTNclose,SIGNAL(clicked(bool)),this,SLOT(SlotClose()));
     connect(ui->BTNopening,SIGNAL(clicked(bool)),this,SLOT(SlotOpening()));
       connect(ui->BTNerosion,SIGNAL(clicked(bool)),this,SLOT(SlotErosion()));
         connect(ui->BTNdilation,SIGNAL(clicked(bool)),this,SLOT(SlotDilate()));

     ui->sp1->setMaximum(255);
     ui->sp2->setMaximum(255);
     ui->sp1->setReadOnly(true);
     ui->sp2->setReadOnly(true);
}

WIND::~WIND()
{
    delete ui;
}

void WIND::SlotLoad()
{

    QString filename=QFileDialog::getOpenFileName(
                this,
                tr("open file"),
                QDir::currentPath(),
                "All files (*.*);;Text File (*.txt);;Music file(*.png)"
                );


      ui->show->setToolTip(filename);

      img=cv::imread(filename.toStdString());
    img2=img.clone();

         ui->show->setPixmap(QPixmap (filename));
          ui->show->setScaledContents( true );

          ui->show->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
          cv::waitKey();

          ui->BTNgray->setEnabled(true);
          ui->BTNgray->setText("Set Gray");

}

void WIND::SlotGray()
{

if(!img.empty() && img.type()!=CV_8UC1 )
{
  cv::cvtColor(img,img,cv::COLOR_RGB2GRAY);

  cv::imwrite("tmp.png",img);

  cv::waitKey();
/*
  ui->show->setPixmap(
               QPixmap::fromImage(
                  QImage(img.data, img.cols, img.rows, img.step, QImage::Format_Grayscale8)
               )
           );
*/

  ui->show->setPixmap(QPixmap ("tmp.png"));

  ui->show->setScaledContents( true );

  ui->show->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );



  cv::waitKey();
  ui->BTNgray->setEnabled(false);
  ui->BTNgray->setText("GRAY");
}
}

void WIND::SlotSave()
{

    if(!img.empty())
    {
    cv::imwrite(ui->show->toolTip().toStdString(),img);
    cv::waitKey();
    }
}

void WIND::SlotRGB()
{


    img=cv::imread(ui->show->toolTip().toStdString());


    ui->show->setPixmap(QPixmap(ui->show->toolTip()));

        ui->show->setScaledContents( true );

        ui->show->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        cv::waitKey();

        ui->BTNgray->setEnabled(true);
        ui->BTNgray->setText("Set gray");

}

void WIND::SlotErosion()
{
    if(!img.empty())
    {
    if(img.type()!=CV_8UC1) cv::cvtColor(img, img, CV_BGR2GRAY);

    cv::Mat const shape = cv::getStructuringElement(
                      cv::MORPH_RECT, cv::Size(5, 5));
        cv::erode(img,img, shape);


    cv::imwrite("tmp.png",img);

    cv::waitKey();

    ui->show->setPixmap(QPixmap ("tmp.png"));

   }

}

void WIND::SlotDilate()
{
    if(!img.empty())
    {
 if(img.type()!=CV_8UC1) cv::cvtColor(img, img, CV_BGR2GRAY);

    cv::threshold(img, img, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);

    cv::Mat const shape = cv::getStructuringElement
                      (cv::MORPH_RECT, cv::Size(5, 5));
        cv::dilate(img,img, shape);


    cv::imwrite("tmp.png",img);

    cv::waitKey();

    ui->show->setPixmap(QPixmap ("tmp.png"));
    }
}

void WIND::SlotClose()
{
    if(!img.empty())
    {
    cv::Mat const structure_elem = cv::getStructuringElement(
                         cv::MORPH_RECT, cv::Size(5, 5));

    cv::morphologyEx(img, img,
                cv::MORPH_CLOSE, structure_elem);


    cv::imwrite("tmp.png",img);

    cv::waitKey();

    ui->show->setPixmap(QPixmap ("tmp.png"));

    }
}

void WIND::SlotOpening()
{
    if(!img.empty())
    {
    cv::Mat const structure_elem = cv::getStructuringElement(
                     cv::MORPH_RECT, cv::Size(5, 5));

    cv::morphologyEx(img,img,
                 cv::MORPH_OPEN, structure_elem);


    cv::imwrite("tmp.png",img);

    cv::waitKey();

    ui->show->setPixmap(QPixmap ("tmp.png"));
  }
}



void WIND::on_horizontalSlider_sliderMoved(int position)
{
   if(!img.empty())
   {



    cv::threshold(img2,img,(position*255)/99,ui->sp2->value(),cv::THRESH_BINARY);

    cv::imwrite("tmp.png",img);

    cv::waitKey();

      ui->show->setPixmap(QPixmap ("tmp.png"));



    ui->show->setScaledContents( true );

    ui->show->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );



    cv::waitKey();



  }
   ui->sp1->setValue((position*255)/99);
}

void WIND::on_slid2_sliderMoved(int position)
{
  if(!img.empty())
  {
    cv::threshold(img2,img,ui->sp1->value(),(position*255)/99,cv::THRESH_BINARY);


    cv::imwrite("tmp.png",img);

    cv::waitKey();

      ui->show->setPixmap(QPixmap ("tmp.png"));

    ui->show->setScaledContents( true );

    ui->show->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );





    cv::waitKey();
  }
  ui->sp2->setValue((position*255)/99);
}



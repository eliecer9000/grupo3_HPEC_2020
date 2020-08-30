#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "diff_and_error.h"
#include "histogram.h"
#include <iostream>
#include <fstream>
#include <string>

// Main class initialization
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    /*******************************
     * Initialize GUI Parameters
     ******************************/

    ui->setupUi(this);

    m_CurItemLeft = NULL;
    m_CurItemRight = NULL;

    connect(ui->B_LeftImgPickBtn, SIGNAL(clicked(bool)),this, SLOT(ButtonClickLeft()));
    connect(ui->B_RightImgPickBtn, SIGNAL(clicked(bool)),this, SLOT(ButtonClickRight()));

    //Keep all images scaled to fit its label
    ui->I_RightRaw->setScaledContents(true);
    ui->I_LeftRaw->setScaledContents(true);
    ui->I_GT->setScaledContents(true);
    ui->I_CT_HD_Diff->setScaledContents(true);
    ui->I_CT_HD_SGBM->setScaledContents(true);
    ui->I_CT_HD_Hist->setScaledContents(true);

    ui->B_Run->setAutoFillBackground(true);

    //Get initial parameters
    MinDisp = ui->P_MinDisp->text().toInt();
    MaxDisp = ui->P_MaxDisp->text().toInt();
    m_u8BlockSize_half =(uint8_t) (ui->P_m_u8BlockSize->text().toInt());
    P1 = ui->P_P1->text().toInt();
    P2 = ui->P_P2->text().toInt();
    UniqRatio = ui->P_UniqRatio->text().toInt();
    SGBMDir = ui->P_SGBMDir->text().toInt();
    sources = ui->P_Source->text().toStdString();

    m_pStereoImg = new StereoFPGA();

    //Update list of Images to use as input
    MainWindow::on_P_Update_In_clicked();
}

MainWindow::~MainWindow()
{
    delete m_pStereoImg;
    m_pStereoImg = nullptr;

    delete ui;
}

//Left image Selection
void MainWindow::ButtonClickLeft(void)
{
    /**************************************
     * Select left image from the GUI list
     **************************************/

    // Set text back to its original value
    if(NULL != m_CurItemLeft)
    {
        m_CurItemLeft->setText(m_CurItemLeft->text().section('-',0,0));
    }
    //Select left image from the list
    m_CurItemLeft = ui->CamerList->currentItem();
    if(nullptr != m_CurItemLeft)
    {
        QString NewText;
        NewText = m_CurItemLeft->text().section('-',0,0);
        m_CurItemLeft->setText(NewText+"-->Left Image");
    //Actually read the image
    in_imgL= imread(sources + NewText.toStdString(), IMREAD_GRAYSCALE);
    //Output of Greyscale
    if(OutputTestdata != 0 && in_imgL.data != NULL)  {
        NewText.replace(QRegExp("([\\w]+)(?=\\.ppm)"), "\\1_grey");
        NewText.replace(".ppm", ".txt");
        string filename = sources + NewText.toStdString();
        ofstream ostrm(filename);
        char str[10];

        ostrm << in_imgL.cols << ' ';
        ostrm << in_imgL.rows << '\n';

        for (int i = 0; i < in_imgL.rows; ++i) {
            for (int j = 0; j < in_imgL.cols; ++j) {
                sprintf(str, "%03X\n", in_imgL.at<uint8_t>(i, j));
                ostrm << str;
            }
        }
        ostrm.close();
    }
    //Show it in the GUI
    QImage imdisplay((uchar*)in_imgL.data, in_imgL.cols, in_imgL.rows, in_imgL.step, QImage::Format_Grayscale8); //Converts the CV image into Qt standard format
    ui->I_LeftRaw->setPixmap(QPixmap::fromImage(imdisplay));//display the image in label that is created earlier
    }
}

//Right image Selection
void MainWindow::ButtonClickRight(void)
{
    /**************************************
     * Select right image from the GUI list
     **************************************/

    // Set text back to its original value
    if(NULL != m_CurItemLeft)
    {
        m_CurItemLeft->setText(m_CurItemLeft->text().section('-',0,0));
    }

    m_CurItemLeft = ui->CamerList->currentItem();
    if(nullptr != m_CurItemLeft)
    {
        QString NewText;
        NewText = m_CurItemLeft->text().section('-',0,0);
        m_CurItemLeft->setText(NewText+"-->Right Image");
    //Actually read the image
    in_imgR= imread(sources + NewText.toStdString(), IMREAD_GRAYSCALE);
    //Output of Greyscale
    if(OutputTestdata != 0 && in_imgR.data != NULL) {
        NewText.replace(QRegExp("([\\w]+)(?=\\.ppm)"), "\\1_grey");
        NewText.replace(".ppm", ".txt");
        string filename = sources + NewText.toStdString();
        ofstream ostrm(filename);

        ostrm << in_imgR.cols << ' ';
        ostrm << in_imgR.rows << '\n';

        for (int i = 0; i < in_imgR.rows; ++i) {
            for (int j = 0; j < in_imgR.cols; ++j) {
                char str[10];
                sprintf(str, "%03X\n", in_imgR.at<uint8_t>(i, j));
                ostrm << str;
            }
        }
        ostrm.close();
    }
    //Show it in the GUI
    QImage imdisplay((uchar*)in_imgR.data, in_imgR.cols, in_imgR.rows, in_imgR.step, QImage::Format_Grayscale8); //Converts the CV image into Qt standard format
    ui->I_RightRaw->setPixmap(QPixmap::fromImage(imdisplay));//display the image in label that is created earlier
    }
}

void MainWindow::on_B_GTPickBtn_clicked()
{
    /**********************************************
     * Select ground truth image from the GUI list
     **********************************************/

    // Set text back to its original value
        if(NULL != m_CurItemLeft)
        {
            m_CurItemLeft->setText(m_CurItemLeft->text().section('-',0,0));
        }

        m_CurItemLeft = ui->CamerList->currentItem();
        if(nullptr != m_CurItemLeft)
        {
            QString NewText;
            NewText = m_CurItemLeft->text().section('-',0,0);
            m_CurItemLeft->setText(NewText+"-->Ground Truth");
    //Actually read the image
        GT_Image= imread(sources + NewText.toStdString(), IMREAD_GRAYSCALE);
    //Show it in the GUI
        QImage imdisplay((uchar*)GT_Image.data, GT_Image.cols, GT_Image.rows, GT_Image.step, QImage::Format_Grayscale8); //Converts the CV image into Qt standard format
        ui->I_GT->setPixmap(QPixmap::fromImage(imdisplay));//display the image in label that is created earlier
        }
}

void MainWindow::on_P_Update_In_clicked()
{
    /*****************************************************************
     * Update list of images in case new are added or path is changed
     *****************************************************************/
    sources = ui->P_Source->text().toStdString();
    QDir myDir(sources.c_str());
    QStringList filesList = myDir.entryList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst);
    ui->CamerList->clear();

    for ( const auto& i : filesList  )
    {
        ui->CamerList->addItem(i);
    }
}

int MainWindow::on_B_Run_clicked()
{
    /***************************************************************************
     * Computes SGBM and calculates its difference to the provided ground truth
     ***************************************************************************/

    //Set the RUN button to red color while computing
    ui->B_Run->setStyleSheet("border: 1px; background-color: rgb(204,0,0)"); ui->B_Run->repaint();

    //Get updated parameters from the GUI
    m_pStereoImg->SetMinDisp(static_cast<int16_t>(ui->P_MinDisp->text().toInt()));
    m_pStereoImg->SetMaxDisp(static_cast<int16_t>(ui->P_MaxDisp->text().toInt()));
    m_pStereoImg->SetBlockSize(static_cast<uint8_t>(ui->P_m_u8BlockSize->text().toInt()));
    m_pStereoImg->SetP1(static_cast<uint16_t>(ui->P_P1->text().toInt()));
    m_pStereoImg->SetP2(static_cast<uint16_t>(ui->P_P2->text().toInt()));
    m_pStereoImg->SetUniqueRatio(static_cast<uint8_t>(ui->P_UniqRatio->text().toInt()));
    m_pStereoImg->SetNumOfDirections(static_cast<uint8_t>(ui->P_SGBMDir->text().toInt()));

    // Check if computation can start -> both images are correctly loaded and parameters are valid
    if (in_imgL.data == NULL)
    {
        fprintf(stderr,"Cannot read left IMG\n");
        ui->B_Run->setStyleSheet("border: 1px; background-color: rgb(78, 154, 6)"); ui->B_Run->repaint();
        return 0;
    }

    if ((in_imgR.data == NULL) & (in_imgR.size == in_imgL.size))
    {
        fprintf(stderr,"Cannot read right IMG or incompatible size\n");
        ui->B_Run->setStyleSheet("border: 1px; background-color: rgb(78, 154, 6)"); ui->B_Run->repaint();
        return 0;
    }

    //m_u8BlockSize_half must have odd size
    if(ui->P_m_u8BlockSize->text().toInt()%2 == 0){
        fprintf(stderr,"\n**********SAD Window size must be an odd number**********\n");
        ui->B_Run->setStyleSheet("border: 1px; background-color: rgb(78, 154, 6)"); ui->B_Run->repaint();
        return 0;
    }


    cv::Mat DepthImg;

    /**********************************************
     * Compute SGBM and copy the result in DepthImg
     **********************************************/
    double * Cost_Compu_Time_array = m_pStereoImg->ComputeAlgo(in_imgL, in_imgR, &DepthImg);

    ui->L_CostCompTime_seconds->setText(QString::fromStdString(to_string(Cost_Compu_Time_array[0])));
    ui->L_find_minLri_time_seconds->setText(QString::fromStdString(to_string(Cost_Compu_Time_array[1])));
    ui->L_compute_hamming_time_seconds->setText(QString::fromStdString(to_string(Cost_Compu_Time_array[2])));

    delete [] Cost_Compu_Time_array;

    /**************************************************************************
     * Show region of interest (see Figure 4 of LH) of the Depth Map in the GUI
     **************************************************************************/
    cv::Mat ROI_CT_SGBM = DepthImg(cv::Range::all(), cv::Range(m_pStereoImg->m_u16xMin, m_pStereoImg->m_u16xMax));
    QImage CT_SGBM((uchar*)ROI_CT_SGBM.data, ROI_CT_SGBM.cols, ROI_CT_SGBM.rows, ROI_CT_SGBM.step, QImage::Format_Grayscale8); //Converts the CV image into Qt standard format
    ui->I_CT_HD_SGBM->setPixmap(QPixmap::fromImage(CT_SGBM));//display the image in label that is created earlier
    ui->I_CT_HD_SGBM->repaint();

    /******************************************************
     * Compare computed disparity map against ground truth
     ******************************************************/
    if ((GT_Image.data != NULL) & (GT_Image.size == in_imgL.size) &( GT_Image.size == in_imgR.size))
    {
        // Get region of interest as described in Figure 4 (Lastenheft)
        cv::Mat ROI_GT = GT_Image(cv::Range(m_pStereoImg->m_u8BlockSize_half, in_imgL.rows-m_pStereoImg->m_u8BlockSize_half), cv::Range(m_pStereoImg->m_u16xMin + m_pStereoImg->m_u8BlockSize_half,  m_pStereoImg->m_u16xMax + m_pStereoImg->m_u8BlockSize_half));
        cv::Mat diff_img(ROI_GT.rows, ROI_GT.cols, CV_8U);
        // Compute error and difference image
        float img_error = Diff_and_Error(ROI_CT_SGBM, diff_img, ROI_GT, true);
        ui->L_error_6->setNum(img_error);
        ui->L_error_6->repaint();

        // Plot a simple histogram to show error distribution
        Mat Histo = Histogram(diff_img);
        QImage Hist((uchar*)Histo.data, Histo.cols, Histo.rows, Histo.step, QImage::Format_RGB16); //Converts the CV image into Qt standard format
        ui->I_CT_HD_Hist->setPixmap(QPixmap::fromImage(Hist));//display the image in label that is created earlier
        ui->I_CT_HD_Hist->repaint();
        //Show difference image
        QImage Diff((uchar*)diff_img.data, diff_img.cols, diff_img.rows, diff_img.step, QImage::Format_Grayscale8); //Converts the CV image into Qt standard format
        ui->I_CT_HD_Diff->setPixmap(QPixmap::fromImage(Diff));//display the image in label that is created earlier
        ui->I_CT_HD_Diff->repaint();
    }

    else {
        printf("\nNo Groundtruth or incopatible size. Skipping ground truth comparisson\n");
        ui->L_error_6->setText("---");
        ui->L_error_6->repaint();

        ui->I_CT_HD_Diff->clear();
        ui->I_CT_HD_Diff->repaint();
    }

    //--------------------Set the RUN button green when computation is over-------------------------
    ui->B_Run->setStyleSheet("border: 1px; background-color: rgb(78, 154, 6)"); ui->B_Run->repaint();
    return 0;
}



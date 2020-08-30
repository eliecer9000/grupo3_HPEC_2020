#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ui_mainwindow.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "sgbm.h"

#include <QDir>

#define MAX_UINT64 std::numeric_limits<unsigned long long>::max()

const int OutputTestdata = 0;

using namespace std;
using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // List of source images
    string sources;

    // Input images from GUI
    Mat in_imgL;
    Mat in_imgR;
    Mat GT_Image;

    //Parameters from GUI
    int MinDisp = 0;
    int MaxDisp = 0;
    uint8_t m_u8BlockSize_half = 0;
    int CTm_u8BlockSize_half = 0;
    int P1 = 0;
    int P2 = 0;
    int UniqRatio = 0;
    int SGBMDir = 0;

private slots:
    // Functions executed on pressing buttons in the GUI
    void ButtonClickRight(void);
    void ButtonClickLeft (void);
    void on_B_GTPickBtn_clicked();
    void on_P_Update_In_clicked();
    int on_B_Run_clicked();

private:
    Ui::MainWindow *ui;
    QListWidgetItem * m_CurItemLeft;
    QListWidgetItem * m_CurItemRight;

    StereoFPGA *m_pStereoImg = nullptr;
};

#endif // MAINWINDOW_H

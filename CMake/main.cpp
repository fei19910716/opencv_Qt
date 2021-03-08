
#include <QQuickItem>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <QApplication>


#include "src/log/LogManager.h"
#include "src/UI/cmainwindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc,argv);
    LogManager::init();

    cv::Mat image;

    image = cv::imread("../test.png");
    if (image.data)
    {
        cv::Mat gray_img;

        cvtColor(image, gray_img, cv::COLOR_BGR2GRAY);
        cv::imshow("hello opencv",gray_img);
    }


    CMainWindow w;
    w.show();

    bool result = app.exec();
    LogManager::destroy();
    return result;

}



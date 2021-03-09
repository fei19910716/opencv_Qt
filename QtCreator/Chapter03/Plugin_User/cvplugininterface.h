#ifndef CVPLUGININTERFACE_H
#define CVPLUGININTERFACE_H

#include <QObject>
#include <QString>
#include "opencv2/opencv.hpp"

// 这个接口类，创建插件和主程序都需要导入到工程中
class CvPluginInterface
{
public:
    virtual ~CvPluginInterface() {}
    virtual QString description() = 0;
    virtual void processImage(const cv::Mat &inputImage, const cv::Mat &outputImage) = 0;
};

#define CVPLUGININTERFACE_IID "com.amin.cvplugin"
Q_DECLARE_INTERFACE(CvPluginInterface, CVPLUGININTERFACE_IID)

#endif // CVPLUGININTERFACE_H

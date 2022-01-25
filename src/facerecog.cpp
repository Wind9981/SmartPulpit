#include <facerecog.h>
#include <iostream>
#include <string>
#include <chrono>
#include <NvInfer.h>
#include <NvInferPlugin.h>
#include <opencv2/opencv.hpp>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/Xrender.h>
#include <cstdint>
#include <cstring>
#include <vector>
#include <l2norm_helper.h>
#include <opencv2/highgui.hpp>
#include "faceNet.h"
#include "videoStreamer.h"
#include "network.h"
#include "mtcnn.h"
#include <QString>
#include <unistd.h>



using namespace nvinfer1;
using namespace nvuffparser;

class ScreenShot
{
    Display* display;
    Window root;
    int x,y,width,height;
    XImage* img{nullptr};
public:
    ScreenShot(int x, int y, int width, int height):
        x(x),
        y(y),
        width(width),
        height(height)
    {
        display = XOpenDisplay(nullptr);
        root = DefaultRootWindow(display);
    }

    void operator() (cv::Mat& cvImg)
    {
        if(img != nullptr)
            XDestroyImage(img);
        img = XGetImage(display, root, x, y, width, height, AllPlanes, ZPixmap);
        cvImg = cv::Mat(height, width, CV_8UC4, img->data);
    }

    ~ScreenShot()
    {
        if(img != nullptr)
            XDestroyImage(img);
        XCloseDisplay(display);
    }
};

void Worker::doWork(const QString &parameter){
    Logger gLogger = Logger();
    // Register default TRT plugins (e.g. LRelu_TRT)
    if (!initLibNvInferPlugins(&gLogger, "")) { return ; }

    // USER DEFINED VALUES
    const string uffFile="../facenetModels/facenet.uff";
    const string engineFile="../facenetModels/facenet.engine";
    DataType dtype = DataType::kHALF;
    //DataType dtype = DataType::kFLOAT;
    bool serializeEngine = true;
    int batchSize = 1;
    int nbFrames = 0;
    int videoFrameWidth = 640;
    int videoFrameHeight = 480;
    int maxFacesPerScene = 1;
    float knownPersonThreshold = 0.6;
    bool isCSICam = false;
    string personName;
    int error;

    // init facenet
    FaceNetClassifier faceNet = FaceNetClassifier(gLogger, dtype, uffFile, engineFile, batchSize, serializeEngine,
            knownPersonThreshold, maxFacesPerScene, videoFrameWidth, videoFrameHeight);

    // init opencv stuff
    VideoStreamer videoStreamer = VideoStreamer(0, videoFrameWidth, videoFrameHeight, 60, isCSICam);
    cv::Mat frame;
    ScreenShot screen(0,0,1024,600);
    cv::Mat img;

    // init mtCNN
    mtcnn mtCNN(videoFrameHeight, videoFrameWidth);

    //init Bbox and allocate memory for "maxFacesPerScene" faces per scene
    std::vector<struct Bbox> outputBbox;
    outputBbox.reserve(maxFacesPerScene);

    // get embeddings of known faces
    std::vector<struct Paths> paths;
    cv::Mat image;
    getFilePaths("../imgs", paths);
    for(int i=0; i < paths.size(); i++) {
        loadInputImage(paths[i].absPath, image, videoFrameWidth, videoFrameHeight);
        outputBbox = mtCNN.findFace(image);
        std::size_t index = paths[i].fileName.find_last_of(".");
        std::string rawName = paths[i].fileName.substr(0,index);
        faceNet.forwardAddFace(image, outputBbox, rawName);
        faceNet.resetVariables();
    }
    outputBbox.clear();
    int Switch = 1;
    int loop = 1;
    std::vector<int> param(2);
    param[0] = cv::IMWRITE_JPEG_QUALITY;
    param[1] = 80;//default(95) 0-100
    while (loop == 1) {
        videoStreamer.getFrame(frame);
        if (frame.empty()) {
            std::cout << "Empty frame! Exiting...\n Try restarting nvargus-daemon by "
                         "doing: sudo systemctl restart nvargus-daemon" << std::endl;
            break;
        }
        if (Switch == 1){
            cv::imwrite("/home/hoang/workspace/faceregconition/mtcnn_facenet_cpp_tensorRT/src/Images/a.jpeg", frame, param);
            emit resultReady(QString::fromStdString("1"));
            Switch = 2;
        } else {
            cv::imwrite("/home/hoang/workspace/faceregconition/mtcnn_facenet_cpp_tensorRT/src/Images/b.jpeg", frame, param);
            emit resultReady(QString::fromStdString("2"));
            Switch = 1;
        }
        outputBbox = mtCNN.findFace(frame);
        faceNet.forward(frame, outputBbox);
        personName = faceNet.featureMatching(frame);
        faceNet.resetVariables();

        //cv::imshow("VideoSource", frame);
        nbFrames++;
        outputBbox.clear();
        frame.release();
        
        if(personName == parameter.toStdString()){
            emit resultReady(QString::fromStdString(personName));
            // while(true){
            //     videoStreamer.getFrame(frame);
            //     if (frame.empty()) {
            //         std::cout << "Empty frame! Exiting...\n Try restarting nvargus-daemon by "
            //                     "doing: sudo systemctl restart nvargus-daemon" << std::endl;
            //         break;
            //     }
            //     std::vector<int> param(2);
            //     param[0] = cv::IMWRITE_JPEG_QUALITY;
            //     param[1] = 80;//default(95) 0-100
            //     cv::imwrite("/home/hoang/img/webcam.jpg", frame, param);
            //     screen(img);
            //     //imshow("img", img);
            //     cv::imwrite("/home/hoang/img/screen.jpg", img, param);
            //     frame.release();
            //     //usleep(33);
            // }
            break;
        }
    }
    videoStreamer.release();
    return;
}

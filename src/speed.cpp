#include "model/yolo.hpp"
#include "common/timer.hpp"
#include "common/image.hpp"
#include "common/position.hpp"


void SpeedTest()
{
    cv::Mat image = cv::imread("inference/persons.jpg");
    auto yolo = yolo::load("yolov8n.engine", yolo::YoloType::YOLOV8);
    if (yolo == nullptr) return;
    nv::EventTimer tm;
    tm.start();
    for (int i = 0; i < 100; i++)
    {
        auto objs = yolo->forward(tensor::cvimg(image));
    }
    tm.stop();
    tm.start();
    for (int i = 0; i < 100; i++)
    {
        auto objs = yolo->forward(tensor::cvimg(image), image.cols, image.rows, 0.0f, 0.0f);
    }
    tm.stop();
}
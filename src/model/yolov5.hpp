#ifndef YOLOV5_HPP__
#define YOLOV5_HPP__
#include <vector>
#include "common/memory.hpp"
#include "common/image.hpp"

namespace yolov5
{

struct Box 
{
    float left, top, right, bottom, confidence;
    int class_label;

    Box() = default;
    Box(float left, float top, float right, float bottom, float confidence, int class_label)
        : left(left),
            top(top),
            right(right),
            bottom(bottom),
            confidence(confidence),
            class_label(class_label) {}
    friend std::ostream& operator<<(std::ostream& os, const Box& box)
    {
        os << std::fixed << std::setprecision(2)  // 设置浮点数精度
           << "Box:\n"
           << "  Left:      " << std::setw(6) << box.left << "\n"
           << "  Top:       " << std::setw(6) << box.top << "\n"
           << "  Right:     " << std::setw(6) << box.right << "\n"
           << "  Bottom:    " << std::setw(6) << box.bottom << "\n"
           << "  Confidence: " << std::setw(6) << box.confidence << "\n"
           << "  Class Label: " << box.class_label;
        return os;
    }
};

using BoxArray = std::vector<Box>;


class Infer {
public:
    virtual BoxArray forward(const tensor::Image &image, int slice_width, int slice_height, float overlap_width_ratio, float overlap_height_ratio, void *stream = nullptr) = 0;
    virtual BoxArray forward(const tensor::Image &image, void *stream = nullptr) = 0;
    virtual BoxArray forwards(void *stream = nullptr) = 0;
};

std::shared_ptr<Infer> load(const std::string &engine_file, int gpu_id = 0, float confidence_threshold=0.5f, float nms_threshold=0.45f);

}



#endif
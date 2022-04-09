#ifndef BINOCS_CONTROL_IMAGE_SOURCE_H_
#define BINOCS_CONTROL_IMAGE_SOURCE_H_

#include <opencv2/opencv.hpp>

/**
 * @brief 
 * @details cv::Mats are basically shared_ptrs so we don't need to track a ptr
 */
struct image_collection_t {
    cv::Mat left_im;
    cv::Mat right_im;

};

/**
 * @brief Image source interface, generates images for use in the pipeline
 * @details this is an interface to allow multiple different source types.  This is a class as many
 * of these source types will need to manage the state of a physical device or interface.
 *
 */
class iImageSource {
    virtual image_collection_t GetImages() = 0;
};

class USBStereoSource : iImageSource {
  public:
    /**
     * @brief Construct a new USBStereoSource object.  
     * @details This is a USB stereo camera.  It is assumed that the images come in one channel appended automatically  
     * 
     * @param dev_name linux base name for device e.g. /dev/video3
     */
    USBStereoSource(const std::string &dev_name);

    image_collection_t GetImages();

  private:
    cv::VideoCapture cap;
    cv::Mat raw_image;
    cv::Mat left_im;
    cv::Mat right_im;
};

#endif
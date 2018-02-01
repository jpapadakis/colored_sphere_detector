/* 
 * File:   main.cpp
 * Author: John Papadakis
 *
 * Created on January 25, 2018, 2:41 PM
 */

#include <SphereDectector.hpp>
#include <rgbd_drivers_uncc/rgbd_driver.hpp>

/*
 * 
 */
int main(int argc, char** argv) {
    SphereDetector detector;
    
    std::cout << "Opening bag file: " << argv[1] << " for reading...\n";
    RGBD_BagFile_Driver bagfile_reader(argv[1]);
    
    boost::function<std::vector<std::pair<cv::Vec3f, Color>> (cv::Mat&, cv::Mat&, cv::Mat&, cv::Mat&)> callback(
            boost::bind(&SphereDetector::detect, &detector, _1, _2, _3, _4));    
    bagfile_reader.setCallback(callback);

    std::vector<std::string> topics;
    topics.push_back(std::string("/camera/rgb/image_color"));
    //topics.push_back(std::string("/camera/rgb/input_image"));
    topics.push_back(std::string("/camera/rgb/camera_info"));
    //topics.push_back(std::string("/camera/depth_registered/input_image"));
    topics.push_back(std::string("/camera/depth/image"));
    bagfile_reader.setTopics(topics);

    bagfile_reader.readRGBDMessages();
    
    return 0;
}


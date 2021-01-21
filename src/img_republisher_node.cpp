//
// Created by chrisliu on 2020/10/21.
//
#include "ros/ros.h"
#include "sensor_msgs/Image.h"
#include "opencv2/opencv.hpp"

#include "cv_bridge/cv_bridge.h"

using namespace cv;
using namespace std;

ros::Publisher img_pub;

void img_callback(const sensor_msgs::ImageConstPtr &img_msg)
{
    cv_bridge::CvImageConstPtr ptr = cv_bridge::toCvCopy(img_msg, sensor_msgs::image_encodings::BGR8);

    img_pub.publish(ptr->toImageMsg());
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "undistortFisheye_node");
    ros::NodeHandle nh;

    ros::Subscriber img_sub = nh.subscribe("/camera/color/image_raw", 100, img_callback);

    img_pub = nh.advertise<sensor_msgs::Image>("republish_img",1000);


    ros::spin();
    return 0;
}
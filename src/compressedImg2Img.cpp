//
// Created by chrisliu on 2020/12/2.
//

#include "ros/ros.h"
#include "sensor_msgs/CompressedImage.h"
#include "sensor_msgs/image_encodings.h"
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
static void ImageCallback(const sensor_msgs::CompressedImageConstPtr &msg)
{
    try
    {
        cv_bridge::CvImagePtr cv_ptr_compressed = cv_bridge::toCvCopy(msg,sensor_msgs::image_encodings::BGR8);
        cv::Mat imgCallback = cv_ptr_compressed->image;
        cv::imshow("compressedImgCallback",imgCallback);
        char key = cv::waitKey(1);
        if (key == 'q' || key == 'Q')
        {
            string imgname = "/home/chrisliu/NewDisk/ROSws/img_ws/src/uncompressed.jpg";
            imwrite(imgname, imgCallback);
        }
        cout<<"cv_ptr_compressed: "<<cv_ptr_compressed->image.cols<<" h: "<<cv_ptr_compressed->image.rows<<endl;
    }
    catch (cv_bridge::Exception& e)
    {
        //ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
    }
}

static void CompressedImageCallback(const sensor_msgs::ImageConstPtr &msg)
{
    try
    {
        cv_bridge::CvImagePtr cv_ptr_compressed = cv_bridge::toCvCopy(msg,sensor_msgs::image_encodings::BGR8);
        cv::Mat imgCallback = cv_ptr_compressed->image;
        cv::imshow("imgCallback",imgCallback);
        char key = cv::waitKey(1);
        if (key == 'q' || key == 'Q')
        {
            string imgname = "/home/chrisliu/NewDisk/ROSws/img_ws/src/compressed.jpg";
            imwrite(imgname, imgCallback);
        }
        cout<<"cv_ptr_compressed: "<<cv_ptr_compressed->image.cols<<" h: "<<cv_ptr_compressed->image.rows<<endl;
    }
    catch (cv_bridge::Exception& e)
    {
        //ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
    }
}
int main(int argc, char **argv)
{
    ros::init(argc, argv, "CompressedImage");
    ros::NodeHandle nh;
    ros::Subscriber image_sub = nh.subscribe("/camera/color/image_raw/compressed",10,ImageCallback);
//    ros::Subscriber compressedImage_sub = nh.subscribe("/camera/color/image_raw",10,CompressedImageCallback);

    ros::Rate loop_rate(10);
    while (ros::ok())
    {
        ROS_INFO("ROS OK!");
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}
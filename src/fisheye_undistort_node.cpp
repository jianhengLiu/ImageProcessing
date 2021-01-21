//
// Created by chrisliu on 2020/10/21.
//
#include "ros/ros.h"
#include "opencv2/opencv.hpp"

#include "image_transport/image_transport.h"
#include "cv_bridge/cv_bridge.h"

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "trajGenerator_node");
    ros::NodeHandle nh;

    image_transport::ImageTransport it(nh);
    image_transport::Publisher pub_undistort_fisheye = it.advertise("undistortFisheye",1);

    cv::Matx33d intrinsic_matrix;
    intrinsic_matrix<<200.1230529821021, 0, 319.0261836498302,
    0, 200.050750054437, 218.9617650999124,
    0, 0, 1;
    cv::Vec4d distortion_coeffs;
    distortion_coeffs<<0.664207, 0.0574451, -0.335926, 0.160933;
    Mat R = Mat::eye(3,3,CV_32F);
    Size image_size(640,480);
    Mat mapx = Mat(image_size,CV_32FC1);
    Mat mapy = Mat(image_size,CV_32FC1);
    fisheye::initUndistortRectifyMap(intrinsic_matrix,distortion_coeffs,R,intrinsic_matrix,image_size,CV_32FC1,mapx,mapy);

    VideoCapture inputVideo(4);
    if (!inputVideo.isOpened())
    {
        cout << "Could not open the input video " << endl;
        return -1;
    }
    Mat frame;
    Mat frameUndistort;
    while (ros::ok())
    {
        inputVideo >> frame;

        cv::remap(frame,frameUndistort,mapx, mapy, INTER_LINEAR);

        pub_undistort_fisheye.publish(cv_bridge::CvImage(std_msgs::Header(),"bgr8",frameUndistort).toImageMsg());
        imshow("undistortImg",frameUndistort);
        waitKey(1);
    }
}
/* 
 * License: Apache 2.0
 * Copyright(c) 2021 MINDS-i Inc
 * based on code from Intel Corporation: Apache 2.0 Copyright(c) 2015
 */

/* basic test of the Intel(c) realsense T265 camera 
 * reporting pose and image data 
 * and using openCV to display the image */

#include <opencv2/opencv.hpp>
#include <librealsense2/rs.hpp>
#include <iostream>

using namespace cv;

int main() 
{
  namedWindow("Test");
  std::string serial;
  
  rs2::pipeline p;
  rs2::config cfg;
  if(!serial.empty())
    cfg.enable_device(serial);
  cfg.enable_stream(RS2_STREAM_POSE, RS2_FORMAT_6DOF);
  /*both Fisheye streams must be enabled*/
  cfg.enable_stream(RS2_STREAM_FISHEYE,1, RS2_FORMAT_Y8);
  cfg.enable_stream(RS2_STREAM_FISHEYE,2, RS2_FORMAT_Y8);
  rs2::pipeline_profile p_profile = p.start(cfg);

  int fisheye_sensor_idx=1;/*1 or 2*/
  rs2::stream_profile fishY_stream_prof = p_profile.get_stream(RS2_STREAM_FISHEYE, fisheye_sensor_idx);
  rs2_intrinsics intr = fishY_stream_prof.as<rs2::video_stream_profile>().get_intrinsics();
  
  int lcnt=0;

  while (lcnt<10000){
    auto frames = p.wait_for_frames();
    rs2::pose_frame p_frame = frames.get_pose_frame();
    
    rs2::video_frame fisheye_frame = frames.get_fisheye_frame(fisheye_sensor_idx);
    rs2_pose pose_data = p_frame.get_pose_data();

    std::cout<<"Position z: "<<pose_data.translation.z<<"\n";

    Mat fisheye_mat(Size(fisheye_frame.get_width(), fisheye_frame.get_height()), CV_8UC1, (void*)fisheye_frame.get_data(), Mat::AUTO_STEP);

    imshow("Test",fisheye_mat);
    char c = (char)waitKey(25);
    if(c==27)
      break;
    lcnt++;
  }

  return 0;
}


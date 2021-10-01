/* License: Apache 2.0
 * Copyright(c) 2021 MINDS-i Inc
 * based on code from Intel Corporation: Apache 2.0 Copyright(c) 2015
 */

/* basic test of the Intel(c) realsense T265 camera reporting pose data */

#include <librealsense2/rs.hpp>
#include <iostream>


int main() 
{
  std::string serial;
  
  rs2::pipeline p;
  rs2::config cfg;
  if(!serial.empty())
    cfg.enable_device(serial);
  cfg.enable_stream(RS2_STREAM_POSE, RS2_FORMAT_6DOF);

  rs2::pipeline_profile p_profile = p.start(cfg);

  int lcnt=0;

  while (lcnt<5000){
    auto frames = p.wait_for_frames();
    rs2::pose_frame p_frame = frames.get_pose_frame();
    
    rs2_pose pose_data = p_frame.get_pose_data();

    std::cout<<"Position: "<<pose_data.translation.x<<" :  "<<pose_data.translation.y<<" :  "<<pose_data.translation.z<<"\n ";

    lcnt++;
  }

  return 0;
}


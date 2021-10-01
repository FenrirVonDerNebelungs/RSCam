# RSCam
Code for running the Intel(c) realsense T265 camera
Note: for the jetson nano the camera may require powering the nano from the barrel jack (and setting the corrresponding jumper)

Code was tested on a Nvidia Jetson Nano running Ubuntu 18.04 LTS
Requires the librealsense SDK to be installed (currently SDK2)

compile hellors.cpp   
$ g++ -std=c++11 hellors.cpp -lrealsense2 -o helloex

Open CV was installed and built from source, for openCV to compile the appropriate environment variables must be set in the shell. currently sourcing the uploaded shell script setenv.sh

compile rsImg.cpp   
$ g++ -std=c++11 rsImg.cpp -lrealsense2 -lopencv_core -lopencv_highgui -o rsImgex

# Tinker
Some tinkering with OpenCV and C++ threads

## Requirements
### Ubuntu 18.04 
(It is not recommended to try on Ubuntu 20.04 . OpenCV and Gstreamer pipeline has issues and whether you use `FFMPEG` or `V4L` for the back side, it still doesn't work and results in not getting any feed from the camera.  
Just for the warning, `HOURS_WASTED_ON_FIXING_PIPELINE = 6`)  

### OpenCV 4.2.0  
Even though I just tried on this version, this code is expected to work on stable versions like 3.4.9 or any other.  

### CMake 3.10
On the CMakeLists.txt file of the project, it is specified that minimum required CMake version is to be 3.10. It will work on any higher version(Such as: 3.22) but not guaranteed to work on lower versions.  

### GCC 8
This project is built on C++17 standards and GCC 8. Minimum required version for C++17 is GCC 5, so it is expected that it will work anything with GCC 5 or above.  

## Build steps:
```
git clone https://github.com/yhdurkaya/Tinker.git
cd Tinker/
mkdir build
cd build/
cmake ..
make
```

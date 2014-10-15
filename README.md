OpenCV-VTK
==========

Simple program to visualise the differences between OpenCV and VTK coordinate system. Modify the cv::flip and cvtColor definitions in the cxx file to see the changes. The flag 0 in cv::flip(vtkImage, openCvimage, 0) is for 180 degree rotation about X-axis. If you comment this line, you can see that the image is upside down. If you comment the cvtColor(openCvimage, openCvimage, CV_RGB2BGR), the red cone in VTK image will be seen as blue in OpenCV image, green cone remains the same and blue in VTK will change to red in Opencv image. Hence both flip with flag 0 and colour channel conversion (RGB2BGR) is necessary to recover the exact image from VTK render window.


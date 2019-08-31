**This directory contains the main process of face detection and face face verification**


**RFCN Baseline**:

![](yuewenjun/facedetection_faceverification/picture/Screenshot_from_2019-05-09_14-31-11.png)

1.  The sensor on the board catches the light information and restored it within the YUV form. 
Every single frame contains 1080x1920 pixels, which occupys 1080x1920 bytes memory(because YUV420SP distribute one byte for each pixel)

2.  Then this part of memory which restored the fresh frame was sent to the VPSS. In our framework, VPSS has two mainly functions.
Each function is an abstraction of a small part of the whole VPSS process, every one of them has an explicit goal to achieve.

3.   VPSS:
    
The first main function is aimed to **run forward the neural network**. 
The source Blob is the very repository of the raw YUV information. The destination Blob is malloced to restore the result of network process
(the pixelformat of the source blob and destination blob can be different).
    
The other focusses on **absorbing the valuable information from the raw destination Blob to Software parameter**, 

4.  After VPSS we come to a very critical part of the whole process, VGS, in which we achieved **the presentation of the results**. 
It's critical because he made it possible to display the results vividly on the screen, so that we can check out if our strategy works well.
Furthermore, people can only be convinced by what they have seen, so the presentation of the results can persuade orhers invest on our company more easily.


**face detection & face verification**

**Our goal:** Develop a stable and efficient system of face detection and verification which can be distributed to authentication system.

**Baseline:** 

![](yuewenjun/facedetection_faceverification/picture/Screenshot_from_2019-05-09_13-50-55.png)
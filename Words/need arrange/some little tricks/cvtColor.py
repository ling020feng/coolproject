# -*- coding:utf-8 -*-
import cv2 as cv

# 色彩空间的转换
def color_space_demo(image):
    gray = cv.cvtColor(image, cv.COLOR_BGR2GRAY)  # RGB转换为gray
    cv.imshow("rgb-->gray", gray)
    hsv = cv.cvtColor(image, cv.COLOR_BGR2HSV)  # RGB转换为hsv
    cv.imshow("rgb-->hsv", hsv)
    yuv = cv.cvtColor(image, cv.COLOR_BGR2YUV)  # RGB转换为yuv
    cv.imshow("rgb-->yuv", yuv)


src = cv.imread("dog_bike_car_416.jpg")
cv.namedWindow("yuanshi-1", cv.WINDOW_AUTOSIZE)
cv.imshow("yuanshi-1", src)
color_space_demo(src)
cv.waitKey(0)
cv.destroyAllWindows()


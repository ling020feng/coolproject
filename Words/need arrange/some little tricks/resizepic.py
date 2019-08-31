# coding: utf-8
import cv2 as cv

img = cv.imread('./61.jpg')
cv.rectangle(img_test,(,92),(74,104),(0,255,0),1)
cv.imwrite('./resized_61.jpg',img_test)
cropped = img_test[92:104, 62:74]
cv.imwrite('./new61.jpg',cropped)

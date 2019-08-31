# coding: utf-8
import cv2 as cv

img = cv.imread('./frisbee_team.jpg')
img_test = cv.resize(img, (384,216))
#cv.rectangle(img_test,(62,92),(74,104),(0,255,0),1)
cv.imwrite('./resized_432.jpg',img_test)
cropped = img_test[92:104, 62:74]
cv.imwrite('./12.jpg',cropped)
# -*- coding: utf-8 -*-
# sometimes we want to tailor a net to fit our trainning goals
# we'd better tailor the caffemodel at the same time, this operation can help us save memory

import caffe 
import caffe_pb2 

BEFORE_MODIFY_DEPLOY_NET = "yourpath/before_modify_deploy.prototxt" 
AFTER_MODIFY_DEPLOY_NET = "yourpath/after_modify_deploy.prototxt" 
BEFORE_MODIFY_CAFFEMODEL = "yourpath/before_modify.caffemodel" 
AFTER_MODIFY_CAFFEMODEL = "yourpath/after_modify.caffemodel" 


#根据prototxt修改caffemodel 
net = caffe.Net(AFTER_MODIFY_DEPLOY_NET, BEFORE_MODIFY_CAFFEMODEL,caffe.TEST) 
net.save(AFTER_MODIFY_CAFFEMODEL ) 
print("加载修改前后的caffemodel") 
model = caffe_pb2.NetParameter() 
f=open(BEFORE_MODIFY_CAFFEMODEL, 'rb') 
model.ParseFromString(f.read()) 
f.close() 
layers_name = [layer.name for layer in model.layers] 
print("修改前",layers_name) 
model2 = caffe_pb2.NetParameter() 
f=open(AFTER_MODIFY_CAFFEMODEL , 'rb') 
model2.ParseFromString(f.read()) 
f.close() 
layers2_name = [layer.name for layer in model2.layer] 
print("修改后",layers2_name)

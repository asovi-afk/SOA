#! /bin/bash

# device_profiles
url='http://localhost:59881/api/v2/deviceprofile/uploadfile'
file_sensor='file=@./init_files/sensorClusterDeviceProfile.yaml' 
curl -X POST -F $file_sensor $url

file_controller='file=@./init_files/windowControllerDeviceProfile.yaml' 
curl -X POST -F $file_controller $url

# device_requests
url='http://localhost:59881/api/v2/device'
file='./init_files/addSensorDeviceRequest.json' 
curl -X POST -T $file $url

file='./init_files/addControllerDeviceRequest.json' 
curl -X POST -T $file $url



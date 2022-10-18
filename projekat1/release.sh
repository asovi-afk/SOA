#! /bin/bash
# removing conteiners
CmongoDB='mongo_db_container'
CpythonAPI='gateway_container'
docker rm -f $CpythonAPI $CmongoDB 

#removing images
ImongoDB='projekat1_gateway:latest'
IpythonAPI='projekat1_mongo_db:latest'
#docker image remove $IpythonAPI $ImongoDB

#removing volumes by removing all unused local volumes
#docker volume prune -f 
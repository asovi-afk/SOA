#! /bin/bash
container='mongo_db_container'
docker exec $container /bin/bash ./reinitDB.sh
#! /bin/bash
container='mongo_db_container_p2'
docker exec $container /bin/bash ./reinitDB.sh
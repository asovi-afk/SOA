#! /bin/bash
container='notification_container'
docker exec -it $container tail -f /logs.txt
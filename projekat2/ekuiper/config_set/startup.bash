#!/bin/bash

/bin/bash /config_set/add_streams_rules.bash &

# remove ipc from temp
cd /tmp
rm -rf $(ls)
cd /kuiper
# start kuiperd
exec "$@"

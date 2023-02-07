#!/bin/bash

cd /kuiper/bin

sleep 6

streams=(requests_stream mem_ses_tit_stream)
rules=(spike_rule formating_rule)

kuiper=./kuiper
config=/config_set

for i in "${streams[@]}"
do
    $kuiper create stream -f $config/$i.txt
done
for i in "${rules[@]}"
do
    $kuiper create rule $i -f $config/$i.json
done



FROM alpine:3.16

RUN ["apk", "update"]
RUN ["apk", "upgrade"]
RUN ["apk", "add", "libc6-compat"]

WORKDIR /app
COPY ./visualization .

ENTRYPOINT [ "./visualization" ]
#CMD [ "-mqtt-host=mqtt_brocker:1883", "-t=p3/edgex/edgex-export-2", "-influxdb-host=v-influxdb:8086"]
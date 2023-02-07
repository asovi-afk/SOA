FROM alpine:3.16

RUN ["apk", "update"]
RUN ["apk", "upgrade"]
RUN ["apk", "add", "libc6-compat"]

COPY analytics /

ENTRYPOINT [ "/analytics" ]
CMD ["-addr=notification:50051"]
FROM gcc:12.2.0

COPY ./grpc_server/cmake/build/server /
RUN touch logs.txt

ENTRYPOINT [ "/server" ]
#ENTRYPOINT ["sleep",  "1d"] # za debug
CMD []
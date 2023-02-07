FROM lfedge/ekuiper:1.7.0-alpine

COPY --chown=kuiper:kuiper ./config_set /config_set
COPY --chown=kuiper:kuiper ./highlights_zip /kuiper/plugins/portable/highlights

USER 0

RUN ["apk", "update"]
RUN ["apk", "upgrade"]
RUN ["apk", "add", "libc6-compat"]
RUN ["apk", "add", "bash"] 

#USER kuiper

ENTRYPOINT ["/bin/bash", "/config_set/startup.bash"]
CMD ["/kuiper/bin/kuiperd"]


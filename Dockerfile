FROM alpine
WORKDIR /home/vlad/kpi_vladik_donk
COPY ./donk . 
RUN apk add libstdc++
RUN apk add libc6-compat
ENTRYPOINT ["./donk"]


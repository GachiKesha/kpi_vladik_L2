FROM alpine AS build
RUN apk add --no-cache build-base automake autoconf
WORKDIR /home/vlad/kpi_vladik_donk
COPY . .
RUN autoreconf -fi 
RUN ./configure
RUN make

FROM alpine
COPY --from=build /home/vlad/kpi_vladik_donk/donk /usr/local/bin/donk
ENTRYPOINT ["/usr/local/bin/donk"]


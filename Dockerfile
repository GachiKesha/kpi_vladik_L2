FROM alpine AS build
RUN apk add --no-cache build-base automake autoconf
WORKDIR /home/vlad/kpi_vladik_donk
COPY . . 
RUN ./configure
RUN make

FROM alpine
COPY --from=build /home/vlad/kpi_vladik_L2/donk /usr/local/bin/donk
ENTRYPOINT ["/usr/local/bin/donk"]


FROM alpine AS build
RUN apk add --no-cache build-base automake autoconf git
WORKDIR /home/vlad/kpi_vladik_donk
RUN git clone --branch branchHTTPservMulti https://github.com/GachiKesha/kpi_vladik_L2.git .
RUN autoreconf -fi 
RUN ./configure
RUN make

FROM alpine
COPY --from=build /home/vlad/kpi_vladik_donk/donk /usr/local/bin/donk
ENTRYPOINT ["/usr/local/bin/donk"]


FROM gcc:11.3.0 as build
RUN apt-get install git -y
RUN git clone https://github.com/lDeathlWhisperl/Contest

FROM ubuntu:latest
RUN apt-get update && apt-get install
RUN apt-get install g++ -y
WORKDIR app
COPY --from=build /Contest/*.cpp .
COPY --from=build /Contest/*.sh .
RUN ["./compile.sh"]
ENTRYPOINT ["./launch.sh"]

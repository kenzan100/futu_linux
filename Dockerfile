FROM debian:latest

RUN apt-get -y update && apt-get install -y build-essential \
  && apt-get install -y vim

WORKDIR /home
ADD . /home

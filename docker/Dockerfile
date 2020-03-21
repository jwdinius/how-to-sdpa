FROM ubuntu:bionic

ENV SDPA_ROOT_DIR=/usr

# USE BASH
SHELL ["/bin/bash", "-c"]

# INSTALL SYSTEM-WIDE DEPENDENCIES
RUN apt-get update && apt-get install -y --allow-unauthenticated libomp-dev \
    libopenblas-dev liblapack-dev libsdpa-dev sdpa build-essential gfortran sudo \
    cmake

RUN adduser --disabled-password --gecos '' sdpa
RUN echo '%sudo ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers

USER sdpa
WORKDIR /home/sdpa
RUN cp -r /usr/share/sdpa/libexample /home/sdpa/libexample

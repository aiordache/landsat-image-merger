#!/bin/bash
IMAGEID=opencv
# set xorg access on host
xhost +local:docker
ABS_PATH="$(pwd)"
docker run -it --rm \
	-e DISPLAY=:0 \
	-v /tmp/.X11-unix:/tmp/.X11-unix \
	-v /root/.Xauthority:/root/.Xauthority:rw  \
	-v $ABS_PATH:/root \
    -p 8080:8080 \
    $IMAGEID




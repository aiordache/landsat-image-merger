#!/bin/bash
IMAGEID=opencv
# set xorg access on host
xhost +local:docker

CID=$(docker create \
	-e DISPLAY=:0 \
	-v /tmp/.X11-unix:/tmp/.X11-unix \
	-v /root/.Xauthority:/root/.Xauthority:rw  \
	-v project:/root/project \
	 -i $IMAGEID)
docker rename $CID satellite
docker start $CID
docker exec -it $CID /bin/bash




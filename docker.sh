#!/bin/bash
IMAGEID="opencv:latest"
# set xorg access on host
xhost +local:docker
ABS_PATH="$(pwd)"


function setup_image() 
{
    docker build -t $IMAGEID .
}

function start_container() 
{
    CID=$(docker create \
	    -e DISPLAY=:0 \
	    -v /tmp/.X11-unix:/tmp/.X11-unix \
	    -v /root/.Xauthority:/root/.Xauthority:rw  \
	    -v $ABS_PATH:/root \
	     -i $IMAGEID)
    docker rename $CID landsat
    docker start $CID
    docker exec -it $CID /bin/bash
    
    echo "Container started. ID:landsat"
}
function start_temp_container() 
{
    docker run -it --rm \
	    -e DISPLAY=:0 \
	    -v /tmp/.X11-unix:/tmp/.X11-unix \
	    -v /root/.Xauthority:/root/.Xauthority:rw  \
	    -v $ABS_PATH:/root \
        $IMAGEID
}

function stop_container() 
{
    docker ps | grep landsat
    docker stop landsat 
    docker rm landsat
}


# ------------- ARG PARSER ----------- #
while [[ $# -gt 0 ]]
do
    action="$1"

    case $action in
        setup)
        echo -e "\n---------  Build Docker Image ---------\n"
        setup_image
        shift
        ;;
        start)
        echo -e "\n---------  Start container ---------\n"
        start_container
        shift
        ;;
        run)
        start_temp_container
        shift
        ;;
        stop)
        stop_container
        shift
        ;;
        *)
        echo "Unknown option $action"
        exit 1
        ;;
    esac
done



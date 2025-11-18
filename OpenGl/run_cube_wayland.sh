#!/bin/bash
set -e

xhost +SI:localuser:root

sudo docker run -it --rm \
    --device=/dev/dri \
    -e DISPLAY=$DISPLAY \
    -e XDG_RUNTIME_DIR=$XDG_RUNTIME_DIR \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    cube

xhost -SI:localuser:root


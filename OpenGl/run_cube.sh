sudo docker build -t cube .
xhost +
sudo docker run -it --rm \
    --device=/dev/dri \
    -e DISPLAY=$DISPLAY \
    -e XDG_RUNTIME_DIR=/tmp \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    cube
xhost -


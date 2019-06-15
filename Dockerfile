FROM debian:min

RUN apt-get update && apt-get -y install vim wget unzip cmake build-essential libcanberra-gtk3-module 

# for wxWidgets
RUN apt-get -y install libwxgtk3.0-0v5 libwxgtk3.0-dev libcanberra-gtk-module


RUN cd /tmp/;wget -O opencv-4.1.0.zip https://github.com/opencv/opencv/archive/4.1.0.zip; unzip opencv-4.1.0.zip;
RUN cd /tmp/opencv-4.1.0 ; mkdir build; 
RUN cd /tmp/opencv-4.1.0/build ;cmake ../; make -j7; make install; ldconfig;





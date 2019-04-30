
FROM debian:min

RUN apt-get update && apt-get -y install vim wget unzip cmake build-essential libcanberra-gtk-module libcanberra-gtk3-module 
#libopencv-dev libboost-all-dev 

# for wxWidgets
RUN apt-get -y install libwxgtk3.0-0v5 libwxgtk3.0-dev


#newest version of boost - including beast feature
RUN cd /tmp/;wget -O boost_1_68_0.tar.gz https://dl.bintray.com/boostorg/release/1.68.0/source/boost_1_68_0.tar.gz;tar xzf boost_1_68_0.tar.gz; chmod +x /tmp/boost_1_68_0/bootstrap.sh;
RUN cd /tmp/boost_1_68_0; ./bootstrap.sh --prefix=/usr
RUN cd /tmp/boost_1_68_0;./b2;./b2 install
RUN echo 'export NO_AT_BRIDGE=1' >> /root/.bashrc


# newest gtk3- compatible opencv version


RUN cd /tmp/;wget -O opencv-4.0.0-rc.zip https://github.com/opencv/opencv/archive/4.0.0-rc.zip; unzip opencv-4.0.0-rc.zip;
RUN cd /tmp/opencv-4.0.0-rc ; mkdir build; sed -i 's/\/usr\/local/\/usr/g' CMakeLists.txt; sed -i 's/\/opencv4//g' CMakeLists.txt; 
RUN cd /tmp/opencv-4.0.0-rc/build ;cmake ../; make -j7; make install; ldconfig;





# landsat-image-merger
Graphical tool to merge Landsat bands.

# Build
Install Docker

Build Image 
```
$ ./docker.sh setup
```
Run container
```
$ ./docker.sh run
non-network local connections being added to access control list
root@b6490fd72cb9:/# cd
root@b6490fd72cb9:~# ls
Dockerfile  LICENSE  Makefile  README.md  docker.sh  include  resources  src
```
Build and run project
```
root@b6490fd72cb9:~# make;./bin/program
```

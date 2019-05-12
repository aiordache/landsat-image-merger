CC=g++
#CFLAGS+=`pkg-config --cflags opencv`
CFLAGS+=`wx-config --cxxflags --libs std` -I/usr/local/include/opencv4/
#/usr/include /usr/lib
#LDFLAGS+=`pkg-config --libs opencv`
LDFLAGS+=-lpthread -lboost_system -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs
#/usr/lib /usr/include
BUILDDIR  = build
BINDIR    = bin
SOURCEDIR = src
EXECUTABLE = program

SOURCES = $(wildcard $(SOURCEDIR)/*.cpp)
OBJECTS = $(patsubst $(SOURCEDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

all: dir $(BINDIR)/$(EXECUTABLE)

dir:
	mkdir -p $(BUILDDIR)

$(BINDIR)/$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJECTS): $(BUILDDIR)/%.o : $(SOURCEDIR)/%.cpp
	$(CC) -c $(CFLAGS)  $< -o $@


clean:
	rm -f $(BUILDDIR)/* $(BINDIR)/$(EXECUTABLE)


#g++ artprov.cpp `wx-config --cxxflags --libs std` -o program

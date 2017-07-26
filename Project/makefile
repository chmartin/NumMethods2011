CC=g++
CFLAGS=-c -v
LDFLAGS= 
SOURCES=Project.cpp Lifetime.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Project

all: $(SOURCES) $(EXECUTABLE) 
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) `root-config --libs --cflags` -o $@ 

.cpp.o:
	$(CC) $(CFLAGS) $< `root-config --libs --cflags` -o $@ 
	
clean:
	rm -rf *o $(EXECUTABLE)
CC=g++
CFLAGS=-c -v
LDFLAGS= 
SOURCES=Stats.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Stats

all: $(SOURCES) $(EXECUTABLE) 
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) `root-config --libs --cflags` -o $@ 

.cpp.o:
	$(CC) $(CFLAGS) $< `root-config --libs --cflags` -o $@ 
	
clean:
	rm -rf *o $(EXECUTABLE)
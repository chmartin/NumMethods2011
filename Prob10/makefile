CC=g++
CFLAGS=-c -v
LDFLAGS= 
SOURCES=Prob10.cpp Van_der_Pol.cpp Lane_Emden.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Prob10

all: $(SOURCES) $(EXECUTABLE) 
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) `root-config --libs --cflags` -o $@ 

.cpp.o:
	$(CC) $(CFLAGS) $< `root-config --libs --cflags` -o $@ 
	
clean:
	rm -rf *o $(EXECUTABLE)
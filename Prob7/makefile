CC=g++
CFLAGS=-c -v
LDFLAGS=
SOURCES=Prob7.cpp Print.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Prob7

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -rf *o $(EXECUTABLE)
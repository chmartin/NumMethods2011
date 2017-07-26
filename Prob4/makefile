CC=g++
CFLAGS=-c -v
LDFLAGS=
SOURCES=Prob4.cpp Print.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Prob4

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -rf *o $(EXECUTABLE)
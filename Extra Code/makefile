CC=g++
CFLAGS=-c -v
LDFLAGS=
SOURCES=Example.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Example

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -rf *o $(EXECUTABLE)
CC=g++
CFLAGS=-c -v
LDFLAGS=
SOURCES=Prob11.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Prob11

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -rf *o $(EXECUTABLE)
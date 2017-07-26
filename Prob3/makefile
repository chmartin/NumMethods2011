CC=g++
CFLAGS=-c -v
LDFLAGS=
SOURCES=Prob3.cpp FunctI.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Prob3

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -rf *o $(EXECUTABLE)
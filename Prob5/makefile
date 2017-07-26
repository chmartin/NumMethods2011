CC=g++
CFLAGS=-c -v
LDFLAGS=
SOURCES=Prob5.cpp Func.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Prob5

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -rf *o $(EXECUTABLE)
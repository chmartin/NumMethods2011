CC=g++
CFLAGS=-c -v
LDFLAGS=
SOURCES=Prob6.cpp Func.cpp Print.cpp Func2.cpp FuncI.cpp Func3.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Prob6

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -rf *o $(EXECUTABLE)
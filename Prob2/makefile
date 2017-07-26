CC=g++
CFLAGS=-c -v
LDFLAGS=
SOURCES=Prob2.cpp RandList.cpp Print.cpp MatrixMult.cpp Transpose.cpp MatrixAdd.cpp Scale.cpp Hilbert.cpp MyMath.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Prob2Answer

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -rf *o $(EXECUTABLE)
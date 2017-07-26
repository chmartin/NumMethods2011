CC=g++
CFLAGS=-c -v
LDFLAGS=
SOURCES=Prob8.cpp Print.cpp InvIter.cpp RandList.cpp Norm.cpp MatrixAdd.cpp Scale.cpp VecMult.cpp VecAdd.cpp MatrixMult.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Prob8

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -rf *o $(EXECUTABLE)
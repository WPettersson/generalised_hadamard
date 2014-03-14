CPP=g++
CC_FLAGS=-Wall -fno-exceptions -Werror -Wl,-O1
#DEBUG=-g
DEBUG=-O2
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXEC=hadamard
%.o: %.cpp
	$(CPP) -c $(DEBUG) $(CC_FLAGS) $< -o $@

$(EXEC): $(OBJECTS)
	$(CPP) $(DEBUG) $(CC_FLAGS) $(OBJECTS) -o $(EXEC)

clean: 
	rm $(OBJECTS) $(EXEC)

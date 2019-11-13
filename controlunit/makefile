CC = g++
CCFLAGS = 
LFLAGS =  
SOURCES = controlunit.cpp moist.cpp main.cpp 
DEPS = controlunit.h moist.h
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = exe

$(EXECUTABLE): $(SOURCES)
	$(CC) -Wall -o $(EXECUTABLE) $(SOURCES)

.PHONY: clean
clean: ##Remove files made by makefile
	rm -f $(EXECUTABLE)

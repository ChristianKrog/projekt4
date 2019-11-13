CC = g++
CCFLAGS = -lwiringPi
LFLAGS =  
SOURCES = controlunit.cpp moist.cpp temperature.cpp main.cpp 
DEPS = controlunit.h moist.h temperature.h
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = exe

$(EXECUTABLE): $(SOURCES)
	$(CC) -Wall -o $(EXECUTABLE) $(SOURCES) $(CCFLAGS)

.PHONY: clean
clean: ##Remove files made by makefile
	rm -f $(EXECUTABLE)

CC = arm-rpizw-g++
CCFLAGS = 
LFLAGS =  
SOURCES = controlunit.cpp moist.cpp temperature.cpp arduinoIF.cpp main.cpp 
DEPS = controlunit.h moist.h temperature.h
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = exe
rpiAddress = root@10.9.8.2

$(EXECUTABLE): $(SOURCES)
	$(CC) -Wall -o $(EXECUTABLE) $(SOURCES) $(CCFLAGS)

.PHONY: clean
clean: ##Remove files made by makefile
	rm -f $(EXECUTABLE)

.PHONY: copy
copy: ##copy to rpi 
	scp $(EXECUTABLE) $(rpiAddress):
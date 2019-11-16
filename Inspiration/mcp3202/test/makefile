CC = g++ 
CCFLAGS = -ggdb -I. 
LFLAGS = -lbcm2835
SOURCES = test.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = exe
rpiAddress = root@10.9.8.2

all: $(EXECUTABLE) ##Complete build

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $(EXECUTABLE) -o $@ $^ $(LFLAGS)

%.o: %.cpp
	$(CC) -c -o $@ $^ $(CCFLAGS)

.PHONY: clean
clean: ##Remove files made by makefile
	rm -f *.o main

.PHONY: help
help:  ##Show help
	  @awk -F ':|##' '/^[^\t].+?:.*?##/ {\
        printf "\033[36m%-30s\033[0m %s\n", $$1, $$NF \
        }' $(MAKEFILE_LIST)

.PHONY: copy
copy: ##copy to rpi 
	scp $(EXECUTABLE) $(rpiAddress):

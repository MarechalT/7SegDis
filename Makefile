CC= gcc
CXX= g++
CFLAGS= -Wall
LIBS= -lwiringPi
TARGET = iLoveFood

.PHONY: default all clean

default: $(TARGET)

all: default reset

OBJECTS = $(patsubst %.cpp,%.o, $(wildcard *.cpp))
HEADERS = $(wildcard *.h)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CXX) $(TARGET).o -Wall $(LIBS) -o $@

reset: $(OBJECTS)
	$(CXX) reset7SD.o -Wall $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)
	-rm -f  reset7SD

CC= gcc
CXX= g++
CXXFLAGS= -Wall
LIBS= -lwiringPi
TARGET = iLoveFood

.PHONY: default all clean

default: $(TARGET)

possibilities: possibilities.o

all: default reset

OBJECTS = $(patsubst %.cpp,%.o, $(wildcard *.cpp))
HEADERS = $(wildcard *.hpp)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CXX) $(TARGET).o -Wall $(LIBS) -o $@

reset: $(OBJECTS)
	$(CXX) reset.o -Wall $(LIBS) -o $@

showall: showall.o translator7SD.o
	$(CXX) $(CXXFLAGS) $(LIBS) -o $@ $^

showall.o: showall.cc translator7SD.h
	$(CXX) $(CXXFLAGS) -c $(LIBS) $<

translator7SD.o: translator7SD.cc translator7SD.h
	$(CXX) $(CXXFLAGS) -c $(LIBS) $<

clean:
	-rm -f *.o $(TARGET) reset showall

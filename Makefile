CXX = g++
CXXFLAGS = -g -Wall
TARGET = main
OBJS = main.o Neo.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp Neo.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Neo.o: Neo.cpp Neo.h
	$(CXX) $(CXXFLAGS) -c Neo.cpp

clean:
	rm -f *.o $(TARGET)
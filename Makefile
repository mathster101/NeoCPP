CXX = g++
CXXFLAGS = -g -Wall
TARGET = main
BUILDDIR = build
OBJS = $(BUILDDIR)/main.o $(BUILDDIR)/Neo.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

$(BUILDDIR)/main.o: main.cpp Neo.h
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c main.cpp -o $(BUILDDIR)/main.o

$(BUILDDIR)/Neo.o: Neo.cpp Neo.h
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c Neo.cpp -o $(BUILDDIR)/Neo.o

clean:
	rm -rf $(BUILDDIR) $(TARGET)

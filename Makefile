CXX = g++
CXXFLAGS = -std=c++11 -fopenmp -Wall -Wextra
TARGET = app.exe
SRCS = main.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	del /f $(TARGET) 2>nul || rm -f $(TARGET)

run: $(TARGET)
	$(TARGET)

.PHONY: all clean run

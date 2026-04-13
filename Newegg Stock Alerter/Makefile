CXX = g++
CXXFLAGS = -IC:\vcpkg\installed\x64-mingw-dynamic\include
LDFLAGS = -LC:\vcpkg\installed\x64-mingw-dynamic\lib -lcurl
TARGET = prog

all:
	$(CXX) main.cpp $(CXXFLAGS) $(LDFLAGS) -o $(TARGET)

run:
	$(CXX) main.cpp $(CXXFLAGS) $(LDFLAGS) -o $(TARGET) && ./$(TARGET)

clean:
	rm -f $(TARGET).exe
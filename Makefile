CXX := g++
CXXFLAGS := -std=c++17 -Iinclude -Wall -Wextra
SRCS := src/main.cpp src/student.cpp src/student_portal.cpp src/console_io.cpp src/login.cpp src/profile.cpp src/dashboard.cpp src/settings.cpp
TARGET := student-portal

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $(SRCS)

clean:
	rm -f $(TARGET) $(TARGET).exe

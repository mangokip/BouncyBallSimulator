CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

SRC = src/main.cpp src/Ball.cpp src/Button.cpp src/Global.cpp  # 🔹 Added Button.cpp
OBJ = $(SRC:.cpp=.o)
INCLUDE = -Iinclude

TARGET = ball_sim

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET) -lsfml-graphics -lsfml-window -lsfml-system

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

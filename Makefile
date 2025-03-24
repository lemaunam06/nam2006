CXX = g++
CXXFLAGS = -Iinclude -I/ucrt64/include/SDL2 -std=c++17 -Wall
LDFLAGS = -L/ucrt64/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -mwindows

SRC = $(wildcard src/*.cpp)  # Lấy tất cả file .cpp trong src/
OBJ = $(SRC:.cpp=.o)
TARGET = Game/game

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
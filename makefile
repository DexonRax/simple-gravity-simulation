CXX = g++
CXXFLAGS = -std=c++17 -Wall -I.

LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRCS = main.cpp Planet.cpp Simulation.cpp Vector2.cpp
OBJS = $(SRCS:.cpp=.o)

TARGET = GravitySim

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: all
	@cp -r assets ./ 2>/dev/null || true
	@cp -r libs ./ 2>/dev/null || true
	./$(TARGET)

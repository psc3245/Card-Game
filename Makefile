CXX = g++
CXXFLAGS = -std=c++17 -I/opt/homebrew/include -I./Utility -I./Shapes -I./RideTheBus -I./Scenes
LDFLAGS = -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system

make:
	$(CXX) $(CXXFLAGS) -c main.cpp
	$(CXX) -o main main.o $(LDFLAGS)
	rm main.o

clean:
	rm main
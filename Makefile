make:
	g++ -c main.cpp
	g++ -o main main.o
	rm main.o

clean:
	rm main
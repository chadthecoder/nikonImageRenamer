all:
	g++-9 main.cpp -std=c++17 -o bin/renamer

run:
	./bin/renamer

clean:
	rm bin/renamer
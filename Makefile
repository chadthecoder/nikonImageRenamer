all:
	g++ main.cpp -std=c++17 -l boost_filesystem -o bin/renamer
	#g++ main.cpp -std=c++17 -lexiv2 -o bin/renamer
	#g++-9 main.cpp -std=c++17 -o bin/renamer

run:
	./bin/renamer

clean:
	rm bin/renamer
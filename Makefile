all:
	g++-9 main.cpp -std=c++17 -o renamer

run:
	./renamer

clean:
	rm renamer
bin/kalki: bin/ src/kalki.cpp
	g++ src/kalki.cpp -o bin/kalki

bin/:
	mkdir bin
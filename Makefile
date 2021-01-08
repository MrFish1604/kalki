bin/kalki: bin/ src/kalki.cpp
	g++ src/kalki.cpp -o bin/kalki
	@echo "\nYou can find kalki in bin/"

bin/:
	mkdir bin
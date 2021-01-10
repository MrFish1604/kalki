bin/kalki: bin/ src/kalki.cpp
	g++ src/kalki.cpp -o bin/kalki
	@echo "\nYou can find kalki in bin/"

bin/:
	mkdir bin

install: bin/kalki
	cp bin/kalki /usr/bin/kalki
	chown root:root /usr/bin/kalki
	chmod 755 /usr/bin/kalki

uninstall: /usr/bin/kalki
	rm /usr/bin/kalki

update:
	git stash
	git checkout main
	git pull
	make bin/kalki
	sudo make install
	git stash pop
	@echo "\nKalki successfully updated."
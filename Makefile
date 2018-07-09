.phony setup:
fresh: main.cpp
		brew tap nlohmann/json
		brew install nlohmann_json
		curl -OL "https://github.com/bakwc/JamSpell-models/raw/master/en.tar.gz"
		tar xvf en.tar.gz
		g++ -std=c++11 lib/*/*.cpp jamspell/*.cpp contrib/*/*.cc contrib/*/*.cpp main.cpp -lboost_regex -I "./" -o chapter.o

setup: main.cpp
		g++ -std=c++11 lib/*/*.cpp jamspell/*.cpp contrib/*/*.cc contrib/*/*.cpp main.cpp -lboost_regex -I "./" -o chapter.o

run: chapter.o
		./chapter.o

.phony clean:
		rm -rf *.o *.spell

hepsi: derle calistir

derle: 
	g++ -g -I ./include/ -o ./lib/DnaVerileriOku.o -c ./src/DnaVerileriOku.cpp
	g++ -g -I ./include/ -o ./lib/Gen.o -c ./src/Gen.cpp
	g++ -g -I ./include/ -o ./lib/Kromozom.o -c ./src/Kromozom.cpp
	g++ -g -I ./include/ -o ./bin/DnaOdev ./lib/DnaVerileriOku.o ./lib/Gen.o ./lib/Kromozom.o ./src/main.cpp

calistir:
	./bin/DnaOdev




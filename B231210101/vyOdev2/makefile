hepsi: derle calistir

derle: 
	g++ -g -I ./include/ -o ./lib/ListNode.o -c ./src/ListNode.cpp
	g++ -g -I ./include/ -o ./lib/TreeNode.o -c ./src/TreeNode.cpp
	g++ -g -I ./include/ -o ./lib/TreeDrawing.o -c ./src/TreeDrawing.cpp
	g++ -g -I ./include/ -o ./bin/Agaclar ./lib/ListNode.o ./lib/TreeNode.o ./lib/TreeDrawing.o ./src/main.cpp

calistir:
	./bin/Agaclar
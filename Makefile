compile: Othello.cpp Player.hpp randomPlayer.cpp randomPlayer.hpp State.cpp State.hpp
	g++ -c Othello.cpp -o Othello.o
	g++ -c randomPlayer.cpp -o randomPlayer.o
	g++ -c State.cpp -o State.o
	g++ -c Player.cpp -o Player.o
	g++ Othello.o randomPlayer.o State.o Player.o
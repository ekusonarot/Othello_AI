#include <iostream>
#include <unistd.h>//sleep
#include <ctime>//time
#include <cstdlib>//rand

#include "State.hpp"
#include "randomPlayer.hpp"
#include "Player.hpp"


int main()
{
    State state;
    state.init();

    randomPlayer player1,player2;
    player1.setSide(-1);
    player2.setSide(1);
    player1.setState(&state);
    player2.setState(&state);
    while (state.existZero()){
        
        system("cls");

        player1.Action();

        system("cls");

        player2.Action();

        //system("pause");
    }

  
}


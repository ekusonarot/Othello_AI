#include <iostream>
#include <unistd.h>//sleep
#include <ctime>//time
#include <cstdlib>//rand

#include "State.hpp"
#include "randomPlayer.hpp"
#include "Player.hpp"
#include "QPlayer.hpp"
#include "neuralNetwork.hpp"

int main(int argc, char **argv)
{
    State state;

    randomPlayer rPlayer(1,0,&state);  
    randomPlayer rPlayer2(-1,0,&state);   
    while(state.existZero(state.get_S())){
        rPlayer.Action();
        rPlayer2.Action();
    }


    return 0;
}


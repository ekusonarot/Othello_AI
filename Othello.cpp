#include <iostream>
#include <unistd.h>//sleep
#include <ctime>//time
#include <cstdlib>//rand

#include "State.hpp"
#include "randomPlayer.hpp"
#include "Player.hpp"
#include "QPlayer.hpp"


int main()
{
    State state;

    randomPlayer rPlayer(1,0,&state);  
    randomPlayer rPlayer2(-1,0,&state);   
    while(state.existZero(state.get_S())){
        rPlayer.Action();
        rPlayer2.Action();
    }

}


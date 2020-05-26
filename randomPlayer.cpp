#include "randomPlayer.hpp"


void randomPlayer::Action() {
    int Action[64] = {0};
    int r;

    getState()->valid_XY(getSide(),Action);//
    if (Action[0] != -1) {
        r = int_random(Action);

        getState()->Action(Action[r]/8,Action[r]%8,getSide());
    }
    std::cout << Action[0] << std::endl;

    getState()->temp_save();

    if (getMode() == 0) getState()->showState();

}
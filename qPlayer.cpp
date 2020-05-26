#include<iostream>
#include "qPlayer.hpp"


void qPlayer::Action() {
    int Action[64] = {0};

    getState()->valid_XY(getSide(),Action);//
    if (Action[0] != -1) {
        //Qに従って行動を選択

        getState()->Action(Action[0]/8,Action[0]%8,getSide());
    }
    std::cout << Action[0] << std::endl;

    getState()->temp_save();

    if (getMode() == 0) getState()->showState();

}
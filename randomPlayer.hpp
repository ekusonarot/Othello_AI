#ifndef RANDOMPLAYER_HPP
#define RANDOMPLAYER_HPP
#include <iostream>
#include <ctime>//time
#include "Player.hpp"


class randomPlayer : public Player{
    int int_random(int*);
    public:
        using Player::Player;
        virtual void Action();
};


inline int randomPlayer::int_random(int* A) {
    std::srand(time(NULL));
        int i=0;
        while (A[i] != -1) {
            i++;
        }
        return rand()%i;
}

inline void randomPlayer::Action() {
    int Action[64] = {0};
    int r;

    int** S = state->get_S();


    state->valid_XY(side,Action,S);

    system("cls");
    if (Action[0] != -1) {
        r = int_random(Action);

        state->Action(Action[r]/8,Action[r]%8,side,S);
    }

    if (mode == 0) state->showState();

}

#endif // RANDOMPLAYER_HPP
#ifndef QPLAYER_HPP
#define QPLAYER_HPP

#include <iostream>
#include <ctime>
#include "Player.hpp"

class qPlayer : public Player {
int int_random(int*);
    public:
        virtual void Action();
};

inline int qPlayer::int_random(int* A) {
    std::srand(time(NULL));
        int i=0;
        while (A[i] != -1) {
            i++;
        }
        return rand()%i;
}

#endif // QPLAYER_HPP
#ifndef RANDOMPLAYER_HPP
#define RANDOMPLAYER_HPP
#include <iostream>
#include <ctime>//time
#include "Player.hpp"


class randomPlayer : public Player{
    int int_random(int*);
    public:
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

#endif // RANDOMPLAYER_HPP
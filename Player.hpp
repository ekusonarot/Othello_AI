#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "State.hpp"


class Player {
    int side;
    State* state;
    public:
        void setSide(int);
        int getSide();
        void setState(State*);
        State* getState() { return state;}
        virtual void Action(){};
};

inline void Player::setSide(int s) {
    side = s;
}

inline int Player::getSide() {
    return side;
}

inline void Player::setState(State* sp) {
    state = sp;
}

#endif // PLAYER_HPP
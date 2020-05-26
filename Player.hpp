#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "State.hpp"


class Player {
    int side;
    int mode=0;//0: 通常 1:盤面表示なし
    State* state;
    public:
        void setSide(int);
        int getSide();
        void setState(State*);
        State* getState();
        void setMode(int);
        int getMode();
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

inline State* Player::getState() {
    return state;
}

inline void Player::setMode(int m) {
    mode = m;
}

inline int Player::getMode() {
    return mode;
}

#endif // PLAYER_HPP
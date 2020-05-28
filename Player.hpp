#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "State.hpp"

/*

*/
class Player {
    public:
        int side;
        int mode=0;//0: 通常 1:盤面表示なし
        State* state;
        Player(int,int,State*);
        virtual void Action(){};
};

/*
    int side : 1 or -1
    int mode : 0 盤面表示あり　　1 盤面表示なし
    State* state : Stateのアドレス
*/
inline Player::Player(int s, int m, State* sp) {
    side = s;
    mode = m;
    state = sp;
}

#endif // PLAYER_HPP
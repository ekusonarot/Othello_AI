#ifndef QPLAYER_HPP
#define QPLAYER_HPP

#include <iostream>
#include <ctime>
#include "Player.hpp"
#include "State.hpp"
#include "neuralNetwork.hpp"

const double Gamma = 1.5;
const double Alpha = 0.5;

class QPlayer : public Player {
    int selectAction(int,int*,int**);
    int argMaxQ(int,int*,int**);
    double MaxQ(int,int*,int**);
    double reward(int,int**);
    double evalQvalue(int,int,int**);
    double newQvalue();
    NN neuralnet;
    public:
        using Player::Player;
        virtual void Action();
};

void QPlayer::Action() {
    int Action[64]={0};
    int a;
    double this_reward;
    double next_reward;
    double this_Q;
    double next_MaxQ;
    double next_next_MaxQ;

    double A_BLOCK=0;
    double B_BLOCK=0;


    system("cls");
    int** S = state->get_S();                          //S[]を取得
    int** second_S = state->get_second_S();
    state->copy(second_S,S);
    int** third_S = state->get_third_S();
    

    /*############################################## 状態s 行動a ############################################################*/
    state->valid_XY(side,Action,second_S);                    //次の行動a をAction[]に格納　末尾　-1
    if (Action[0] != -1) {
        a = selectAction(side,Action,second_S);               //次の行動a　があるとき　方策によって次の行動を決める
        state->Action(Action[a]/8,Action[a]%8,side,second_S); //行動aを実行
        state->copy(third_S,second_S);

        this_reward = reward(side,second_S);                //報酬r = this_reward 状態s' = second_S

        this_Q = evalQvalue(side,Action[a],S);                     //このターンの報酬
        next_MaxQ = MaxQ(-side,Action,second_S);                   //次のターンは相手だから -side

        /*################################################ 状態s' 行動a' ##########################################################*/
        state->valid_XY(-side,Action,third_S);                 //次の行動a をAction[]に格納　末尾　-1
        if (Action[0] != -1) {
            a = selectAction(-side,Action,third_S);               //次の行動a'　があるとき　方策によって次の行動を決める
            state->Action(Action[a]/8,Action[a]%8,-side,third_S); //状態s' で行動a'を実行

            next_reward = reward(-side,third_S);                //報酬r' = next_reward 状態s' = third_S

            next_next_MaxQ = MaxQ(side,Action,third_S);         //次の次のターンは自分だから side

            B_BLOCK = next_MaxQ + Alpha * (next_reward + -(Gamma * next_next_MaxQ) - next_MaxQ);
        }

    // next_MaxQ = next_MaxQ + Alpha * (next_reward + -(Gamma * next_next_MaxQ) - next_MaxQ)  ←　B_BLOCK
    // Q(s,a) = Q(s,a) + Alpha * (this_reward + -(Gamma * next_MaxQ) - Q(s,a))                ←　A_BLOCK

        A_BLOCK = this_Q + Alpha * (this_reward + -(Gamma * next_MaxQ) - this_Q); 
    }
    // 入力データ s,a 教師データ A_BLOCK で　学習

}

/*
    selectAction(): 方策　状態s での行動aを選択
        一定確率Gammaでランダムに行動
        入力:
            side: 1 or -1
            A: 行動a　配列 末尾-1
            sp: S[] or second_S[] とか
        出力：
            A[0]~A[i] != -1
            の　0~i
*/
inline int QPlayer::selectAction(int side, int* A, int** sp) {
    std::srand(time(NULL));
    if (std::rand()/RAND_MAX < Gamma) {
        int i=0;
        while (A[i] != -1) {
            i++;
        }
        return rand()%i;
    }
    
    int i = argMaxQ(side, A, sp);
    return i;

}

/*
    argMaxQ(): Q値が最大となる行動を返す
        入力:
            side: 1 or -1
            A: 行動a　配列 末尾-1
            sp: S[] or second_S[] とか
        出力：
            A[0]~A[i] != -1
            の　0~i
*/
inline int QPlayer::argMaxQ(int side, int* A, int** sp) {
    double max_Q=-100;
    double Q;
    int i=0,max_i=0;
    while (A[i] != -1) {
        Q = evalQvalue(side, A[i], sp);   //Q値を求める
        if(max_Q < Q) {
            max_Q = Q;
            max_i = i;
        }
        i++;
    }
    return i;
}

/*
    maxQ(): 最大のQ値を返す
        入力:
            side: 1 or -1
            A: 行動a　配列 末尾-1
            sp: S[] or second_S[] とか
        出力：
            最大のQ値
*/
inline double QPlayer::MaxQ(int side, int* A, int** sp) {
    double max_Q=-100;
    double Q;
    int i=0;
    while (A[i] != -1) {
        Q = evalQvalue(side, A[i], sp);   //Q値を求める
        if(max_Q < Q) max_Q = Q;
        i++;
    }
    return max_Q;
}

/*
    報酬rの計算
*/
inline double QPlayer::reward(int side, int** sp) {
    if (state->existZero(sp)) 
        return 1;

    if (32 < state->count(side,sp)) 
        return 10;
    else
        return -10;
}

/*
    Q値の計算
*/
inline double QPlayer::evalQvalue(int side, int action, int** sp) {
    double Q_value;
    int input[128]={0};
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            input[i*8+j] = side * sp[i][j];
        }
    }
    input[action]=1;
    Q_value = neuralnet.eval(input);// NN で　計算
    return Q_value;
}

#endif // QPLAYER_HPP
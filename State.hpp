#ifndef STATE_HPP
#define STATE_HPP

#include <stdlib.h>

class State {
    int** S;
    int** second_S;
    int** third_S;
    bool is_valid_upward(int,int,int,int**);
    bool is_valid_downward(int,int,int,int**);
    bool is_valid_rightward(int,int,int,int**);
    bool is_valid_leftward(int,int,int,int**);
    bool is_valid_topright(int,int,int,int**);
    bool is_valid_lowerright(int,int,int,int**);
    bool is_valid_lowerleft(int,int,int,int**);
    bool is_valid_topleft(int,int,int,int**);
    
    void turn_up(int,int,int,int**);
    void turn_right(int,int,int,int**);
    void turn_down(int,int,int,int**);
    void turn_left(int,int,int,int**);
    void turn_topright(int,int,int,int**);
    void turn_lowright(int,int,int,int**);
    void turn_lowleft(int,int,int,int**);
    void turn_topleft(int,int,int,int**);

    public:
        
        State();
        ~State();
        int is_valid_XY(int,int,int,int**);
        void valid_XY(int,int*,int**);
        void temp_save(int**);
        void Action(int,int,int,int**);
        void showState();
        bool existZero(int**);
        int count(int,int**);
        int** get_S();
        int** get_second_S();
        int** get_third_S();
};

inline State::State() {    
    S = new int*[8];
    second_S = new int*[8];
    third_S = new int*[8];


    for (int i=0; i < 8; i++) {
        S[i] = new int[8];
        second_S[i]= new int[8];
        third_S[i]= new int[8];
    }

    for (int i=0; i < 8; i++) {
        for (int j=0; j < 8; j++) {
            S[i][j] = 0;
            second_S[i][j] = 0;
            third_S[i][j] = 0;
        }
    }
    S[3][3] = 1; S[4][4] = 1;
    second_S[3][3] = 1; second_S[4][4] = 1;
    third_S[3][3] = 1; third_S[4][4] = 1;
    
    S[3][4] = -1; S[4][3] = -1;
    second_S[3][4] = -1; second_S[4][3] = -1;
    third_S[3][4] = -1; third_S[4][3] = -1;

}

inline State::~State() {
    for (int i=0; i < 8; i++) {
        delete [] S[i]; 
        delete [] second_S[i];
        delete [] third_S[i];
    }
    delete [] S;
    delete [] second_S;
    delete [] third_S;
}

/*
    return S;
*/
inline int** State::get_S() {
    return S;
}

/*
    return second_S;
*/
inline int** State::get_second_S() {
    return second_S;
}

/*
    return third_S;
*/
inline int** State::get_third_S() {
    return third_S;
}

/*
    existZero:  状態spにゼロがあるか判定
    入力:
        sp: S[] か temp_S[]の先頭アドレス
    
    出力:
        ゼロがあるとき　true
        ないとき　　　　false
*/
inline bool State::existZero(int** sp)
{
    for (int i=0; i < 8; i++) {
        for (int j=0; j < 8; j++) {
            if (sp[i][j] == 0) return true;
        }
    }
    return false;
}

/*
    countOne:   sp中のcの数を数える。
    入力:
        c:  自分の石　1 or -1
        sp: S[] か　temp_S[] の先頭アドレス
    出力:
        石の数
*/
inline int State::count(int c, int** sp) 
{
    int count=0;
    for (int i=0; i < 8; i++) {
        for (int j=0; j < 8; j++) {
            if (sp[i][j] == c) count++;
        }
    }
    return count;
}

/*
    showState:    S[]を表示
    入力:
        なし

    出力:
        なし
*/
inline void State::showState()
{
    for (int i=0; i < 8; i++) {
        for (int j=0; j < 8; j++) {
            std::cout << S[i][j] << "    " ;
        }
        std::cout << std::endl << std::endl;
    }
}

/*
    temp_save:    状態spをS[]に保存
    入力:
        sp: temp_S[]　の先頭アドレス

    出力:
        なし
*/
inline void State::temp_save(int** sp)
{
    for (int i=0; i < 8; i++) {
        for (int j=0; j < 8; j++) {
            S[i][j] = sp[i][j];
        }
    }
}

inline bool State::is_valid_upward(int x, int y, int c, int** sp)
{
    if (x<=2) return false;
    if (sp[x][y] != 0 || sp[x-1][y] != -c || x < 0 || y < 0 || 7 < x || 7 < y) return false;
    x -= 2;
    while (0 <= x) {
        if (sp[x][y] == c) return true;
        else if(sp[x][y] == 0) return false;
        x--;
    }
    return false;
}

inline bool State::is_valid_downward(int x, int y, int c, int** sp)
{
    if (6<=x) return false;
    if (sp[x][y] != 0 || sp[x+1][y] != -c || x < 0 || y < 0 || 7 < x || 7 < y) return false;
    x += 2;
    while (x < 8) {
        if (sp[x][y] == c) return true;
        else if(sp[x][y] == 0) return false;
        x++;
    }
    return false;
}

inline bool State::is_valid_rightward(int x, int y, int c, int** sp)
{
    if (6<=x) return false;
    if (sp[x][y] != 0 || sp[x][y+1] != -c || x < 0 || y < 0 || 7 < x || 7 < y) return false;
    y += 2;
    while (y < 8) {
        if (sp[x][y] == c) return true;
        else if(sp[x][y] == 0) return false;
        y++;
    }
    return false;
}

inline bool State::is_valid_leftward(int x, int y, int c, int** sp)
{
    if (y<=2) return false;
    if (sp[x][y] != 0 || sp[x][y-1] != -c || x < 0 || y < 0 || 7 < x || 7 < y) return false;
    y -= 2;
    while (0 <= y) {
        if (sp[x][y] == c) return true;
        else if(sp[x][y] == 0) return false;
        y--;
    }
    return false;
}

inline bool State::is_valid_topright(int x, int y, int c, int** sp)
{
    if (x<=2 || 6<=y) return false;
    if (sp[x][y] != 0 || sp[x-1][y+1] != -c || x < 0 || y < 0 || 7 < x || 7 < y) return false;
    y += 2;
    x -= 2;
    while (y < 8 && 0 <= x) {
        if (sp[x][y] == c) return true;
        else if(sp[x][y] == 0) return false;
        x--;
        y++;
    }
    return false;
}

inline bool State::is_valid_lowerright(int x, int y, int c, int** sp)
{
    if (6<=x || 6<=y) return false;
    if (sp[x][y] != 0 || sp[x+1][y+1] != -c || x < 0 || y < 0 || 7 < x || 7 < y) return false;
    y += 2;
    x += 2;
    while (y < 8 && x < 8) {
        if (sp[x][y] == c) return true;
        else if(sp[x][y] == 0) return false;
        x++;
        y++;
    }
    return false;
}

inline bool State::is_valid_lowerleft(int x, int y, int c, int** sp)
{
    if (6<=x || y<=2) return false;
    if (sp[x][y] != 0 || sp[x+1][y-1] != -c || x < 0 || y < 0 || 7 < x || 7 < y) return false;
    y -= 2;
    x += 2;
    while (0 <= y && x < 8) {
        if (sp[x][y] == c) return true;
        else if(sp[x][y] == 0) return false;
        x++;
        y--;
    }
    return false;
}

inline bool State::is_valid_topleft(int x, int y, int c, int** sp)
{
    if (x<=2 || y<=2) return false;
    if (sp[x][y] != 0 || sp[x-1][y-1] != -c || x < 0 || y < 0 || 7 < x || 7 < y) return false;
    y -= 2;
    x -= 2;
    while (0 <= y && 0 <= x) {
        if (sp[x][y] == c) return true;
        else if(sp[x][y] == 0) return false;
        x--;
        y--;
    }
    return false;
}

/*
    is_valid_XY:    (x, y)に打てるかどうか判定する。
    入力:
        x:  x座標
        y:  y座標
        c:  打つ石  -1 or 1
        sp: S[] か temp_S[]　の先頭アドレス

    出力:
        打てるなら 0以上
*/
inline int State::is_valid_XY(int x, int y, int c, int** sp)
{
    int retval=0;
    if (is_valid_upward(x,y,c,sp)) retval += 1;
    if (is_valid_rightward(x,y,c,sp)) retval += 2;
    if (is_valid_downward(x,y,c,sp)) retval += 4;
    if (is_valid_leftward(x,y,c,sp)) retval += 8;
    if (is_valid_topright(x,y,c,sp)) retval += 16;
    if (is_valid_lowerright(x,y,c,sp)) retval += 32;
    if (is_valid_lowerleft(x,y,c,sp)) retval += 64;
    if (is_valid_topleft(x,y,c,sp)) retval += 128;
    return retval;
}

/*
    valid_XY:    次に打てる行動 (x, y) を探索
    入力:
        c:  打つ石  -1 or 1
        V:  次の行動を保存する配列の先頭アドレス
        sp: S[] か temp_S[]　の先頭アドレス

    出力:
        なし
*/
inline void State::valid_XY(int c, int* V, int** sp)
{
    for (int i=0; i < 8; i++) {
        for (int j=0; j < 8; j++) {
            if (State::is_valid_XY(i,j,c,sp) != 0) *V++ = i*8+j;
        }
    }
    *V++ = -1;
}

inline void State::turn_up(int x,int y,int c, int** sp)
{
    do {
        sp[x][y] = c;
        x--;
    }while (sp[x][y] != c);
}

inline void State::turn_right(int x,int y,int c, int** sp)
{
    do {
        sp[x][y] = c;
        y++;
    }while (sp[x][y] != c);
}

inline void State::turn_down(int x,int y,int c, int** sp)
{
    do {
        sp[x][y] = c;
        x++;
    }while (sp[x][y] != c);
}

inline void State::turn_left(int x,int y,int c, int** sp)
{
    do {
        sp[x][y] = c;
        y--;
    }while (sp[x][y] != c);
}

inline void State::turn_topright(int x,int y,int c, int** sp)
{
    do {
        sp[x][y] = c;
        x--;
        y++;
    }while (sp[x][y] != c);
}

inline void State::turn_lowright(int x,int y,int c, int** sp)
{
    do {
        sp[x][y] = c;
        x++;
        y++;
    }while (sp[x][y] != c);
}

inline void State::turn_lowleft(int x,int y,int c, int** sp)
{
    do {
        sp[x][y] = c;
        x++;
        y--;
    }while (sp[x][y] != c);
}

inline void State::turn_topleft(int x,int y,int c, int** sp)
{
    do {
        sp[x][y] = c;
        x--;
        y--;
    }while (sp[x][y] != c);
}

/*
    Action:    (x, y)にcを打つ。
    入力:
        x:  x座標
        y:  y座標
        c:  打つ石  -1 or 1
        sp: S[] か temp_S[]　の先頭アドレス

    出力:
        なし
*/
inline void State::Action(int x, int y, int c, int** sp)
{
    int is_valid_XY = State::is_valid_XY(x,y,c,sp);
    if (is_valid_XY % 2) turn_up(x,y,c,sp);
    is_valid_XY /= 2;
    if (is_valid_XY % 2) turn_right(x,y,c,sp);
    is_valid_XY /= 2;
    if (is_valid_XY % 2) turn_down(x,y,c,sp);
    is_valid_XY /= 2;
    if (is_valid_XY % 2) turn_left(x,y,c,sp);
    is_valid_XY /= 2;
    if (is_valid_XY % 2) turn_topright(x,y,c,sp);
    is_valid_XY /= 2;
    if (is_valid_XY % 2) turn_lowright(x,y,c,sp);
    is_valid_XY /= 2;
    if (is_valid_XY % 2) turn_lowleft(x,y,c,sp);
    is_valid_XY /= 2;
    if (is_valid_XY % 2) turn_topleft(x,y,c,sp);
}


#endif // STATE_HPP
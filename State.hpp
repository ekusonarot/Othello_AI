#ifndef STATE_HPP
#define STATE_HPP

class State {
    int S[8][8] = {
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,1,-1,0,0,0},
        {0,0,0,-1,1,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0}
    };
    bool is_valid_upward(int,int,int);
    bool is_valid_downward(int,int,int);
    bool is_valid_rightward(int,int,int);
    bool is_valid_leftward(int,int,int);
    bool is_valid_topright(int,int,int);
    bool is_valid_lowerright(int,int,int);
    bool is_valid_lowerleft(int,int,int);
    bool is_valid_topleft(int,int,int);
    
    void turn_up(int,int,int);
    void turn_right(int,int,int);
    void turn_down(int,int,int);
    void turn_left(int,int,int);
    void turn_topright(int,int,int);
    void turn_lowright(int,int,int);
    void turn_lowleft(int,int,int);
    void turn_topleft(int,int,int);

    public:
        int temp_S[8][8];
        int is_valid_XY(int,int,int);
        void valid_XY(int,int*);
        void temp_save();
        void init();
        void Action(int,int,int);
        void showState();
        bool existZero();
};

#endif // STATE_HPP
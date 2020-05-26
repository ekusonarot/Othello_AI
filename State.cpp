#include "State.hpp"
#include <iostream>


bool State::existZero()
{
    for (int i=0; i < 8; i++) {
        for (int j=0; j < 8; j++) {
            if (S[i][j] == 0) return true;
        }
    }
    return false;
}

void State::showState()
{
    for (int i=0; i < 8; i++) {
        for (int j=0; j < 8; j++) {
            std::cout << S[i][j] << "    " ;
        }
        std::cout << std::endl << std::endl;
    }
}

void State::temp_save()
{
    for (int i=0; i < 8; i++) {
        for (int j=0; j < 8; j++) {
            S[i][j] = temp_S[i][j];
        }
    }
}

void State::init()
{
    for (int i=0; i < 8; i++) {
        for (int j=0; j < 8; j++) {
            temp_S[i][j] = S[i][j];
        }
    }
}

bool State::is_valid_upward(int x, int y, int c)
{
    if (State::S[x][y] != 0 || State::S[x-1][y] != -c || x < 0 || y < 0 || 7 < x || 7 < y) return false;
    x -= 2;
    while (0 <= x) {
        if (State::S[x][y] == c) return true;
        else if(State::S[x][y] == 0) return false;
        x--;
    }
    return false;
}

bool State::is_valid_downward(int x, int y, int c)
{     
    if (State::S[x][y] != 0 || State::S[x+1][y] != -c || x < 0 || y < 0 || 7 < x || 7 < y) return false;
    x += 2;
    while (x < 8) {
        if (State::S[x][y] == c) return true;
        else if(State::S[x][y] == 0) return false;
        x++;
    }
    return false;
}

bool State::is_valid_rightward(int x, int y, int c)
{
    if (State::S[x][y] != 0 || State::S[x][y+1] != -c || x < 0 || y < 0 || 7 < x || 7 < y) return false;
    y += 2;
    while (y < 8) {
        if (State::S[x][y] == c) return true;
        else if(State::S[x][y] == 0) return false;
        y++;
    }
    return false;
}

bool State::is_valid_leftward(int x, int y, int c)
{
    if (State::S[x][y] != 0 || State::S[x][y-1] != -c || x < 0 || y < 0 || 7 < x || 7 < y) return false;
    y -= 2;
    while (0 <= y) {
        if (State::S[x][y] == c) return true;
        else if(State::S[x][y] == 0) return false;
        y--;
    }
    return false;
}

bool State::is_valid_topright(int x, int y, int c)
{
    if (State::S[x][y] != 0 || State::S[x-1][y+1] != -c || x < 0 || y < 0 || 7 < x || 7 < y) return false;
    y += 2;
    x -= 2;
    while (y < 8 && 0 <= x) {
        if (State::S[x][y] == c) return true;
        else if(State::S[x][y] == 0) return false;
        x--;
        y++;
    }
    return false;
}

bool State::is_valid_lowerright(int x, int y, int c)
{
    if (State::S[x][y] != 0 || State::S[x+1][y+1] != -c || x < 0 || y < 0 || 7 < x || 7 < y) return false;
    y += 2;
    x += 2;
    while (y < 8 && x < 8) {
        if (State::S[x][y] == c) return true;
        else if(State::S[x][y] == 0) return false;
        x++;
        y++;
    }
    return false;
}

bool State::is_valid_lowerleft(int x, int y, int c)
{
    if (State::S[x][y] != 0 || State::S[x+1][y-1] != -c || x < 0 || y < 0 || 7 < x || 7 < y) return false;
    y -= 2;
    x += 2;
    while (0 <= y && x < 8) {
        if (State::S[x][y] == c) return true;
        else if(State::S[x][y] == 0) return false;
        x++;
        y--;
    }
    return false;
}

bool State::is_valid_topleft(int x, int y, int c)
{
    if (State::S[x][y] != 0 || State::S[x-1][y-1] != -c || x < 0 || y < 0 || 7 < x || 7 < y) return false;
    y -= 2;
    x -= 2;
    while (0 <= y && 0 <= x) {
        if (State::S[x][y] == c) return true;
        else if(State::S[x][y] == 0) return false;
        x--;
        y--;
    }
    return false;
}

int State::is_valid_XY(int x, int y, int c)
{
    int retval=0;
    if (is_valid_upward(x,y,c)) retval += 1;
    if (is_valid_rightward(x,y,c)) retval += 2;
    if (is_valid_downward(x,y,c)) retval += 4;
    if (is_valid_leftward(x,y,c)) retval += 8;
    if (is_valid_topright(x,y,c)) retval += 16;
    if (is_valid_lowerright(x,y,c)) retval += 32;
    if (is_valid_lowerleft(x,y,c)) retval += 64;
    if (is_valid_topleft(x,y,c)) retval += 128;
    return retval;
}

void State::valid_XY(int c, int* V)
{
    for (int i=0; i < 8; i++) {
        for (int j=0; j < 8; j++) {
            if (State::is_valid_XY(i,j,c) != 0) *V++ = i*8+j;
        }
    }
    *V++ = -1;
}

void State::turn_up(int x,int y,int c)
{
    do {
        State::temp_S[x][y] = c;
        x--;
    }while (State::temp_S[x][y] != c);
}

void State::turn_right(int x,int y,int c)
{
    do {
        State::temp_S[x][y] = c;
        y++;
    }while (State::temp_S[x][y] != c);
}

void State::turn_down(int x,int y,int c)
{
    do {
        State::temp_S[x][y] = c;
        x++;
    }while (State::temp_S[x][y] != c);
}

void State::turn_left(int x,int y,int c)
{
    do {
        State::temp_S[x][y] = c;
        y--;
    }while (State::temp_S[x][y] != c);
}

void State::turn_topright(int x,int y,int c)
{
    do {
        State::temp_S[x][y] = c;
        x--;
        y++;
    }while (State::temp_S[x][y] != c);
}

void State::turn_lowright(int x,int y,int c)
{
    do {
        State::temp_S[x][y] = c;
        x++;
        y++;
    }while (State::temp_S[x][y] != c);
}

void State::turn_lowleft(int x,int y,int c)
{
    do {
        State::temp_S[x][y] = c;
        x++;
        y--;
    }while (State::temp_S[x][y] != c);
}

void State::turn_topleft(int x,int y,int c)
{
    do {
        State::temp_S[x][y] = c;
        x--;
        y--;
    }while (State::temp_S[x][y] != c);
}

void State::Action(int x, int y, int c)
{
    int is_valid_XY = State::is_valid_XY(x,y,c);
    if (is_valid_XY % 2) turn_up(x,y,c);
    
    is_valid_XY /= 2;
    if (is_valid_XY % 2) turn_right(x,y,c);
    is_valid_XY /= 2;
    if (is_valid_XY % 2) turn_down(x,y,c);
    is_valid_XY /= 2;
    if (is_valid_XY % 2) turn_left(x,y,c);
    is_valid_XY /= 2;
    if (is_valid_XY % 2) turn_topright(x,y,c);
    is_valid_XY /= 2;
    if (is_valid_XY % 2) turn_lowright(x,y,c);
    is_valid_XY /= 2;
    if (is_valid_XY % 2) turn_lowleft(x,y,c);
    is_valid_XY /= 2;
    if (is_valid_XY % 2) turn_topleft(x,y,c);
}

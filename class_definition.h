#ifndef CLASS_DEFINITION_H_INCLUDED
#define CLASS_DEFINITION_H_INCLUDED

#include<vector>
#include<iostream>
#include<windows.h>
#include<cstdlib>
#include<ctime>
#include<conio.h>

//prototypes
int instruction();

class point
{
    int x,y;//x is the actual x divides 2
    static constexpr char *sna="¡ö";
    static constexpr char *wal="¡õ";
    static constexpr char *int1="|";
    static constexpr char *int2="¡ª";
    static constexpr char *foo="¡î";
    int e;//the status of the point, the snake body, the wall, or the food, etc
public:
    enum{sn=0,wa,in1,in2,fo=4};
    point(int m=-1,int n=-1,int l=-1){x=m;y=n;e=l;}
    int Get_x(){return x;}
    int Get_y(){return y;}
    int Get_e(){return e;}
    bool operator==(const point &t) const{if(x==t.x&&y==t.y) return true;else return false;}
    void show_point() const;
};

class printable//set the snake(s) before map_elements
{
    int m;//mode
    //the snake
    int toward1;
    int length1;
    std::vector<point> body1;
    int toward2;
    int length2;
    std::vector<point> body2;
    //other map elements
    int grade1=0,grade2=0;
    std::vector<point> wall;
    std::vector<point> interval;
    point food1,food2;
public:
    enum{up=0,down,left,right=3};//snake toward
    enum{s_easy=4,s_hard,s_evil1,s_evil2,s_evil3=8};//s means single, d means double players
    enum{d_easy=9,d_hard,d_evil1,d_evil2,d_evil3=13};//easy means no walls or barriers, hard means with walls, evil means with both
    printable(int mode);
    void rand_food();
    bool in(int x,int y,std::vector<point> &t);//to judge if point (x,y) is in t, return true if it is
    int snake_move(int to1=-1,int to2=-1);//return 1 if snake doesn't touch wall or itself, 0 if does
    void show_all();//including grades
};

#endif // CLASS_DEFINITION_H_INCLUDED

#include"class_definition.h"

extern HANDLE hout;
extern COORD pos;

int speed=2;//refresh frequency = 1000(ms)/speed

void point::show_point() const
{
    pos.X=2*x;
    pos.Y=y;
    SetConsoleCursorPosition(hout,pos);
    char ch[3];
    if(e==sn) strcpy(ch,sna);
    else if(e==wa) strcpy(ch,wal);
    else if(e==in1) strcpy(ch,int1);
    else if(e==in2) strcpy(ch,int2);
    else if(e==fo) strcpy(ch,foo);
    std::cout<<ch;
}

printable::printable(int mode)
{
    m=mode;
    //snake body initialization
    if(m>=4&&m<=8){
        toward1=left;
        length1=4;
        body1={{9,12,point::sn},{10,12,point::sn},{11,12,point::sn},{12,12,point::sn}};
        grade1=0;
        toward2=-1;
        length2=0;
        body2={};
        grade2=0;
    }
    else if(m>=9&&m<=13){
        toward1=left;
        length1=4;
        body1={{9,12,point::sn},{10,12,point::sn},{11,12,point::sn},{12,12,point::sn}};
        grade1=0;
        toward2=right;
        length2=4;
        body2={{21,12,point::sn},{20,12,point::sn},{19,12,point::sn},{18,12,point::sn}};
        grade2=0;
    }
    //wall initialization
    if(m==s_easy||m==d_easy) {wall={};}
    else if(m==s_hard||m==d_hard){//surrounding walls
        for(int i=0;i<31;i++) wall.push_back({i,0,point::wa});
        for(int i=0;i<31;i++) wall.push_back({i,26,point::wa});
        for(int i=1;i<26;i++) wall.push_back({0,i,point::wa});
        for(int i=1;i<26;i++) wall.push_back({30,i,point::wa});
    }
    else if(m==s_evil1||m==d_evil1){
        //surrounding walls
        for(int i=0;i<31;i++) wall.push_back({i,0,point::wa});
        for(int i=0;i<31;i++) wall.push_back({i,26,point::wa});
        for(int i=1;i<26;i++) wall.push_back({0,i,point::wa});
        for(int i=1;i<26;i++) wall.push_back({30,i,point::wa});
        //barriers
        for(int i=9;i<13;i++) wall.push_back({i,7,point::wa});
        for(int i=16;i<20;i++) wall.push_back({i,7,point::wa});
        for(int i=9;i<13;i++) wall.push_back({i,17,point::wa});
        for(int i=16;i<20;i++) wall.push_back({i,17,point::wa});
        for(int i=8;i<11;i++) wall.push_back({9,i,point::wa});
        for(int i=14;i<17;i++) wall.push_back({9,i,point::wa});
        for(int i=8;i<11;i++) wall.push_back({19,i,point::wa});
        for(int i=14;i<17;i++) wall.push_back({19,i,point::wa});
    }
    else if(m==s_evil2||m==d_evil2){
        //surrounding walls
        for(int i=0;i<31;i++) wall.push_back({i,0,point::wa});
        for(int i=0;i<31;i++) wall.push_back({i,26,point::wa});
        for(int i=1;i<26;i++) wall.push_back({0,i,point::wa});
        for(int i=1;i<26;i++) wall.push_back({30,i,point::wa});
        //barriers
        std::vector<point> t{{9,7,point::wa},{10,8,point::wa},{11,9,point::wa},{12,10,point::wa},{18,7,point::wa},{17,8,point::wa},{16,9,point::wa},{15,10,point::wa},{15,13,point::wa},{16,14,point::wa},{17,15,point::wa},{18,16,point::wa},{12,13,point::wa},{11,14,point::wa},{10,15,point::wa},{9,16,point::wa}};
        wall.insert(wall.end(),t.begin(),t.end());
    }
    else if(m==s_evil3||m==d_evil3){//no surrounding walls, it's a yin-yang map
        //barriers
        for(int i=0;i<15;i++) wall.push_back({i,6,point::wa});
        for(int i=14;i<29;i++) wall.push_back({i,18,point::wa});
        for(int i=7;i<18;i++) wall.push_back({14,i,point::wa});
    }
    //intervals
    for(int i=0;i<27;i++) interval.push_back({31,i,point::in1});
    for(int i=0;i<31;i++) interval.push_back({i,27,point::in2});
    //food
    rand_food();
}

void printable::rand_food()
{
    int t=30*26-body1.size()-body2.size()-wall.size();
    double K=1.0*rand()/RAND_MAX*(t-1);
    int k=int(K);
    int x=k%30,y=k/30;
    if(m>=4&&m<=8){
        while(in(x,y,body1)||in(x,y,wall)){
            x++;
            if(x==30) {x=0;y++;}
        }
        food1={x,y,point::fo};
    }
    else if(m>=9&&m<=13){
        while(in(x,y,body1)||in(x,y,body2)||in(x,y,wall)){
            x++;
            if(x==30) {x=0;y++;}
        }
        food1={x,y,point::fo};
        t=30*26-body1.size()-body2.size()-wall.size()-1;
        K=1.0*rand()/RAND_MAX*(t-1);
        k=int(K);
        int mm=k%30,n=k/30;
        while(in(x,y,body1)||in(x,y,body2)||in(x,y,wall)||(mm==x&&n==y)){
            mm++;
            if(mm==30) {mm=0;n++;}
        }
        food2={mm,n,point::fo};
    }
}

bool printable::in(int x,int y,std::vector<point> &t)
{
    for(int i=0;i<t.size();i++)
        if(t[i].Get_x()==x&&t[i].Get_y()==y) return true;
    return false;
}

int printable::snake_move(int to1,int to2)
{
    if(m>=4&&m<=8){
        //update toward
        if((toward1==left||toward1==right)&&(to1==up||to1==down)) toward1=to1;
        else if((toward1==up||toward1==down)&&(to1==left||to1==right)) toward1=to1;
        //next status
        int x,y;
        if(toward1==up) {x=body1[0].Get_x(); y=body1[0].Get_y()-1;}
        else if(toward1==down) {x=body1[0].Get_x(); y=body1[0].Get_y()+1;}
        else if(toward1==left) {x=body1[0].Get_x()-1; y=body1[0].Get_y();}
        else if(toward1==right) {x=body1[0].Get_x()+1; y=body1[0].Get_y();}
        if(x==31) x=0; else if(x==-1) x=30; if(y==-1) y=26; else if(y==27) y=0;
        point t{x,y,point::sn};
        body1.insert(body1.begin(),t);
        //test, eat food
        if(food1==body1[0]){
            length1++;
            if(30*26==length1+wall.size()) return 100;
            rand_food();
            if(length1<=8) grade1+=10;
            else if(length1<=12) grade1+=20;
            else if(length1<=16) grade1+=30;
            else grade1+=40;
            switch(length1){case 9: case 13: case 17: speed++;break;}
        }
        else body1.pop_back();
        //test, into wall or body
        std::vector<point> only_body1;
        only_body1.insert(only_body1.end(),body1.begin()+1,body1.end());
        if(in(body1[0].Get_x(),body1[0].Get_y(),wall)||in(body1[0].Get_x(),body1[0].Get_y(),only_body1)) {body1={};length1=0;return 0;}
        else return 1;
    }
    else if(m>=9&&m<=13){
        //update toward
        if((toward1==left||toward1==right)&&(to1==up||to1==down)) toward1=to1;
        else if((toward1==up||toward1==down)&&(to1==left||to1==right)) toward1=to1;
        if((toward2==left||toward2==right)&&(to2==up||to2==down)) toward2=to2;
        else if((toward2==up||toward2==down)&&(to2==left||to2==right)) toward2=to2;
        //next status
        int x,y;
        if(toward1==up) {x=body1[0].Get_x(); y=body1[0].Get_y()-1;}
        else if(toward1==down) {x=body1[0].Get_x(); y=body1[0].Get_y()+1;}
        else if(toward1==left) {x=body1[0].Get_x()-1; y=body1[0].Get_y();}
        else if(toward1==right) {x=body1[0].Get_x()+1; y=body1[0].Get_y();}
        if(x==31) x=0; else if(x==-1) x=30; if(y==-1) y=26; else if(y==27) y=0;
        point t{x,y,point::sn};
        body1.insert(body1.begin(),t);

        if(toward2==up) {x=body2[0].Get_x(); y=body2[0].Get_y()-1;}
        else if(toward2==down) {x=body2[0].Get_x(); y=body2[0].Get_y()+1;}
        else if(toward2==left) {x=body2[0].Get_x()-1; y=body2[0].Get_y();}
        else if(toward2==right) {x=body2[0].Get_x()+1; y=body2[0].Get_y();}
        if(x==31) x=0; else if(x==-1) x=30; if(y==-1) y=26; else if(y==27) y=0;
        t={x,y,point::sn};
        body2.insert(body2.begin(),t);
        //test, eat food
        if(food1==body1[0]||food2==body1[0]){
            length1++;
            if(30*26==length1+length2+wall.size()) return 100;
            rand_food();
            if(length1<=8) grade1+=10;
            else if(length1<=12) grade1+=20;
            else if(length1<=16) grade1+=30;
            else grade1+=40;
        }
        else body1.pop_back();

        if(food1==body2[0]||food2==body2[0]){
            length2++;
            if(30*26==length1+length2+wall.size()) return 100;
            rand_food();
            if(length2<=8) grade2+=10;
            else if(length2<=12) grade2+=20;
            else if(length2<=16) grade2+=30;
            else grade2+=40;
            switch(length1+length2){case 9: case 13: case 17: speed++;break;}
        }
        else body2.pop_back();
        //test, into wall or body
        std::vector<point> only_body1,only_body2;
        int a,b;
        only_body1.insert(only_body1.end(),body1.begin()+1,body1.end());
        only_body2.insert(only_body2.end(),body2.begin()+1,body2.end());
        if(in(body1[0].Get_x(),body1[0].Get_y(),wall)||in(body1[0].Get_x(),body1[0].Get_y(),only_body1)) {body1={};length1=0;a=0;}
        else a=1;
        if(in(body2[0].Get_x(),body2[0].Get_y(),wall)||in(body2[0].Get_x(),body2[0].Get_y(),only_body2)) {body2={};length2=0;b=10;}
        else b=20;
        return a+b;
    }
}

void printable::show_all()
{
    for(int i=0;i<body1.size();i++) body1[i].show_point();
    for(int i=0;i<body2.size();i++) body2[i].show_point();
    for(int i=0;i<wall.size();i++) wall[i].show_point();
    food1.show_point();
    if(m>=9&&m<=13) food2.show_point();
    for(int i=0;i<interval.size();i++) interval[i].show_point();
    pos.X=2*36;
    pos.Y=13;
    SetConsoleCursorPosition(hout,pos);
    std::cout<<"P1得分："<<grade1;
    pos.X=2*36;
    pos.Y=15;
    SetConsoleCursorPosition(hout,pos);
    std::cout<<"P2得分："<<grade2;

    /*pos.X=0;
    pos.Y=28;
    SetConsoleCursorPosition(hout,pos);
    for(int i=0;i<body1.size();i++) {std::cout<<'('<<body1[i].Get_x()<<','<<body1[i].Get_y()<<')'<<' ';}
    system("pause");*/
}

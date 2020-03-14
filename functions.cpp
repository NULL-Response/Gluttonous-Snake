#include"class_definition.h"

extern HANDLE hout;
extern COORD pos;
extern int speed;

int instruction()
{
    using namespace std;
    int a,b;
    pos.X=20;
    pos.Y=13;
    SetConsoleCursorPosition(hout,pos);
    cout<<"贪吃蛇：v1.1";
    pos.X=18;
    pos.Y=13;
    SetConsoleCursorPosition(hout,pos);
    cout<<"选择单双人，单人按1，双人按2：";
    cin>>a;
    pos.X=18;
    pos.Y=13;
    SetConsoleCursorPosition(hout,pos);
    cout<<"选择模式，简单（1）、困难（2）、地图1（3）、地图2（4）、地图3（5）：";
    cin>>b;
    system("cls");
    if(a==1&&b==1) return printable::s_easy;
    else if(a==1&&b==2) return printable::s_hard;
    else if(a==1&&b==3) return printable::s_evil1;
    else if(a==1&&b==4) return printable::s_evil2;
    else if(a==1&&b==5) return printable::s_evil3;
    else if(a==2&&b==1) return printable::d_easy;
    else if(a==2&&b==2) return printable::d_hard;
    else if(a==2&&b==3) return printable::d_evil1;
    else if(a==2&&b==4) return printable::d_evil2;
    else if(a==2&&b==5) return printable::d_evil3;
}

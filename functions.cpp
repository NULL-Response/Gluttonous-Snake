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
    cout<<"̰���ߣ�v1.1";
    pos.X=18;
    pos.Y=13;
    SetConsoleCursorPosition(hout,pos);
    cout<<"ѡ��˫�ˣ����˰�1��˫�˰�2��";
    cin>>a;
    pos.X=18;
    pos.Y=13;
    SetConsoleCursorPosition(hout,pos);
    cout<<"ѡ��ģʽ���򵥣�1�������ѣ�2������ͼ1��3������ͼ2��4������ͼ3��5����";
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

#include"class_definition.h"

using namespace std;

HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
COORD pos;

extern int speed;
//SetConsoleCursorPosition(hout,pos);
//system("cls");

//30*26

int main()
{
    srand(time(NULL));
    int mode=instruction();
    printable m(mode);
    pos.X=18;
    pos.Y=13;
    SetConsoleCursorPosition(hout,pos);
    std::cout<<"游戏将在3s后开始！";
    Sleep(2500);
    while(1){
        system("cls");
        m.show_all();
        int judge,p1=-1,p2=-1;
        DWORD k=GetTickCount();
        if(mode>=printable::s_easy&&mode<=printable::s_evil3){
            while(GetTickCount()-k<1000/speed){
                if(_kbhit())
                    switch(getch()){
                        case 119: p1= printable::up; break;
                        case 97: p1= printable::left; break;
                        case 115: p1= printable::down; break;
                        case 100: p1= printable::right; break;
                    }
            }
            judge=m.snake_move(p1);
            if(judge==100){
                pos.X=18;
                pos.Y=13;
                SetConsoleCursorPosition(hout,pos);
                std::cout<<"恭喜！获胜了！";
                break;
            }
            else if(judge==0){
                pos.X=18;
                pos.Y=13;
                SetConsoleCursorPosition(hout,pos);
                std::cout<<"游戏结束，";
                system("pause");
                break;
            }
        }
            else if(mode>=printable::d_easy&&mode<=printable::d_evil3){
                    while(GetTickCount()-k<1000/speed){
                        if(_kbhit())
                            switch(_getch()){
                                case 119: p1= printable::up; break;
                                case 97: p1= printable::left; break;
                                case 115: p1= printable::down; break;
                                case 100: p1= printable::right; break;
                                case 72: p2= printable::up; break;
                                case 75: p2= printable::left; break;
                                case 80: p2= printable::down; break;
                                case 77: p2= printable::right; break;
                            }
                    }
            judge=m.snake_move(p1,p2);
            if(judge==100){
                pos.X=18;
                pos.Y=13;
                SetConsoleCursorPosition(hout,pos);
                std::cout<<"恭喜！获胜了！";
                break;
            }
            else if(judge!=21){
                pos.X=18;
                pos.Y=13;
                SetConsoleCursorPosition(hout,pos);
                std::cout<<"游戏结束，";
                system("pause");
                break;
            }
        }
    }
    return 0;
}

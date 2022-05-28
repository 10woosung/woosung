#include<iostream>
#include<windows.h>
#include<string>
#include <stdlib.h>

using namespace std;

struct node
{
    int y, x;
};
//이 코드는 지렁이의 좌표역할을 한다.


node snake[20] = { {3,3} };
int tail = 1;
void add(node xy) {
    snake[tail] = xy;
    tail++;
}
char dir = 'R'; // 'U', 'D', 'L', 'R'
int cnt = 0;

int appleY, appleX;//사과의 좌표변수 이다

char MAP[20][21] = {
   "####################"  ,
   "#                  #"  ,
   "#                  #"  ,
   "#                  #"  ,
   "#                  #"  ,
   "#                  #"  ,
   "#                  #"  ,
   "#                  #"  ,
   "#                  #"  ,
   "#                  #"  ,
   "#                  #"  ,
   "#                  #"  ,
   "#                  #"  ,
   "#                  #"  ,
   "#                  #"  ,
   "#                  #"  ,
   "#                  #"  ,
   "#                  #"  ,
   "#                  #"  ,
   "####################"  ,
};
//기본으로 출력되는 맵 역할을 한다.


void printMap() { // MAP을 출력하는 기능 
    system("cls");
    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 20; x++) {
            printf("%c", MAP[y][x]);
        }
        cout << "\n";
    }
}

void eventcheck() { //지렁이의 이동방향을 바꾸는 기능
    if (GetAsyncKeyState(VK_UP)) {
        dir = 'U';
    }
    if (GetAsyncKeyState(VK_DOWN)) {
        dir = 'D';

    }
    if (GetAsyncKeyState(VK_LEFT)) {
        dir = 'L';

    }
    if (GetAsyncKeyState(VK_RIGHT)) {
        dir = 'R';
    }
}
void move() { // 지렁이를 이동방향대로 이동시키는 기능
    if (dir == 'R') {
        snake[0].x++;

    }
    if (dir == 'L') {
        snake[0].x--;

    }
    if (dir == 'U') {
        snake[0].y--;

    }
    if (dir == 'D') {
        snake[0].y++;

    }
}

void appleSetting() { // 사과의 위치를 랜덤으로 변경시키는 기능
    appleY = rand() % 18 + 1; // 0~17   -> 1 ~ 18
    appleX = rand() % 18 + 1;
}
void follow() { // 지렁이의 꼬리가 지렁이를 따라가게 하는 기능
    for (int i = tail - 1; i >= 1; i--) {
        snake[i] = snake[i - 1];
    }
}
int main()
{
    appleSetting();
    while (1) {
        eventcheck();
        follow();
        move();
        if (MAP[snake[0].y][snake[0].x] == '#') { // 지렁이가 맵 끝인 #에 닿았을 떄 게임오버가 되는 기능
            system("cls");
            printf("game over");
            Sleep(1000);
            break;
        }
        for (int i = 1; i <= tail - 1; i++) { //지렁이가 꼬리에 닿았을 떄 게임오버가 되는 기능
            if ((snake[0].x == snake[i].x) && (snake[0].y == snake[i].y))
            {
                system("cls");
                printf("game over");
                Sleep(1000);
                return 0;

            }
        }
        MAP[snake[0].y][snake[0].x] = 'O'; 
        MAP[appleY][appleX] = '@'; 
        for (int i = 1; i <= tail - 1; i++)  { // 지렁이의 꼬리를 생성하는 기능
            MAP[snake[i].y][snake[i].x] = 'o';
        }

        printMap();

        MAP[snake[0].y][snake[0].x] = ' '; // 지렁이의 머리가 있던 자리를 없애주는 기능
        MAP[appleY][appleX] = ' '; //사과가 있던 자리를 없애주는 기능
        for (int i = 0; i <= tail - 1; i++) { // 꼬리가 있던 자리를 없애주는 기능
            MAP[snake[i].y][snake[i].x] = ' ';
        }


        printf("\n먹은 사과수%d개", cnt);
        if (snake[0].x == appleX && appleY == snake[0].y) { //지렁이가 사과를 먹었을 때 속도를 증가시키고 사과를 랜덤좌표로 이동시키는 기능.
            cnt++;
            node temp = { snake[tail - 1].y , snake[tail - 1].x - 1 };
            add(temp);
            appleSetting();
        }

        if (cnt <= 2) {
            Sleep(800);
        }
        else if (cnt <= 5) {
            Sleep(500);
        }
        else {
            Sleep(200);
        }

    }

    return 0;
}





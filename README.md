#include<iostream>
#include<windows.h>
#include<string>
#include <stdlib.h>

using namespace std;

struct node {
    int y, x;
};



node snake[20] = { {3,3} };
int tail = 1;
void add(node xy) {
    snake[tail] = xy;
    tail++;
}
char dir = 'R'; // 'U', 'D', 'L', 'R'
int cnt = 0;

int appleY, appleX;

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



void printMap() { // MAP을 출력하는 기능 
    system("cls");
    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 20; x++) {
            printf("%c", MAP[y][x]);
        }
        cout << "\n";
    }
}

void eventcheck() {
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
void move() {
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

void appleSetting() {
    appleY = rand() % 18 + 1; // 0~17   -> 1 ~ 18
    appleX = rand() % 18 + 1;
}
void follow() {
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
        if (MAP[snake[0].y][snake[0].x] == '#') {
            system("cls");
            printf("game over");
            Sleep(1000);
            break;
        }
        for (int i = 1; i <= tail - 1; i++) {
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
        for (int i = 1; i <= tail - 1; i++) {
            MAP[snake[i].y][snake[i].x] = 'o';
        }

        printMap();

        MAP[snake[0].y][snake[0].x] = ' ';
        MAP[appleY][appleX] = ' ';
        for (int i = 0; i <= tail - 1; i++) {
            MAP[snake[i].y][snake[i].x] = ' ';
        }


        printf("\n먹은 사과수%d개", cnt);
        if (snake[0].x == appleX && appleY == snake[0].y) {
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

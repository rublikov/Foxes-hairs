#include <iostream>
#include <cmath>
#include <stdlib.h>
#include<Windows.h>
#include<vector>
#include <random>
#include <chrono>

struct Carrot {
    int x;
    int y;
    
    void SpawnCarrot() {
        std::cout << "@";
    }
    void NewCords() {
        x = rand() % 100;
        y = rand() % 24;
    }
    void DrawCarrot(std::vector<std::string>& fl) {
        fl[y][x] = '@';
    }
    Carrot(int x, int y) : x(x), y(y){}
    /*bool colision(int a, int b) {
        if ((x != a) || (y != b)) {
            return true;
        }
        return false;
    }*///я не знаю зачем он тут нужен
};
class Creature {
protected:
    int hunger;
    int distant;
    int speed;
    int x, y;
    int ostx = 0;
    int osty = 0;

public:

    bool colision(int a, int b) {
        if ((x == a) && (y == b)) {
            return true;
        }
        return false;
    }
    void movex(int a) {
        if (a != 0) {
            if (a > 0) {
                x++;
            }
            else { x--; }
        }
    }

    void movey(int a) {
        if (a != 0) {
            if (a > 0) {
                y++;
            }
            else { y--; }
        }
    }

    void GoTo(int x_point, int y_point) {
        int delta_x = x_point - x;
        int delta_y = y_point - y;
        int movement;
        if ((abs(delta_x) + abs(delta_y)) < speed) {
             movement = abs(delta_x) + abs(delta_y);
        }
        else {
             movement = speed;
        }
        int eqx, eqy;
        if (delta_x != 0 || delta_y != 0)
        {

            if (delta_y != 0) {
                eqx = abs(delta_x / delta_y);
            }
            else {
                
                while (movement > 0) {

                    movex(delta_x);
                    movement--;
                }
                
                return;
            }
            if (delta_x != 0) {
                eqy = abs(delta_y / delta_x);
            }
            else {
                
                while (movement > 0) {

                    movey(delta_y);
                    movement--;
                }

                return;
            }

            if (eqx > eqy) {
                while (movement > 0) {
                    if (eqx - ostx > 0) {
                        movex(delta_x);
                        ostx++;
                    }
                    else {
                        ostx = 0;
                        movey(delta_y);
                    }
                    movement--;
                }
            }
            else {
                while (movement > 0) {
                    if (eqy - osty > 0) {
                        movey(delta_y);
                        osty++;
                    }
                    else {
                        osty = 0;
                        movex(delta_x);
                    }
                    movement--;
                }
            }
            
            


        }
    }
    void DrawCreature(std::vector<std::string>& fl, int a, int b) {

        fl[y][x] = '-';
        GoTo(a, b);
        fl[y][x] = '*';
    }
    
    Creature() {}
    Creature(int x, int y, int sp):x(x), y(y), speed(sp),hunger(5),distant(15) {}
    void ScanAndDrow(std::vector<std::string>& fl, std::vector<Carrot>& fd) {
        srand(time(NULL));
        int min = 1000;
        
        int n=-1;
        //scans to find closest
        for (int i = 0; i < fd.size(); i++) {
            if( ((abs(x - fd[i].x) + abs(y - fd[i].y) < 1000))&&(min> (abs(x - fd[i].x)) + abs(y - fd[i].y))) {
                n = i;
                min = abs(x - fd[0].x)+ abs(y - fd[i].y);
            }
        }
        if (n == -1) {
            DrawCreature(fl, rand() % 99, rand() % 24);
        }
        else {
            DrawCreature(fl, fd[n].x, fd[n].y);
        }

    }
    
        
};
class Rabbit :public Creature {

public:
    //Rabbit():Creature() {}
    Rabbit(int x, int y, int sp):Creature(x, y, sp) {
        
    }
    void eat() {}

};


int main()
{   
    srand(time(NULL));
    
    
    std::vector<Carrot> foods;
    for (int i = 0; i < 3; i++) {
        foods.push_back(Carrot(rand() % 100, rand()%24));
    }
    std::vector<Rabbit> rabbits;
    for (int i = 0; i < 3; i++) {
        rabbits.push_back(Rabbit(10 * i, 20, i+1));
    }
    std::vector <std::string> field;
    for (int i = 0; i < 25; i++) {
        field.push_back("----------------------------------------------------------------------------------------------------");
    }
    for (int l = 0; l < 150; l++) {
        for (int i = 0; i < 3; i++) {
            foods[i].DrawCarrot(field);
        }
        for (int j = 0; j < rabbits.size(); j++) {
            for (int i = 0; i < foods.size(); i++) {
                if (rabbits[j].colision(foods[i].x, foods[i].y)) {
                    //rabbits[j].eat() на будущее
                    foods[i].NewCords();
                }
            }
        }
        for (int p = 0; p < rabbits.size(); p++) {
            rabbits[p].ScanAndDrow(field, foods);
        }
        for (int i = 0; i < 25; i++) {
            std::cout << field[i] << '\n';
        }
        Sleep(300);
        if (l != 99) {
            system("cls");
        }
    }
    
}
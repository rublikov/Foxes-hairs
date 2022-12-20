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
    Carrot(int x, int y) : x(x), y(y) {}
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
    int getscordsx() {
        return x;
    }
    int getcordsy() {
        return y;
    }
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
    Creature(int x, int y, int sp) :x(x), y(y), speed(sp), hunger(5), distant(15) {}
    void ScanAndDrow(std::vector<std::string>& fl, std::vector<Carrot>& fd) {
        srand(time(NULL));
        int min = 1000;

        int n = -1;
        //scans to find closest
        for (int i = 0; i < fd.size(); i++) {
            if (((abs(x - fd[i].x) + abs(y - fd[i].y) < 1000)) && (min > (abs(x - fd[i].x)) + abs(y - fd[i].y))) {
                n = i;
                min = abs(x - fd[i].x) + abs(y - fd[i].y);
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
class Foxes : public Creature {
    Foxes(int x, int y, int sp) :Creature(x, y, sp) {}
};
class Rabbit :public Creature {
    int hunger_max = 150;

    int mingap = 20;

public:
    int gap;
    //Rabbit():Creature() {}
    Rabbit(int x, int y, int sp, int gap) :Creature(x, y, sp), gap(10) {}
    void eat() {
        if (hunger + 60 < hunger_max) {
            hunger += 60;
        }
        else {
            hunger = hunger_max;
        }
    }
    bool readyforsex() {
        return((gap > mingap) && (hunger > 0.8 * hunger_max));
    }
    void tick() {
        gap++;
    }
    void hung() {
        hunger--;
    }
    friend void sex(Rabbit C1, Rabbit C2, std::vector<Rabbit>& rabbits);
    friend int dist(Rabbit C1, Rabbit C2);
};
void sex(Rabbit C1, Rabbit C2, std::vector<Rabbit>& rab) {
    C1.hunger -= 40;
    C2.hunger -= 40;
    C1.gap = 0;
    C2.gap = 0;
    rab.push_back(Rabbit(C1.x, C2.y, 5, 1));           //speed change future
}
int dist(Rabbit C1, Rabbit C2)
{
    return(abs(C1.x - C2.x) + abs(C1.y - C2.y));
}


int main()
{
    srand(time(NULL));
    int num_of_food = 7;
    std::vector<Carrot> foods;
    for (int i = 0; i < num_of_food; i++) {
        foods.push_back(Carrot(rand() % 100, rand() % 24));
    }
    std::vector<Rabbit> rabbits;
    for (int i = 0; i < 3; i++) {
        rabbits.push_back(Rabbit(10 * i, 20, i + 1, 1));
    }
    std::vector<Rabbit*> readyrabbits;                           // 
    

    std::vector <std::string> field;
    for (int i = 0; i < 25; i++) {
        field.push_back("----------------------------------------------------------------------------------------------------");
    }
    for (int l = 0; l < 150; l++) {
        for (int i = 0; i < num_of_food; i++) {
            foods[i].DrawCarrot(field);
        }
        for (int j = 0; j < rabbits.size(); j++) {
            for (int i = 0; i < foods.size(); i++) {
                if (rabbits[j].colision(foods[i].x, foods[i].y)) {
                    rabbits[j].eat();
                    foods[i].NewCords();
                }
            }
        }
        readyrabbits.clear();
      
        for (int i = 0; i < 3; i++) {
            Rabbit* p = NULL;
            if (rabbits[i].readyforsex()) {
                p = &rabbits[i];
                readyrabbits.push_back(p);
            }
        }
        for (int p = 0; p < rabbits.size(); p++) {
            rabbits[p].tick();
            if (!rabbits[p].readyforsex()) {
                rabbits[p].ScanAndDrow(field, foods);
            }
            /*
                rabbits[p].ScanAndDrow<Rabbit>(field, readyrabbits);
            }
            rabbits[p].tick();
            rabbits[p].hung();
        */

            else {
                for (int i = 0; i < readyrabbits.size() - 1; i++) {
                    int min = 555;
                    int k = -1;
                    for (int j = i + 1; j < readyrabbits.size(); j++) {
                        if (dist(*readyrabbits[i], *readyrabbits[j]) < min)
                        {
                            min = dist(*readyrabbits[i], *readyrabbits[j]);
                            k = j;
                        }
                    }
                    if ((min < 555)&&(k!=-1))  {
                        readyrabbits[i]->DrawCreature(field, 5, 5);       // experiment
                        if (dist(*readyrabbits[i], *readyrabbits[k]) < 3) {
                            sex(*readyrabbits[i], *readyrabbits[k], rabbits);
                        }
                    }
                }
            }
        }


        for (int i = 0; i < 25; i++) {
            std::cout << field[i] << '\n';
        }
        Sleep(150);
        if (l != 99) {
            system("cls");
        }

    }
}
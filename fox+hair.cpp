#include<iostream>
#include<cmath>
#include<stdlib.h>
#include<Windows.h>
#include<vector>
#include<random>
#include<chrono>

struct Carrot {
    int x;
    int y;

    void SpawnCarrot() {
        std::cout << "@";
    }
    void NewCords() {
        x = rand() % 200+1;
        y = rand() % 48+1;
    }
    void DrawCarrot(std::vector<std::string>& fl) {
        fl[y][x] = '@';
    }
    Carrot(int x, int y) : x(x), y(y) {}
    /*bool colision(int a, int b) {
        if ((x != a) || (y != b)) {
            return true;
        }
        return false;
    }*///я не знаю зачем он тут нужен
};
class Creature {
protected:
    int distant;
    int ostx = 0;
    int osty = 0;
public:
    int x, y;
    int age;
    int hunger;
    int speed;
    Creature() {}
    Creature(int x, int y, int sp, int h, int age) :x(x), y(y), speed(sp), hunger(h), age(age), distant(15) {}
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

    void ScanAndDrow(std::vector<std::string>& fl, std::vector<Carrot>& fd) {
        srand(time(NULL));
        int min = 1000;

        int n = -1;
        //scans to find closest
        for (int i = 0; i < fd.size(); i++) {
            if (((abs(x - fd[i].x) + abs(y - fd[i].y) < 30)) && (min > (abs(x - fd[i].x)) + abs(y - fd[i].y))) {
                n = i;
                min = abs(x - fd[0].x) + abs(y - fd[i].y);
            }
        }
        if (n == -1) {
            DrawCreature(fl, rand() % 98 + 1, rand() % 48 + 1);
        }
        else {
            DrawCreature(fl, fd[n].x, fd[n].y);
        }

    }

    friend int dist(Creature* C1, Creature* C2);
};

int dist(Creature* C1, Creature* C2) {
    return(abs(C1->x - C2->x) + abs(C1->y - C2->y));
}
class Rabbit :public Creature {
public:
    //Rabbit():Creature() {}
    int max_hunger = 150;
    int min_gap = 60;
    Rabbit(int x, int y, int sp, int h, int age) :Creature(x, y, sp, h, age) {};
    void eat() 
    {
        hunger += 25;
    };
    friend void sex(Rabbit* C1, Rabbit* C2, std::vector<Rabbit*> rabbits);
};
void sex(Rabbit* C1, Rabbit* C2, std::vector<Rabbit*> rab) //добавить вероятность двойни и тройни
{
    C1->hunger -= 30;
    C2->hunger -= 30;
    C1->age = 15;
    C2->age = 15;
    Rabbit* p = NULL;
    p = new Rabbit(C1->x, C2->y, C1->speed, C1->max_hunger, 2); // генетика здесь
    rab.push_back(p); 
};


int main()
{
    int num_of_food = 6;                                    // количество еды одновременно на поле!
    srand(time(NULL));
    std::vector<Carrot> foods;                              // первая загрузка еды в вектор
    for (int i = 0; i < num_of_food; i++) {
        foods.push_back(Carrot(rand() % 199 + 1, rand() % 49));
    }
    std::vector<Rabbit*> rabbits;                           // создание вектора указателей на кроликов
    Rabbit* p = NULL;
    for (int i = 0; i < 3; i++) {
        p = new Rabbit(10 * i, 20, i*2 + 1, 50 + 10 * i, 1);
        rabbits.push_back(p);
    }
    std::vector <std::string> field;                        // создание поля
    for (int i = 0; i < 50; i++) {
        field.push_back("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
    }
                                       
    for (int l = 0; l < 500; l++) {                         // l++ -- один тик
        for (int i = 0; i < num_of_food; i++) {
            foods[i].DrawCarrot(field);                     // один раз нарисовали все морковки
        }
        for (int j = 0; j < rabbits.size(); j++) {
            for (int i = 0; i < foods.size(); i++) {
                if (rabbits[j]->colision(foods[i].x, foods[i].y)) {
                    rabbits[j]->eat(); 
                    if (rabbits[j]->hunger > rabbits[j]->max_hunger)
                    {
                        rabbits[j]->hunger = rabbits[j]->max_hunger;
                    }
                    foods[i].NewCords();
                }
            }
        }
        for (int p = 0; p < rabbits.size(); p++) {              // ??
            rabbits[p]->ScanAndDrow(field, foods);
        }
        for (int j = 0; j < rabbits.size(); j++) 
        {                                                       // старение, голод и смерть
            rabbits[j]->age++;
            rabbits[j]->hunger--;                               // отнимается 1 HungerPoint за тик
            if (rabbits[j]->hunger < 1)
            {
                rabbits[j]->speed = 0;
            }
        }
        for (int j = 0; j < rabbits.size() - 1; j++)
        {
            if ((rabbits[j]->hunger > 0, 8 * rabbits[j]->max_hunger) && (rabbits[j]->age > rabbits[j]->min_gap))
            {
                for (int i = j+1; i < rabbits.size(); i++)
                {
                    if ((rabbits[i]->hunger > 0, 8 * rabbits[i]->max_hunger) && (rabbits[i]->age > rabbits[i]->min_gap))
                    {
                        rabbits[i]->GoTo(rabbits[j]->x, rabbits[j]->y); // доделать адекватно
                        rabbits[j]->GoTo(rabbits[i]->x, rabbits[i]->y);
                        if (dist(rabbits[i], rabbits[j]) < 2)
                        {
                            sex(rabbits[j], rabbits[i], rabbits);
                        }
                    }


                }
            }
        }
                                // удаляем, только если лиса доела труп
            /* {
                std::vector<Rabbit*>::iterator pObj = rabbits.begin();
                pObj += j;
                delete* pObj;
                auto iter = rabbits.cbegin();
                iter += j;
                rabbits.erase(iter);
            }*/
        
        //to add age++ 
        for (int i = 0; i < 50; i++) {
            std::cout << field[i] << '\n';
        }
        Sleep(300);
        if (l != 75) {                              // ????
            system("cls");
        }
    }



}
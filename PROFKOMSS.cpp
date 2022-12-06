#include <iostream>
#include <cmath>
#include<Windows.h>
#include<vector>

struct Carrot {
    int x;
    int y;
    
    void SpawnCarrot() {
        std::cout << "@";
    }
    Carrot(int x, int y) : x(x), y(y){}
    bool colision(int a, int b) {
        if ((x != a) || (y != b)) {
            return true;
        }
        return false;
    }
};
class Creature {
    int hunger;
    int speed;
    int x, y;
    int ostx = 0;
    int osty = 0;

public:

    bool colision(int a, int b) {
        if ((x != a) || (y != b)) {
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
    
    Creature(int x, int y, int sp):x(x), y(y), speed(sp),hunger(5) {}
   //std::vector<std::string> 
       void DrawCreature( std::vector<std::string> & fl, int a, int b) {
       
               fl[y][x] = '+';
               GoTo(a, b);
               fl[y][x] = '*';
           

        
    }
        
};


int main()
{   
    Creature Gosha(10, 24, 1);

    Carrot Crosh(1,1);
    std::vector <std::string> field;
    for (int i = 0; i < 25; i++) {
        field.push_back("----------------------------------------------------------------------------------------------------");
    }
    for (int l = 0; l < 150; l++) {
        Gosha.DrawCreature(field, Crosh.x, Crosh.y);
        
        for (int i = 0; i < 25; i++) {
            std::cout << field[i] << '\n';
        }
        Sleep(100);
        if (l != 99) {
            system("cls");
        }
    }
    
}
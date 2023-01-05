
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include<iostream>
#include<thread>
#include<mutex>
using namespace std;
#include"BattleBit_Control.h"
#include"BattleBit_View.h"
#include"BattleBit_Model.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include<omp.h>
int main(int argc, char** argv)
{
    //Soldier& s = Soldier::getinstance();
    BattleBit_Control* battlebit_control = new  BattleBit_Control();

    battlebit_control->game_start(ROW_MAX, COL_MAX);
   return 0;
}


/*int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
*/
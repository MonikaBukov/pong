//
// Created by monik on 25/11/2022.
//

#ifndef PONGSFML_PADDLE_H
#define PONGSFML_PADDLE_H
#include <SFML/Graphics.hpp>


class Paddle : public sf::Sprite
{
 private:
 public:

    float speed = 200;
    bool moving = false;
    int direction = 0;


};

#endif // PONGSFML_PADDLE_H

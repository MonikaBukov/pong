//
// Created by monik on 25/11/2022.
//

#include "Ball.h"


void Ball::position(sf::RenderWindow& window)
{
  setPosition(
    window.getSize().x / 2 - getGlobalBounds().width,
    window.getSize().y / 2 - getGlobalBounds().height / 2);
}





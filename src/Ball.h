//
// Created by monik on 25/11/2022.
//
#ifndef PONGSFML_BALL_H
#define PONGSFML_BALL_H

#include <SFML/Graphics.hpp>
#include "Vector.h"
#include "iostream"

  class Ball : public sf::Sprite
  {
   public:
    Ball()= default;
    /*virtual ~Ball()
    {
      if (ballTexture != nullptr)
      {
        delete ballTexture;
      }

    }
    explicit Ball(const std::string& file_path):ballTexture(new sf::Texture())
    {
      if (!ballTexture->loadFromFile(file_path))
      {
        std::cerr << "Error\n";
        delete ballTexture;
        ballTexture = nullptr;
      }
      setTexture(*ballTexture);
    }
     */
    Ball(sf::Texture& myTexture, const std::string& file_path)
    {
      if (!myTexture.loadFromFile(file_path))
      {
        std::cerr << "Error\n";
      }
      setTexture(myTexture);
    }
    void drawBall(sf::RenderWindow & window)
    {
      window.draw(*this);
    }
    void position(sf::RenderWindow& window);
    float speed = 200;
  };

#endif // PONGSFML_BALL_H

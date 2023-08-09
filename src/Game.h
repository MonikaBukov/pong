
#ifndef PONG_GAME_H
#define PONG_GAME_H

#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"
#include "Vector.h"
#include "Paddle.h"
#include "Ball.h"


class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyEvent(sf::Event event);

  void gameOver();
  bool is_collide(sf::Sprite sprite1, sf::Sprite sprite2);

  //positions
  void startPosition();
  void positionReset();

  enum GameStates
  {
    MENU = 1,
    PLAY_GAME = 2,
    GAME_OVER = 3,
    PAUSE = 4
  };
  GameStates game_state;

 private:
  sf::RenderWindow& window;

  /*sf::Sound hit_sound;
  sf::SoundBuffer buffer; */
  // texts
  sf::Font font;
  sf::Font bfont;

  //menu
  sf::Text start_game;
  sf::Text AI_game;
  sf::Text quit_game;
  sf::Text menu_text;
  sf::Text esc_text;
  void menu();
  int menu_position = 1;
  bool ai_selected = false;
  void normalTextSetup(sf::Text& text);
  void selectedTextSetup(sf::Text& text);


  //pause screen
  sf::Text p_menu_text;
  sf::Text continue_game;
  sf::Text finish_game;
  void pauseMenu();
  bool yes_selected = true;

  //score
  sf::Text score1_text;
  sf::Text score2_text;
  sf::Text who_wins;
  int score_P1 = 0;
  int score_P2 = 0;
  void score();

  //objects
  sf::RectangleShape rectangle;

  //up, down player / AI
  Paddle blue_paddle;
  sf::Texture blue_paddle_texture;

  void aiPaddleMovement();
  int b    = 0;

  //w,s player
  Paddle red_paddle;
  sf::Texture red_paddle_texture;


  //ball
  Ball ball;
  sf::Texture bTexture;
  Vector ball_direction;
  void ballMovement(const float& dt);

  static float middlePointY(sf::Sprite sprite, float x);

  //sf::Sound hit_sound;
};

#endif // PONG_GAME_H

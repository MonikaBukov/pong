
#include "Game.h"
#include <iostream>

float Game::middlePointY(sf::Sprite sprite, float x)
  {
   x = sprite.getPosition().y + sprite.getGlobalBounds().height/2;
   return x;
  }

void Game::positionReset()
{
  if (0 - ball.getGlobalBounds().width > ball.getPosition().x || ball.getPosition().x > window.getSize().x)
  {
    if (0 - ball.getGlobalBounds().width > ball.getPosition().x)
    {
      ball_direction.x = -100;
      score2_text.setString(std::to_string(++score_P2));
    }
    else if (ball.getPosition().x > window.getSize().x)
    {
      ball_direction.x = 100;
      score1_text.setString(std::to_string(++score_P1));
    }
    ball.speed = 200;
    startPosition();
  }
}

void Game::aiPaddleMovement()
{
  if(ai_selected)
  {
    blue_paddle.moving = true;
    if (
      (middlePointY(ball, b) > (blue_paddle.getPosition().y + blue_paddle.getGlobalBounds().height) &&
      ball.getPosition().x > window.getSize().x / 1.5))
    {
      blue_paddle.direction = 1;
    }
    else if (
      (middlePointY(ball, b) < blue_paddle.getPosition().y) &&
      ball.getPosition().x > window.getSize().x/ 1.5)
    {
      blue_paddle.direction = -1;
    }
    else{
      blue_paddle.direction = 0;
    }
  }
}

void Game::normalTextSetup(sf::Text& text)
{
  text.setFont(font);
  text.setCharacterSize(20);
  text.setFillColor(sf::Color::White);
}

void Game::selectedTextSetup(sf::Text& text)
{
  text.setFont(bfont);
  text.setCharacterSize(50);
  text.setFillColor(sf::Color::White);
}

void Game::ballMovement(const float & dt)
{
  if (ball.getPosition().y > (window.getSize().y - ball.getGlobalBounds().height))
  {
    ball_direction.y = -ball_direction.y;
  }
  if (ball.getPosition().y < 0)
  {
    ball_direction.y = -ball_direction.y;
  }
  if (is_collide(ball, blue_paddle))
  {
    ball_direction.x = -50;

    float b = middlePointY(blue_paddle, b) - middlePointY(ball, b);
    ball_direction.y = -b;
    ball_direction.normalise();
    ball.speed += 20;
  }
  if (is_collide(ball, red_paddle))
  {
    float a = middlePointY(red_paddle, a) - middlePointY(ball, a);
    ball_direction.x = 50;
    ball_direction.y = -a;

    ball_direction.normalise();
    ball.speed += 20;

  }
  ball_direction.normalise();
  ball.move(ball_direction.x * ball.speed * dt, ball_direction.y * ball.speed * dt);
}

void Game::startPosition()
{
  ball.setPosition(
    window.getSize().x / 2 - ball.getGlobalBounds().width,
    window.getSize().y / 2 - ball.getGlobalBounds().height / 2);

  blue_paddle.setPosition(
    window.getSize().x - 30 - blue_paddle.getGlobalBounds().width,
    window.getSize().y / 2 - blue_paddle.getGlobalBounds().height / 2);

  red_paddle.setPosition(
    30, window.getSize().y / 2 - red_paddle.getGlobalBounds().height / 2);
  ball_direction.y = 0;

  ball.speed = 300;
}

bool Game::is_collide(sf::Sprite sprite1, sf::Sprite sprite2)
{
  if (
    (sprite1.getPosition().x + sprite1.getGlobalBounds().width >
     sprite2.getPosition().x) &&
    sprite1.getPosition().x <
      sprite2.getPosition().x + sprite2.getLocalBounds().width &&
    (sprite1.getPosition().y + sprite1.getGlobalBounds().height) >
      sprite2.getPosition().y &&
    sprite1.getPosition().y <
      sprite2.getPosition().y + sprite2.getGlobalBounds().height)
  {
    return true;
  }
  else
    return false;
}

void Game::gameOver()
{
  if (score_P1 == 2 || score_P2 == 2)
  {
    game_state = GameStates::GAME_OVER;
    score1_text.setPosition(
      window.getSize().x * 0.25 - score1_text.getGlobalBounds().width / 2,
      window.getSize().y * 0.5 - score1_text.getGlobalBounds().height);
    score2_text.setPosition(
      window.getSize().x * 0.75 - score2_text.getGlobalBounds().width / 2,
      window.getSize().y * 0.5 - score2_text.getGlobalBounds().height);

    if (score_P1 > score_P2)
    {
      who_wins.setString("Red won!");
      who_wins.setFillColor(sf::Color::Red);
    }
    else
    {
      who_wins.setString("Blue won!");
      who_wins.setFillColor(sf::Color(3,37,126));
    }
    who_wins.setFont(font);
    who_wins.setCharacterSize(60);
    who_wins.setPosition(
      window.getSize().x / 2 - who_wins.getGlobalBounds().width / 2.,
      window.getSize().y / 4 - who_wins.getGlobalBounds().height / 2);
  }
}

void Game::menu()
{
  if (!font.loadFromFile("Data/Fonts/Digital Play St.ttf"))
  {
    std::cout << "font did not load";
  }
  if (!bfont.loadFromFile("Data/Fonts/digital dark system.ttf"))
  {
    std::cout << "font did not load";
  }
  normalTextSetup(menu_text);
  menu_text.setString("Welcome to Pong. Press enter to start:");

  menu_text.setPosition(
    window.getSize().x / 2 - menu_text.getGlobalBounds().width / 2.,
    window.getSize().y / 4 - menu_text.getGlobalBounds().height / 2);

  start_game.setString("Start Game 2P");
  normalTextSetup(start_game);
  start_game.setPosition(
    window.getSize().x / 2 - 300 - start_game.getGlobalBounds().width / 2.,
    window.getSize().y / 2 - start_game.getGlobalBounds().height / 2);

  AI_game.setString("Start Game 1P");
  normalTextSetup(AI_game);
  AI_game.setPosition(
    window.getSize().x / 2 - AI_game.getGlobalBounds().width / 2.,
    window.getSize().y / 2 - AI_game.getGlobalBounds().height / 2);

  quit_game.setString("Quit");
  normalTextSetup(quit_game);
  quit_game.setPosition(
    window.getSize().x / 2 + 300 - quit_game.getGlobalBounds().width / 2.,
    window.getSize().y / 2 - quit_game.getGlobalBounds().height / 2);
};

void Game::pauseMenu()
{
  p_menu_text.setString("Do you wish to continue?:");
  normalTextSetup(p_menu_text);
  p_menu_text.setPosition(
    window.getSize().x / 2 - p_menu_text.getGlobalBounds().width / 2,
    window.getSize().y / 4 - p_menu_text.getGlobalBounds().height / 2);

  // play
  continue_game.setString("Yes");
  normalTextSetup(continue_game);
  continue_game.setPosition(
    window.getSize().x / 2 - 200 - continue_game.getGlobalBounds().width / 2.,
    window.getSize().y / 2 - continue_game.getGlobalBounds().height / 2);

  // quit
  finish_game.setString("No");
  normalTextSetup(finish_game);
  finish_game.setPosition(
    window.getSize().x / 2 + 200 - finish_game.getGlobalBounds().width / 2.,
    window.getSize().y / 2 - finish_game.getGlobalBounds().height / 2);
};

void Game::score()
{

  score1_text.setFont(font);
  score1_text.setCharacterSize(70);
  score1_text.setFillColor(sf::Color::White);
  score1_text.setPosition(
    window.getSize().x * 0.25 - score1_text.getGlobalBounds().width / 2, 30);


  score2_text.setFont(font);
  score2_text.setCharacterSize(70);
  score2_text.setFillColor(sf::Color::White);
  score2_text.setPosition(
    window.getSize().x * 0.75 - score2_text.getGlobalBounds().width / 2, 30);
}

Game::Game(sf::RenderWindow& game_window) : window(game_window)
{
  srand(time(NULL));
}

Game::~Game() {
}

bool Game::init()
{
  rectangle.setSize(sf::Vector2f(1, window.getSize().y));
  rectangle.setPosition(window.getSize().x / 2, 0);

  ball = Ball(bTexture, "Data/Images/ballGrey.png");
  ball.position(window);

  menu();
  pauseMenu();
  score();

  esc_text.setString("esc");
  selectedTextSetup(esc_text);
  esc_text.setPosition(window.getSize().x - esc_text.getGlobalBounds().width - 20, 10);


 /* sf::SoundBuffer buffer;
  if (!buffer.loadFromFile("Data/Images/Plink.wav"))
    return -1;
  hit_sound.setBuffer(buffer);
*/
  //paddles
  if (!red_paddle_texture.loadFromFile("Data/Images/paddleRed.png"))
  {
    std::cout << "paddleRed texture did not load\n";
  }
  red_paddle.setTexture(red_paddle_texture);
  red_paddle.setPosition(
    30, window.getSize().y / 2 - red_paddle.getGlobalBounds().height / 2);

  if (!blue_paddle_texture.loadFromFile("Data/Images/paddleBlue.png"))
  {
    std::cout << "paddleBlue texture did not load\n";
  }
  blue_paddle.setTexture(blue_paddle_texture);
  blue_paddle.setPosition(
    window.getSize().x - 30 - blue_paddle.getGlobalBounds().width,
    window.getSize().y / 2 - blue_paddle.getGlobalBounds().height / 2);

  //vectors
  ball_direction.x = 100;
  ball_direction.y = 0;
  ball_direction.normalise();

  game_state = GameStates::MENU;

  return true;
}

void Game::update(float dt)
{
  if (game_state == GameStates::MENU)
  {
    score1_text.setString(std::to_string(score_P1=0));
    score2_text.setString(std::to_string(score_P2=0));
    startPosition();
  }
  if (game_state == GameStates::PLAY_GAME)
  {
    aiPaddleMovement();
    ballMovement(dt);
    if (
      red_paddle.moving && ((red_paddle.direction == -1 && red_paddle.getPosition().y > 0) ||
                  (red_paddle.direction == 1 &&
                   (red_paddle.getPosition().y +
                    red_paddle.getGlobalBounds().height) < window.getSize().y)))
    {
      red_paddle.move(0, red_paddle.direction * red_paddle.speed * dt);
    }
    if (
      blue_paddle.moving &&
      ((blue_paddle.direction == -1 && blue_paddle.getPosition().y > 0) ||
       (blue_paddle.direction == 1 &&
        (blue_paddle.getPosition().y + blue_paddle.getGlobalBounds().height) <
          window.getSize().y)))
    {
      blue_paddle.move(0, blue_paddle.direction * blue_paddle.speed * dt);
    }
    positionReset();
    gameOver();
  }
}

void Game::render()
{
  if (game_state == GameStates::MENU)
  {
    window.draw(start_game);
    window.draw(menu_text);
    window.draw(AI_game);
    window.draw(quit_game);
  }
  if (game_state == GameStates::PAUSE)
  {
    window.draw(continue_game);
    window.draw(p_menu_text);
    window.draw(finish_game);
  }

  if (game_state == GameStates::PLAY_GAME)
  {
    window.draw(esc_text);
    window.draw(red_paddle);
    window.draw(blue_paddle);
    window.draw(score1_text);
    window.draw(score2_text);
    window.draw(rectangle);
    ball.drawBall(window);

  }
  if (game_state == GameStates::GAME_OVER)
  {
    window.draw(esc_text);
    window.draw(score1_text);
    window.draw(score2_text);
    window.draw(who_wins);
  }
}

void Game::mouseClicked(sf::Event event)
{
  // get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);
}

void Game::keyEvent(sf::Event event)
{
  if (game_state == GameStates::MENU)
  {
    if (event.key.code == sf::Keyboard::Right && event.type == sf::Event::KeyPressed)
    {
      if(menu_position < 3)
      {
        ++menu_position;
      }
    }
    else if (
      event.key.code == sf::Keyboard::Left &&
      event.type == sf::Event::KeyPressed)
    {
      if (menu_position > 1)
      --menu_position;

    }

    if (menu_position == 1)
    {
      selectedTextSetup(start_game);
      normalTextSetup(AI_game);
      normalTextSetup(quit_game);

    }
    if (menu_position == 2)
    {
      normalTextSetup(start_game);
      selectedTextSetup(AI_game);
      normalTextSetup(quit_game);

    }
    else if (menu_position == 3)
    {
      normalTextSetup(start_game);
      normalTextSetup(AI_game);
      selectedTextSetup(quit_game);
    }
    {
      if (
        (event.key.code == sf::Keyboard::Enter &&
        event.type == sf::Event::KeyPressed) && (menu_position == 1 || menu_position == 2))
      {
        if(menu_position == 2)
        {ai_selected = true;}
        game_state = GameStates::PLAY_GAME;
      }
      else if (
        event.key.code == sf::Keyboard::Enter &&
        event.type == sf::Event::KeyPressed && menu_position == 3)
      {
        window.close();
      }
    }
  }

    if (game_state == GameStates::PLAY_GAME)
    {
      if (
        event.key.code == sf::Keyboard::Escape &&
        event.type == sf::Event::KeyPressed)
      {
        game_state = GameStates::PAUSE;
      }

      else if (event.key.code == sf::Keyboard::W)
      {
        red_paddle.moving      = event.type == sf::Event::KeyPressed;
        red_paddle.direction = -1;
      }
      else if (event.key.code == sf::Keyboard::S)
      {
        red_paddle.moving     = event.type == sf::Event::KeyPressed;
        red_paddle.direction = 1;
      }
      if (!ai_selected)
      {
        if (event.key.code == sf::Keyboard::Up)
        {
          blue_paddle.moving       = event.type == sf::Event::KeyPressed;
          blue_paddle.direction = -1;
        }
        else if (event.key.code == sf::Keyboard::Down)
        {
          blue_paddle.moving        = event.type == sf::Event::KeyPressed;
          blue_paddle.direction = 1;
        }
      }
    }
    else if (game_state == GameStates::PAUSE)
    {
      if (
        ((event.key.code == sf::Keyboard::Left) ||
         (event.key.code == sf::Keyboard::Right)) &&
        event.type == sf::Event::KeyPressed)
      {
        yes_selected = !yes_selected;
        if (yes_selected)
        {
          selectedTextSetup(continue_game);
          normalTextSetup(finish_game);
        }
        else
        {
          normalTextSetup(continue_game);
          selectedTextSetup(finish_game);
        }
      }

      else if (
        event.key.code == sf::Keyboard::Enter &&
        event.type == sf::Event::KeyPressed)
      {
        if (yes_selected)
        {
          game_state = GameStates::PLAY_GAME;
        }
        else
        {
          game_state = GameStates::MENU;
        }
      }
    }

  if (game_state == GameStates::GAME_OVER && event.key.code == sf::Keyboard::Escape)
  {
    score_P1      = 0;
    score_P2      = 0;
    game_state    = GameStates::MENU;
  };
}

/*
 * File: Paddle.hpp
 * Project: Breakout
 * Created Date: Friday December 27th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Friday December 27th 2019 10:03:21 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <TE/IDrawable.hpp>
#include <TE/IUpdatable.hpp>
#include <TE/InputHandler.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <SFML/System/Vector2.hpp>

class Paddle : public InputHandler, public IUpdatable, public IDrawable
{
private:
  void defaultInit();

  bool moveLeft(sf::Event &event);
  bool moveRight(sf::Event &event);
  bool releaseLeft(sf::Event &event);
  bool releaseRight(sf::Event &event);

public:
  Paddle();
  ~Paddle();

  virtual void draw(const sf::Time &dt, sf::RenderTexture &renderTexture);
  virtual void update(const sf::Time &dt);

  void setTexture(sf::Texture &texture);
  void setSpeed(float speed);
  float getSpeed();
  int getDirection();
  sf::Vector2f getPosition();

  int getWidth();
  int getHeight();

private:
  sf::Sprite paddle;
  int direction;

  float speed;
  int width;
  int height;

public:
};

#endif
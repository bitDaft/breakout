/*
 * File: Ball.hpp
 * Project: Breakout
 * Created Date: Friday December 27th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Friday December 27th 2019 10:03:21 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#ifndef BALL_HPP
#define BALL_HPP

#include <TE/IDrawable.hpp>
#include <TE/IUpdatable.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Ball : public IUpdatable, public IDrawable
{

private:
  virtual void draw(const sf::Time &dt, sf::RenderTexture &renderTexture);
  virtual void update(const sf::Time &dt);

public:
  Ball();
  ~Ball();

  void setPosition(float x, float y);
  void setTexture(sf::Texture &texture);
  void setVelocity(sf::Vector2f velocity);
  sf::Vector2f getVelocity();
  sf::Vector2f getPosition();
  int getWidth();
  int getHeight();

private:
  sf::Sprite ball;
  sf::Vector2f velocity;
  int width;
  int height;
};

#endif
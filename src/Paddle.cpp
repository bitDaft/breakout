/*
 * File: Paddle.cpp
 * Project: Breakout
 * Created Date: Friday December 27th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Saturday December 28th 2019 10:56:39 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#include "Paddle.hpp"
#include "Actions.hpp"

#include <iostream>

Paddle::Paddle()
    : IUpdatable(1),
      IDrawable(2),
      direction(0),
      speed(300),
      width(0),
      height(0)
{
  defaultInit();
}
Paddle::~Paddle()
{
}

void Paddle::setTexture(sf::Texture &texture)
{
  float fromBottom = 50;
  paddle.setTexture(texture);
  paddle.setPosition(300, 600 - fromBottom - texture.getSize().y);
  width = texture.getSize().x;
  height = texture.getSize().y;
}

void Paddle::draw(const sf::Time &dt, sf::RenderTexture &renderTexture)
{
  renderTexture.draw(paddle);
}

void Paddle::update(const sf::Time &dt)
{
  sf::Vector2f new_pos = paddle.getPosition();
  new_pos.x += speed * direction * dt.asSeconds();
  if (!(new_pos.x < 0 || new_pos.x + width > 800 || new_pos.y < 0 || new_pos.y + height > 600))
  {
    paddle.setPosition(new_pos);
  }
}
void Paddle::setSpeed(float speed)
{
  this->speed = speed;
}

void Paddle::defaultInit()
{
  _reactionMapper->bindActionToReaction<moveLeft>(Actions::LEFT);
  _reactionMapper->bindActionToReaction<moveRight>(Actions::RIGHT);
  _reactionMapper->bindActionToReaction<releaseLeft>(Actions::LEFT_RELEASE);
  _reactionMapper->bindActionToReaction<releaseRight>(Actions::RIGHT_RELEASE);
}

bool Paddle::moveLeft(sf::Event &event)
{
  direction--;
  return false;
}
bool Paddle::moveRight(sf::Event &event)
{
  direction++;
  return false;
}
bool Paddle::releaseLeft(sf::Event &event)
{
  direction++;
  return false;
}
bool Paddle::releaseRight(sf::Event &event)
{
  direction--;
  return false;
}

sf::Vector2f Paddle::getPosition()
{
  return paddle.getPosition();
}

int Paddle::getWidth()
{
  return width;
}
int Paddle::getHeight()
{
  return height;
}
float Paddle::getSpeed()
{
  return speed;
}
int Paddle::getDirection()
{
  return direction;
}

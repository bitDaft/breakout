/*
 * File: Ball.cpp
 * Project: Breakout
 * Created Date: Friday December 27th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Friday December 27th 2019 11:06:09 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#include "ball.hpp"
#include "xoshiro256plus.hpp"
#include <iostream>

Ball::Ball()
    : IUpdatable(1),
      IDrawable(3),
      velocity(0, 5),
      width(0),
      height(0)
{
}
Ball::~Ball()
{
}

void Ball::draw(const sf::Time &dt, sf::RenderTexture &renderTexture)
{
  renderTexture.draw(ball);
}

void Ball::update(const sf::Time &dt)
{
  sf::Vector2f new_pos = ball.getPosition() + (velocity * dt.asSeconds());
  if (new_pos.x < 0 || new_pos.x + width > 800)
  {
    velocity.x = -velocity.x;
  }
  if (new_pos.y < 0 || new_pos.y + height > 600)
  {
    velocity.y = -velocity.y;
  }
  ball.setPosition(new_pos);
}

void Ball::setPosition(float x, float y)
{
  ball.setPosition(x, y);
}
void Ball::setTexture(sf::Texture &texture)
{
  width = texture.getSize().x;
  height = texture.getSize().y;
  ball.setTexture(texture);
}
void Ball::setVelocity(sf::Vector2f velocity)
{
  this->velocity = velocity;
}
sf::Vector2f Ball::getPosition()
{
  return ball.getPosition();
}
int Ball::getWidth()
{
  return width;
}
int Ball::getHeight()
{
  return height;
}
sf::Vector2f Ball::getVelocity()
{
  return velocity;
}
/*
 * File: Ball.cpp
 * Project: Breakout
 * Created Date: Friday December 27th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Sunday December 29th 2019 9:46:40 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#include "ball.hpp"
#include "xoshiro256plus.hpp"
#include <iostream>

#define MAX_SPEED_X 400
#define MAX_SPEED_Y 400

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
    new_pos = ball.getPosition() + (velocity * dt.asSeconds());
  }
  if (new_pos.y < 0 || new_pos.y + height > 600)
  {
    velocity.y = -velocity.y;
    new_pos = ball.getPosition() + (velocity * dt.asSeconds());
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
  if (velocity.x > MAX_SPEED_X)
  {
    velocity.x = MAX_SPEED_X;
  }
  if (velocity.y > MAX_SPEED_Y)
  {
    velocity.y = MAX_SPEED_Y;
  }
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
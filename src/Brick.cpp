/*
 * File: Brick.cpp
 * Project: Breakout
 * Created Date: Friday December 27th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Saturday December 28th 2019 11:34:18 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#include "Brick.hpp"

void Brick::draw(const sf::Time &dt, sf::RenderTexture &renderTexture)
{
  renderTexture.draw(brick);
}

Brick::Brick(float x, float y, sf::Texture &texture)
    : IDrawable(1),
      width(0),
      height(0)
{
  brick.setPosition(x, y);
  brick.setTexture(texture);
  width = texture.getSize().x;
  height = texture.getSize().y;
  // brick.setScale(2.f,2.f);
}
Brick::~Brick()
{
}

sf::Vector2f Brick::getPosition()
{
  return brick.getPosition();
}
int Brick::getWidth()
{
  return width;
}
int Brick::getHeight()
{
  return height;
}
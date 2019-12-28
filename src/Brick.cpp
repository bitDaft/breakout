/*
 * File: Brick.cpp
 * Project: Breakout
 * Created Date: Friday December 27th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Friday December 27th 2019 2:54:52 pm
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
    : IDrawable(1)
{
  brick.setPosition(x, y);
  brick.setTexture(texture);
  // brick.setScale(2.f,2.f);
}
Brick::~Brick()
{
}

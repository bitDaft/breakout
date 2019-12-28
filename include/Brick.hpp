/*
 * File: Brick.hpp
 * Project: Breakout
 * Created Date: Friday December 27th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Friday December 27th 2019 3:12:28 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#ifndef BRICK_HPP
#define BRICK_HPP

#include <TE/IDrawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Brick : public IDrawable
{

private:
  virtual void draw(const sf::Time &dt, sf::RenderTexture &renderTexture);

public:
  Brick(float x, float y, sf::Texture &texture);
  ~Brick();

private:
  sf::Sprite brick;

public:
};

#endif
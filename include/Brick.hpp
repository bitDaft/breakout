/*
 * File: Brick.hpp
 * Project: Breakout
 * Created Date: Friday December 27th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Saturday December 28th 2019 11:34:18 am
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

  sf::Vector2f getPosition();
  int getWidth();
  int getHeight();

private:
  sf::Sprite brick;
  int width;
  int height;

public:
};

#endif
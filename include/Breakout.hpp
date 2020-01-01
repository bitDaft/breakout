/*
 * File: Breakout.hpp
 * Project: Breakout
 * Created Date: Friday December 27th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Sunday December 29th 2019 10:59:21 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#ifndef BREAKOUT_HPP
#define BREAKOUT_HPP

#include <vector>

#include <TE/Game.hpp>
#include <TE/IUpdatable.hpp>

#include "Brick.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"

class Breakout : public Game, public IUpdatable
{
private:
  void defaultInit();
  void init();
  void end();

  virtual void update(const sf::Time &dt);

  void brick_factory(int count, int perRow, int startX, int startY);

public:
  Breakout(const int wndWidth, const int wndHeight, const char *wndName);
  ~Breakout();

private:
  unsigned int brickHandle;
  unsigned int paddleHandle;
  unsigned int ballHandle;

  std::vector<Brick *> brick_list;
  Paddle paddle;
  Ball ball;
  sf::Vector2f preballpos;
};

#endif
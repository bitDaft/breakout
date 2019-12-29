/*
 * File: Breakout.cpp
 * Project: Breakout
 * Created Date: Friday December 27th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Sunday December 29th 2019 10:14:48 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#include <TE/ResourceManager.hpp>

#include "Breakout.hpp"
#include "Actions.hpp"
#include "xoshiro256plus.hpp"

#include <iostream>

#define BRICK_ROWS 30
#define BRICK_PER_ROW_COUNT 25 // can be a maximum of 33 with default size of texture

Breakout::Breakout(const int wndWidth, const int wndHeight, const char *wndName)
    : Game(wndWidth, wndHeight, wndName),
      IUpdatable(2)
{
  defaultInit();
  brick_list.reserve(30);
}

Breakout::~Breakout()
{
}

void Breakout::brick_factory(int count, int perRow, int startX, int startY)
{
  sf::Texture &_tempTexture = ResourceManager::getTexture(brickHandle);
  float width = _tempTexture.getSize().x;
  float height = _tempTexture.getSize().y;
  for (int i = 0; i < count; i++)
  {
    brick_list.emplace_back(new Brick(((i % perRow) * width) + startX, ((i / perRow) * height) + startY, _tempTexture));
  }
}
void Breakout::defaultInit()
{
  _aMapper.bindInputToAction(sf::Keyboard::Up, sf::Event::KeyPressed, Actions::UP);
  _aMapper.bindInputToAction(sf::Keyboard::Up, sf::Event::KeyReleased, Actions::UP_RELEASE);
  _aMapper.bindInputToAction(sf::Keyboard::Down, sf::Event::KeyPressed, Actions::DOWN);
  _aMapper.bindInputToAction(sf::Keyboard::Down, sf::Event::KeyReleased, Actions::DOWN_RELEASE);
  _aMapper.bindInputToAction(sf::Keyboard::Left, sf::Event::KeyPressed, Actions::LEFT);
  _aMapper.bindInputToAction(sf::Keyboard::Left, sf::Event::KeyReleased, Actions::LEFT_RELEASE);
  _aMapper.bindInputToAction(sf::Keyboard::Right, sf::Event::KeyPressed, Actions::RIGHT);
  _aMapper.bindInputToAction(sf::Keyboard::Right, sf::Event::KeyReleased, Actions::RIGHT_RELEASE);
  _aMapper.bindInputToAction(sf::Keyboard::Escape, sf::Event::KeyPressed, Actions::QUIT);
  _aMapper.bindInputToAction(sf::Keyboard::W, sf::Event::KeyPressed, Actions::UP);
  _aMapper.bindInputToAction(sf::Keyboard::W, sf::Event::KeyReleased, Actions::UP_RELEASE);
  _aMapper.bindInputToAction(sf::Keyboard::S, sf::Event::KeyPressed, Actions::DOWN);
  _aMapper.bindInputToAction(sf::Keyboard::S, sf::Event::KeyReleased, Actions::DOWN_RELEASE);
  _aMapper.bindInputToAction(sf::Keyboard::A, sf::Event::KeyPressed, Actions::LEFT);
  _aMapper.bindInputToAction(sf::Keyboard::A, sf::Event::KeyReleased, Actions::LEFT_RELEASE);
  _aMapper.bindInputToAction(sf::Keyboard::D, sf::Event::KeyPressed, Actions::RIGHT);
  _aMapper.bindInputToAction(sf::Keyboard::D, sf::Event::KeyReleased, Actions::RIGHT_RELEASE);

  _aMapper.bindInputToAction(sf::Mouse::Button::Left, sf::Event::MouseButtonPressed, Actions::MOUSE_LEFT);
  _aMapper.bindInputToAction(sf::Mouse::Button::Left, sf::Event::MouseButtonReleased, Actions::MOUSE_LEFT_RELEASE);
  _aMapper.bindInputToAction(sf::Mouse::Button::Right, sf::Event::MouseButtonPressed, Actions::MOUSE_RIGHT);
  _aMapper.bindInputToAction(sf::Mouse::Button::Right, sf::Event::MouseButtonReleased, Actions::MOUSE_RIGHT_RELEASE);
  _aMapper.bindInputToAction(sf::Mouse::Button::Middle, sf::Event::MouseButtonPressed, Actions::MOUSE_MIDDLE);
  _aMapper.bindInputToAction(sf::Mouse::Button::Middle, sf::Event::MouseButtonReleased, Actions::MOUSE_MIDDLE_RELEASE);
  _aMapper.bindInputToAction(sf::Mouse::Button::XButton1, sf::Event::MouseButtonPressed, Actions::MOUSE_X1);
  _aMapper.bindInputToAction(sf::Mouse::Button::XButton1, sf::Event::MouseButtonReleased, Actions::MOUSE_X1_RELEASE);
  _aMapper.bindInputToAction(sf::Mouse::Button::XButton2, sf::Event::MouseButtonPressed, Actions::MOUSE_X2);
  _aMapper.bindInputToAction(sf::Mouse::Button::XButton2, sf::Event::MouseButtonReleased, Actions::MOUSE_X2_RELEASE);
  _aMapper.bindInputToAction(sf::Event::MouseMoved, Actions::MOUSE_MOVED);
  _aMapper.bindInputToAction(sf::Event::MouseWheelScrolled, Actions::MOUSE_SCROLL);
}

void Breakout::init()
{
  brickHandle = ResourceManager::loadTexture("assets/breakout-tile.png");
  paddleHandle = ResourceManager::loadTexture("assets/breakout-paddle.png");
  ballHandle = ResourceManager::loadTexture("assets/breakout-ball.png");

  brick_factory(
      BRICK_PER_ROW_COUNT * BRICK_ROWS,
      BRICK_PER_ROW_COUNT,
      (gameWindow.getSize().x - (ResourceManager::getTexture(brickHandle).getSize().x * BRICK_PER_ROW_COUNT)) / 2,
      100);

  paddle.setTexture(ResourceManager::getTexture(paddleHandle));
  ball.setTexture(ResourceManager::getTexture(ballHandle));
  ball.setPosition(gameWindow.getSize().x / 2, gameWindow.getSize().y - 100);
  ball.setVelocity(sf::Vector2f(100, -50));

  _reactionMapper->bindActionToReaction<quit>(Actions::QUIT);
  _inputManager.pushEntity(&paddle);

  setRandSeed(45287349545, 7658327957364, 4658723498543, 84658327953);
}

void Breakout::end()
{
}

void Breakout::update(const sf::Time &dt)
{
  // check for collisions
  sf::Vector2f ballpos = ball.getPosition();
  sf::Vector2f paddlepos = paddle.getPosition();
  sf::Vector2f _vel = ball.getVelocity();

  // check whether it is below all the block threshold
  int endY = ball.getHeight() * BRICK_ROWS + 100; // 100 is the start offset

  if (ballpos.y > endY && _vel.y > 0) // if it is below blocks and move down check paddle collision
  {
    bool cond11 = ballpos.x < (paddlepos.x + paddle.getWidth());
    bool cond12 = (ballpos.x + ball.getWidth()) > paddlepos.x;
    bool cond21 = ballpos.y < (paddlepos.y + paddle.getHeight());
    bool cond22 = (ballpos.y + ball.getHeight()) > paddlepos.y;

    if (cond11 && cond12 && cond21 && cond22)
    {
      _vel.y = -_vel.y;
      _vel.x = _vel.x + (paddle.getSpeed() * paddle.getDirection() * dt.asSeconds());
      _vel.x *= 1.05;
      _vel.y *= 1.05;
      ball.setVelocity(_vel);
    }
  }
  else // else check for brick collision
  {
    int hitX = false;
    int hitY = false;
    int xdist = 0;
    int ydist = 0;
    int toDelete = -1;
    for (int i = 0; i < brick_list.size(); i++)
    {
      sf::Vector2f preballpos = ball.getPosition();
      if (brick_list[i] != nullptr)
      {
        sf::Vector2f brickpos = brick_list[i]->getPosition();
        if (_vel.y > 0)
        {
          if (brickpos.y < ballpos.y - 10)
          {
            continue;
          }
        }
        else
        {
          if (brickpos.y > ballpos.y + 10)
          {
            break;
          }
        }
        bool cond11 = ballpos.x < (brickpos.x + brick_list[i]->getWidth());
        bool cond12 = (ballpos.x + ball.getWidth()) > brickpos.x;
        bool cond21 = ballpos.y < (brickpos.y + brick_list[i]->getHeight());
        bool cond22 = (ballpos.y + ball.getHeight()) > brickpos.y;
        if (cond11 && cond12 && cond21 && cond22)
        {
          _vel.x *= 1.01;
          _vel.y *= 1.01;
          if (!hitX && !hitY)
          {
            int tempx = xdist;
            int tempy = ydist;
            xdist = ballpos.x + ball.getWidth() - brickpos.x;
            if (xdist > brick_list[i]->getWidth())
            {
              xdist = brickpos.x + brick_list[i]->getWidth() - ballpos.x;
            }
            ydist = ballpos.y + ball.getHeight() - brickpos.y;
            if (ydist > brick_list[i]->getHeight())
            {
              ydist = brickpos.y + brick_list[i]->getHeight() - ballpos.y;
            }
            if (xdist < tempx || ydist < tempy)
            {
              xdist = tempx;
              ydist = tempy;
            }
            else
            {
              toDelete = i;
            }
            if (xdist <= ydist)
            {
              hitX = true;
            }
            else if (xdist >= ydist)
            {
              hitY = true;
            }
            ball.setPosition(preballpos.x,preballpos.y);
          }
        }
      }
    }
    if (hitX)
    {
      _vel.x = -_vel.x;
    }
    if (hitY)
    {
      _vel.y = -_vel.y;
    }
    if (hitX || hitY)
    {
      delete brick_list[toDelete];
      brick_list[toDelete] = nullptr;
    }
    ball.setVelocity(_vel);
  }
}

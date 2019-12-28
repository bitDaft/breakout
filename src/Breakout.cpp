/*
 * File: Breakout.cpp
 * Project: Breakout
 * Created Date: Friday December 27th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Saturday December 28th 2019 11:06:42 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#include <TE/ResourceManager.hpp>

#include "Breakout.hpp"
#include "Actions.hpp"
#include "xoshiro256plus.hpp"

#include <iostream>

#define BRICK_ROWS 20
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
  ball.setPosition(gameWindow.getSize().x / 2, gameWindow.getSize().y - 200);
  ball.setVelocity(sf::Vector2f(0, 100));

  _reactionMapper->bindActionToReaction<quit>(Actions::QUIT);
  _inputManager.pushEntity(&paddle);

  setRandSeed(45287349545, 327658327957364, 324658723498543, 3784658327953);
}

void Breakout::end()
{
}

void Breakout::update(const sf::Time &dt)
{
  // check for collisions
  sf::Vector2f ballpos = ball.getPosition();
  sf::Vector2f paddlepos = paddle.getPosition();
  bool cond11 = ballpos.x < (paddlepos.x + paddle.getWidth());
  bool cond12 = (ballpos.x + ball.getWidth()) > paddlepos.x;
  bool cond21 = ballpos.y < (paddlepos.y + paddle.getHeight());
  bool cond22 = (ballpos.y + ball.getHeight()) > paddlepos.y;

  if (cond11 && cond12 && cond21 && cond22)
  {
    sf::Vector2f _vel = ball.getVelocity();
    if (_vel.y > 0)
    {
      _vel.y = -_vel.y;
    }
    _vel.x = _vel.x + (paddle.getSpeed() * paddle.getDirection() * dt.asSeconds());
    ball.setVelocity(_vel);
  }
}

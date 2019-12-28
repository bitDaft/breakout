/*
 * File: main.cpp
 * Project: Breakout
 * Created Date: Friday December 27th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Friday December 27th 2019 1:15:46 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#include <iostream>

#include "Breakout.hpp"

int main(int argc, char *argv[]) {

	Breakout *game = new Breakout(800,600,"Break-Out");
	game->run();

}
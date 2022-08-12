/*
 * window.hpp
 *
 *  Created on: 9 ago 2022
 *  Author: Francesco Antonetti Lamorgese Passeri
 *  License: CC-BY-SA 4.0 (https://creativecommons.org/licenses/by-sa/4.0/)
 *  This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
 */

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "Arduino.h"

#ifndef UTFT_h
#include "UTFT/UTFT.h"
#endif

class window
{
private:
	int size[2];
	int position[2];
	int fontSize[2];
	UTFT& tft;
public:
	window(UTFT&,int*,int*);
	window(UTFT&,int,int,int,int);
	int* getSize();
	int* getPosition();
	void drawBorders();
	void clearWindow();
	void text(String text);
};

#endif /* WINDOW_HPP_ */

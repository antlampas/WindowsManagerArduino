/*
 * windowManager.cpp
 *
 *  Created on: 9 ago 2022
 *  Author: Francesco Antonetti Lamorgese Passeri
 *  License: CC-BY-SA 4.0 (https://creativecommons.org/licenses/by-sa/4.0/)
 *  This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
 */

#ifndef WINDOWMANAGER_HPP_
#include "windowManager.hpp"
#endif

#include "Arduino.h"

windowManager::windowManager(const int winNum) : windowsNumber{winNum},countRegisteredWindows{0}
{
	this->windows = (window**)malloc(sizeof(window*)*winNum);
	for(int i=0;i<windowsNumber;i++) this->windows[i] = nullptr;
}
bool windowManager::checkWindow(int* size,int* position)
{
	/*
	 * Checks if the window passed doesn't overlap with any other previously created window
	 */
	for(int i=0;i<this->countRegisteredWindows;i++)
	{
		int previousWindowPosition[2] {this->windows[i]->getPosition()[0],this->windows[i]->getPosition()[1]};
		int previousWindowSize[2]     {this->windows[i]->getSize()[0],this->windows[i]->getSize()[1]};

		if(!((position[0]>(previousWindowPosition[0]+previousWindowSize[0])) || ((position[0]+size[0])<previousWindowPosition[0]) || (position[1]>(previousWindowPosition[1]+previousWindowSize[1])) || ((position[1]+size[1])<previousWindowPosition[1])))
		{
			return true;
		}
	}
	return false;
}
void windowManager::registerWindow(UTFT& tft,int* size,int* position)
{
	/*
	 * The window can be built only if:
	 * - it is the first window to be created (this->countRegisteredWindows == 0; this->checkWindow() doesn't matter)
	 * - the window doesn't overlap any other previous created windows (this->countRegisteredWindows > 0 AND this->checkWindow() is True)
	 * The Truth Table is (A = (this->countRegisteredWindows > 0), B = this->checkWindow(size,position))
	 *               A    B    |   OP
	 *              --------------------
	 *               V    V    |   F
	 *               V    F    |   V
	 *               F    V    |   V
	 *               F    F    |   V
	 *
	 *  The operation associated with that Truth Table is: !(A&&B)
	 */
	bool overlap {this->checkWindow(size,position)};
	bool count   {(this->countRegisteredWindows > 0) ? true : false};

	if(!(count && overlap))
	{
		this->windows[this->countRegisteredWindows] = new window(tft,size,position);
		this->countRegisteredWindows++;
	}
}
void windowManager::deregisterWindow(int id)
{
	delete this->windows[id];
	this->countRegisteredWindows--;
}
int windowManager::getWindowsCount()
{
	return this->countRegisteredWindows;
}
window* windowManager::getWindow(int i)
{
	return this->windows[i];
}

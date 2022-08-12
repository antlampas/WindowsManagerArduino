/*
 * windowManager.hpp
 *
 *  Created on: 9 ago 2022
 *  Author: Francesco Antonetti Lamorgese Passeri
 *  License: CC-BY-NC-SA 4.0 (https://creativecommons.org/licenses/by-nc-sa/4.0/)
 *  This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
 */

#ifndef WINDOWMANAGER_HPP_
#define WINDOWMANAGER_HPP_

#include "window.hpp"

#include "Arduino.h"

class windowManager
{
private:
	const int windowsNumber;
	int countRegisteredWindows;
	window **windows;
public:
	windowManager(const int);
	void    registerWindow(UTFT&,int*,int*);
	void    deregisterWindow(int);
	int     getWindowsCount();
	window* getWindow(int);
private:
	bool checkWindow(int*,int*);
	void checkLoop();
};

#endif /* WINDOWMANAGER_HPP_ */

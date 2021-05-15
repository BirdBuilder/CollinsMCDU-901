/*
 This file is part of Pi-XPlane-FMC-CDU
 A Raspberry Pi-based External FMC for XPlane

 Copyright (C) 2017-2018 shahada abubakar
 <shahada@abubakar.net>

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.
 
 ==================A word from the "modder"============================================
 This file is a modification of the original version by Shahada for use with
 a Rockwell Collins MCDU-901. I do not claim to have created this software nor
 do I intend to distribute the modified package. The likelyhood of this
 modified version being compatable with anything other than the "901" is zero.
 The sole purpose of the modification is to allow the MCDU-901's key matrix to
 work with the software. Tim.P 10/4/21
 ======================================================================================

 */


#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <wiringPi.h>

#include "FMCManager.h"

#include "Screen.h"
#include "KeypadScanner.h"

//Screen dimension constants
const int SCREEN_WIDTH = 600;	//was 640
const int SCREEN_HEIGHT = 480;	//was 480

using namespace std;


int main(int argc, char * argv[]) {

	syslog (LOG_INFO, "=== PiXPlaneFMCCDU is starting. ===");

	// initialize wiringPi
	wiringPiSetup ();

	// initialize
	FMCManager::getInstance();
	KeypadScanner::getInstance()->launchThread();

	// main SDL loop
	Screen::getInstance()->mainLoop();


	return 0;
}




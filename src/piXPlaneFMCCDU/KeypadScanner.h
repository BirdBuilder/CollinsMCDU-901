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

#ifndef PIXPLANEFMCCDU_SRC_KEYPADSCANNER_H_
#define PIXPLANEFMCCDU_SRC_KEYPADSCANNER_H_

#include <syslog.h>
#include <vector>
#include <stdlib.h>

class KeypadScanner {
private:
	KeypadScanner(); // private so it cannot be called

	KeypadScanner(KeypadScanner const &) {};

	KeypadScanner & operator=(KeypadScanner const &) {
		abort();
	}	 // assignment operator is private

protected:
	static KeypadScanner * instance;

	// columns are outputs. All are set to HIGH except the column being scanned.
	std::vector<int> columnPins = { 15, // Column 1 Raspberry pin 8	FMC Ribbon Pin 11
			16, // Column 2 Raspberry pin 10	FMC Ribbon Pin 13
			1, 	// Column 3 Raspberry pin 12	FMC Ribbon Pin 15
			4, 	// Column 4 Raspberry pin 16	FMC Ribbon Pin 17
			5, 	// Column 5 Raspberry pin 18	FMC Ribbon Pin 18
			6,	// Column 6 Raspberry pin 22	FMC Ribbon Pin 19
			10,	// Column 7 Raspberry pin 24	FMC Ribbon Pin 20
			11,	// Column 8 Raspberry pin 26	FMC Ribbon Pin 21
			27,	// Column 9 Raspberry pin 36	FMC Ribbon Pin 22
			28	// Column 10 Raspberry pin 38	FMC Ribbon Pin 23
			};

	// 	// rows are inputs.
	std::vector<int> rowPins = { 29,	//	Row 1 Raspberry pin 40	FMC Ribbon Pin 2
			8,	//	Row 2 Raspberry pin 3	FMC Ribbon Pin 4 (I2C SDA) (fixed pull-up)
			9,	// 	Row 3 Raspberry pin 5	FMC Ribbon Pin 6 (I2C SCL) (fixed pull-up)
			7,	// 	Row 4 Raspberry pin 7	FMC Ribbon Pin 8 (GPCLK0)
			0,	//	Row 5 Raspberry pin 11	FMC Ribbon Pin 10
			2, 	// 	Row 6 Raspberry pin 13	FMC Ribbon Pin 12
			3,	//	Row 7 Raspberry pin 15	FMC Ribbon Pin 14
			12	// 	Row 8 Raspberry pin 19	FMC Ribbon Pin 5(MOSI)
			};

	bool isRunning;
	bool stopRequested;

	unsigned int pressedRow;
	unsigned int pressedCol;
	bool somethingPressed;

public:

	static KeypadScanner * getInstance() {
		if (!instance) {
			syslog(LOG_INFO, "Intantiating KeypadScanner");
			instance = new KeypadScanner();
		}
		return instance;
	}

	void launchThread();
	void mainLoop();

	virtual ~KeypadScanner();

};

#endif /* PIXPLANEFMCCDU_SRC_KEYPADSCANNER_H_ */

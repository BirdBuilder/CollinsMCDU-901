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

#include <sstream>

#include "Screen.h"
#include "Version.h"

#include "SplashFMC.h"

using namespace std;

SplashFMC::SplashFMC() {
	numCols = 24;
}

SplashFMC::~SplashFMC() {

}

void SplashFMC::init() {

	Screen::getInstance()->initialize(numCols);

	Screen::getInstance()->clearScreen();

	drawCenteredText(0, "Collins MCDU-901");

	ostringstream buf;
	buf << "Ver " << MAJORVERSION << "." << MINORVERSION;
	drawCenteredText(3, buf.str());


	drawCenteredText(6, "Copyright (c) 2017-2018");
	drawCenteredText(7, "shahada abubakar");

	drawCenteredText (9, "Modified For.");
	drawCenteredText (10, "Collins MCDU-901");
	drawCenteredText (11, "By BirdBuilder");




}

void SplashFMC::deInit() {

}

void SplashFMC::receiveData(time_t time, std::string type, std::string dataref,
		std::string value) {

}

void SplashFMC::keyPressEvent(int row, int col) {

}

void SplashFMC::keyReleaseEvent(int row, int col) {

}

void SplashFMC::drawCenteredText(int line, std::string text) {

	int x = (numCols - text.length()) / 2;
	Screen::getInstance()->drawLine(x, line, text);

}

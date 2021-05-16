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

#include <iostream>
#include <regex>
#include <sstream>
#include <algorithm>

#include "ZiboFMC.h"
#include "Screen.h"
#include "FMCManager.h"
#include "LEDs.h"

using namespace std;

ZiboFMC::ZiboFMC(bool isCaptain) {

	side = isCaptain ? "1" : "2";

	// populate keyInfo [rows] [cols]
	keyInfo[3][7] = "laminar/B738/button/fmc" + side + "_1L";			// LSK1
	keyInfo[7][7] = "laminar/B738/button/fmc" + side + "_2L";			// LSK2
	keyInfo[6][7] = "laminar/B738/button/fmc" + side + "_3L"; 			// LSK3
	keyInfo[3][5] = "laminar/B738/button/fmc" + side + "_4L"; 			// LSK4
	keyInfo[7][5] = "laminar/B738/button/fmc" + side + "_5L"; 			// LSK5
	keyInfo[6][5] = "laminar/B738/button/fmc" + side + "_6L"; 			// LSK6
	keyInfo[3][2] = "laminar/B738/button/fmc" + side + "_1R"; 			// RSK1
	keyInfo[7][2] = "laminar/B738/button/fmc" + side + "_2R"; 			// RSK2 
	keyInfo[6][2] = "laminar/B738/button/fmc" + side + "_3R"; 			// RSK3
	keyInfo[3][1] = "laminar/B738/button/fmc" + side + "_4R";			// RSK4
	keyInfo[7][1] = "laminar/B738/button/fmc" + side + "_5R"; 			// RSK5 
	keyInfo[6][1] = "laminar/B738/button/fmc" + side + "_6R"; 			// RSK6
	keyInfo[3][9] = "laminar/B738/button/fmc" + side + "_init_ref"; 	// INIT REF
	keyInfo[7][9] = "laminar/B738/button/fmc" + side + "_rte";			// RTE
	keyInfo[8][6] = "laminar/B738/button/fmc" + side + "_clb"; 			// BRT
	keyInfo[8][7] = "laminar/B738/button/fmc" + side + "_crz";			// BLANK
	keyInfo[3][6] = "laminar/B738/button/fmc" + side + "_des";			// DIM
	keyInfo[4][2] = "laminar/B738/button/fmc" + side + "_menu";			// MENU
	keyInfo[6][9] = "laminar/B738/button/fmc" + side + "_legs"; 		// LEGS
	keyInfo[3][8] = "laminar/B738/button/fmc" + side + "_dep_app";		// DEP/ARR
	keyInfo[6][8] = "laminar/B738/button/fmc" + side + "_hold";			// HOLD
	keyInfo[3][4] = "laminar/B738/button/fmc" + side + "_prog";			// PROG
	keyInfo[3][3] = "laminar/B738/button/fmc" + side + "_exec";			// EXEC
	keyInfo[8][2] = "laminar/B738/button/fmc" + side + "_n1_lim"; 		// ATC
	keyInfo[6][6] = "laminar/B738/button/fmc" + side + "_fix";			// FIX
	keyInfo[8][9] = "laminar/B738/button/fmc" + side + "_prev_page";	// PRV
	keyInfo[8][8] = "laminar/B738/button/fmc" + side + "_next_page"; 	// NXT
	keyInfo[2][8] = "laminar/B738/button/fmc" + side + "_A";			// A
	keyInfo[2][10] = "laminar/B738/button/fmc" + side + "_B";			// B
	keyInfo[2][6] = "laminar/B738/button/fmc" + side + "_C";			// C
	keyInfo[2][4] = "laminar/B738/button/fmc" + side + "_D";			// D
	keyInfo[2][3] = "laminar/B738/button/fmc" + side + "_E";			// E
	keyInfo[2][2] = "laminar/B738/button/fmc" + side + "_F";			// F
	keyInfo[2][1] = "laminar/B738/button/fmc" + side + "_G";			// G
	keyInfo[1][8] = "laminar/B738/button/fmc" + side + "_H";			// H
	keyInfo[1][10] = "laminar/B738/button/fmc" + side + "_I";			// I
	keyInfo[1][6] = "laminar/B738/button/fmc" + side + "_J";			// J
	keyInfo[1][4] = "laminar/B738/button/fmc" + side + "_K";			// K
	keyInfo[1][3] = "laminar/B738/button/fmc" + side + "_L";			// L
	keyInfo[1][2] = "laminar/B738/button/fmc" + side + "_M";			// M
	keyInfo[1][1] = "laminar/B738/button/fmc" + side + "_N";			// N
	keyInfo[5][8] = "laminar/B738/button/fmc" + side + "_O";			// O
	keyInfo[5][10] = "laminar/B738/button/fmc" + side + "_P";			// P
	keyInfo[5][6] = "laminar/B738/button/fmc" + side + "_Q";			// Q
	keyInfo[5][4] = "laminar/B738/button/fmc" + side + "_R";			// R
	keyInfo[5][3] = "laminar/B738/button/fmc" + side + "_S";			// S
	keyInfo[5][2] = "laminar/B738/button/fmc" + side + "_T";			// T
	keyInfo[5][1] = "laminar/B738/button/fmc" + side + "_U";			// U
	keyInfo[4][8] = "laminar/B738/button/fmc" + side + "_V";			// V
	keyInfo[4][10] = "laminar/B738/button/fmc" + side + "_W";			// W
	keyInfo[4][6] = "laminar/B738/button/fmc" + side + "_X";			// X
	keyInfo[4][4] = "laminar/B738/button/fmc" + side + "_Y";			// Y
	keyInfo[4][3] = "laminar/B738/button/fmc" + side + "_Z";			// Z
	keyInfo[6][10] = "laminar/B738/button/fmc" + side + "_SP";			// SP
	keyInfo[7][6] = "laminar/B738/button/fmc" + side + "_del";			// DEL
	keyInfo[4][1] = "laminar/B738/button/fmc" + side + "_slash";		// /
	keyInfo[7][10] = "laminar/B738/button/fmc" + side + "_clr";			// CLR
	keyInfo[4][7] = "laminar/B738/button/fmc" + side + "_period";		// .
	keyInfo[4][5] = "laminar/B738/button/fmc" + side + "_0";			// 0
	keyInfo[4][9] = "laminar/B738/button/fmc" + side + "_minus";		// +/-
	keyInfo[5][7] = "laminar/B738/button/fmc" + side + "_7"; 			// 7
	keyInfo[5][5] = "laminar/B738/button/fmc" + side + "_8";			// 8
	keyInfo[5][9] = "laminar/B738/button/fmc" + side + "_9";			// 9
	keyInfo[1][7] = "laminar/B738/button/fmc" + side + "_4";			// 4
	keyInfo[1][5] = "laminar/B738/button/fmc" + side + "_5";			// 5
	keyInfo[1][9] = "laminar/B738/button/fmc" + side + "_6";			// 6
	keyInfo[2][7] = "laminar/B738/button/fmc" + side + "_1";			// 1
	keyInfo[2][5] = "laminar/B738/button/fmc" + side + "_2";			// 2
	keyInfo[2][9] = "laminar/B738/button/fmc" + side + "_3";			// 3

}

ZiboFMC::~ZiboFMC() {
	// TODO Auto-generated destructor stub
}

std::string ZiboFMC::getName() {

	return side == "1" ? "ZIB0" : "ZIB1";
}

void ZiboFMC::init() {

	Screen::getInstance()->initialize(24);
	Screen::getInstance()->clearScreen();
	LEDs::getInstance()->setAllLEDs(0);
	subscribeDataRefs();
}



void ZiboFMC::subscribe (std::string dataref) {

	FMCManager::getInstance()->subscribeDataRef (dataref);
	//xplaneUDPClient->subscribeDataRef(dataref+"[0][23]", 3);
}

void ZiboFMC::unsubscribe(std::string dataref) {

	FMCManager::getInstance()->unsubscribeDataRef(dataref);
}

void ZiboFMC::subscribeDataRefs() {

	// These are the datarefs that we need when we're active.

	// L = Large Lines, including Page Label (maps to even line numbers)
	// X = Small Lines (maps to odd line numbers)
	// S = small font on Large Lines

	subscribe("laminar/B738/fmc" + side + "/Line00_L");
	subscribe("laminar/B738/fmc" + side + "/Line00_S");

	subscribe("laminar/B738/fmc" + side + "/Line01_X");
	subscribe("laminar/B738/fmc" + side + "/Line02_X");
	subscribe("laminar/B738/fmc" + side + "/Line03_X");
	subscribe("laminar/B738/fmc" + side + "/Line04_X");
	subscribe("laminar/B738/fmc" + side + "/Line05_X");
	subscribe("laminar/B738/fmc" + side + "/Line06_X");

	subscribe("laminar/B738/fmc" + side + "/Line01_L");
	subscribe("laminar/B738/fmc" + side + "/Line02_L");
	subscribe("laminar/B738/fmc" + side + "/Line03_L");
	subscribe("laminar/B738/fmc" + side + "/Line04_L");
	subscribe("laminar/B738/fmc" + side + "/Line05_L");
	subscribe("laminar/B738/fmc" + side + "/Line06_L");

	subscribe("laminar/B738/fmc" + side + "/Line01_I");
	subscribe("laminar/B738/fmc" + side + "/Line02_I");
	subscribe("laminar/B738/fmc" + side + "/Line03_I");
	subscribe("laminar/B738/fmc" + side + "/Line04_I");
	subscribe("laminar/B738/fmc" + side + "/Line05_I");
	subscribe("laminar/B738/fmc" + side + "/Line06_I");

	subscribe("laminar/B738/fmc" + side + "/Line01_S");
	subscribe("laminar/B738/fmc" + side + "/Line02_S");
	subscribe("laminar/B738/fmc" + side + "/Line03_S");
	subscribe("laminar/B738/fmc" + side + "/Line04_S");
	subscribe("laminar/B738/fmc" + side + "/Line05_S");
	subscribe("laminar/B738/fmc" + side + "/Line06_S");

	subscribe("laminar/B738/fmc" + side + "/Line01_G");
	subscribe("laminar/B738/fmc" + side + "/Line02_G");
	subscribe("laminar/B738/fmc" + side + "/Line03_G");
	subscribe("laminar/B738/fmc" + side + "/Line04_G");
	subscribe("laminar/B738/fmc" + side + "/Line05_G");
	subscribe("laminar/B738/fmc" + side + "/Line06_G");

	subscribe("laminar/B738/fmc" + side + "/Line01_M");
	subscribe("laminar/B738/fmc" + side + "/Line02_M");
	subscribe("laminar/B738/fmc" + side + "/Line03_M");
	subscribe("laminar/B738/fmc" + side + "/Line04_M");
	subscribe("laminar/B738/fmc" + side + "/Line05_M");
	subscribe("laminar/B738/fmc" + side + "/Line06_M");
	subscribe("laminar/B738/fmc" + side + "/Line_entry");
	
	subscribe("laminar/B738/fmc/fmc_message");
	
	if (side=="1") {
		subscribe("laminar/B738/indicators/fmc_exec_lights");
	} else {
		subscribe("laminar/B738/indicators/fmc_exec_lights_fo");
	}


	// subscribe to datarefs for LEDs that Zibo738 supports
	//FMCManager::getInstance()->subscribeDataRef("laminar/B738/indicators/fmc_exec_lights", 1);
	//FMCManager::getInstance()->subscribeDataRef("laminar/B738/indicators/fmc_exec_lights_fo", 1);
	//FMCManager::getInstance()->subscribeDataRef("laminar/B738/indicators/fmc_message", 1);

}


void ZiboFMC::deInit () {


	unsubscribe("laminar/B738/fmc" + side + "/Line00_L");
	unsubscribe("laminar/B738/fmc" + side + "/Line00_S");

	unsubscribe("laminar/B738/fmc" + side + "/Line01_X");
	unsubscribe("laminar/B738/fmc" + side + "/Line02_X");
	unsubscribe("laminar/B738/fmc" + side + "/Line03_X");
	unsubscribe("laminar/B738/fmc" + side + "/Line04_X");
	unsubscribe("laminar/B738/fmc" + side + "/Line05_X");
	unsubscribe("laminar/B738/fmc" + side + "/Line06_X");

	unsubscribe("laminar/B738/fmc" + side + "/Line01_L");
	unsubscribe("laminar/B738/fmc" + side + "/Line02_L");
	unsubscribe("laminar/B738/fmc" + side + "/Line03_L");
	unsubscribe("laminar/B738/fmc" + side + "/Line04_L");
	unsubscribe("laminar/B738/fmc" + side + "/Line05_L");
	unsubscribe("laminar/B738/fmc" + side + "/Line06_L");
	unsubscribe("laminar/B738/fmc" + side + "/Line01_I");
	unsubscribe("laminar/B738/fmc" + side + "/Line02_I");
	unsubscribe("laminar/B738/fmc" + side + "/Line03_I");
	unsubscribe("laminar/B738/fmc" + side + "/Line04_I");
	unsubscribe("laminar/B738/fmc" + side + "/Line05_I");
	unsubscribe("laminar/B738/fmc" + side + "/Line06_I");
	unsubscribe("laminar/B738/fmc" + side + "/Line01_S");
	unsubscribe("laminar/B738/fmc" + side + "/Line02_S");
	unsubscribe("laminar/B738/fmc" + side + "/Line03_S");
	unsubscribe("laminar/B738/fmc" + side + "/Line04_S");
	unsubscribe("laminar/B738/fmc" + side + "/Line05_S");
	unsubscribe("laminar/B738/fmc" + side + "/Line06_S");
	unsubscribe("laminar/B738/fmc" + side + "/Line01_G");
	unsubscribe("laminar/B738/fmc" + side + "/Line02_G");
	unsubscribe("laminar/B738/fmc" + side + "/Line03_G");
	unsubscribe("laminar/B738/fmc" + side + "/Line04_G");
	unsubscribe("laminar/B738/fmc" + side + "/Line05_G");
	unsubscribe("laminar/B738/fmc" + side + "/Line06_G");
	unsubscribe("laminar/B738/fmc" + side + "/Line01_M");
	unsubscribe("laminar/B738/fmc" + side + "/Line02_M");
	unsubscribe("laminar/B738/fmc" + side + "/Line03_M");
	unsubscribe("laminar/B738/fmc" + side + "/Line04_M");
	unsubscribe("laminar/B738/fmc" + side + "/Line05_M");
	unsubscribe("laminar/B738/fmc" + side + "/Line06_M");
	
	unsubscribe("laminar/B738/fmc/fmc_message");
	
	if (side=="1") {
		unsubscribe("laminar/B738/indicators/fmc_exec_lights");
	} else {
		unsubscribe("laminar/B738/indicators/fmc_exec_lights_fo");
	}


	// unsubscribe to datarefs for LEDs that Zibo738 supports
	//FMCManager::getInstance()->unsubscribeDataRef("laminar/B738/indicators/fmc_exec_lights");
	//FMCManager::getInstance()->unsubscribeDataRef("laminar/B738/indicators/fmc_exec_lights_fo");
	//FMCManager::getInstance()->unsubscribeDataRef("laminar/B738/indicators/fmc_message");

}

void ZiboFMC::keyPressEvent(int row, int col) {
	auto rowV = keyInfo.find(row);
	if (rowV == keyInfo.end()) {
		cerr << "Invalid row " << row << endl;
		return;
	}

	auto colV = rowV->second.find(col);
	if (colV == rowV->second.end()) {
		cerr << "Invalid col " << col << endl;
		return;
	}

	cerr << "zibo keypress on r=" << rowV->first << " c=" << colV->first
			<< " \"" << colV->second << "\"" << endl;

	FMCManager::getInstance()->sendCommand(colV->second);
}

void ZiboFMC::keyReleaseEvent(int row, int col) {

	// do nothing?
}


void ZiboFMC::receiveDataRef(std::string type, std::string dataref,
		std::string value) {

	ostringstream buf;
	buf << "ZiboFMC got [" << dataref << "|" << value << "]" << endl;
	cerr << buf.str() << endl;
	syslog (LOG_INFO, "%s", buf.str().c_str());


	regex r("^laminar/B738/fmc" + side + "/Line(\\d+)_(.)$");
	smatch m;
	if (regex_match(dataref, m, r)) {

		int line = stoi(m[1]);
		string size = m[2];

		// zibo uses '*' for the square entry box. we don't have that
		// so we use '_' instead.
		replace (value.begin(), value.end(), '*', '_');

		/* Zibo has a number of datarefs that apply to every line.
		 * 	X=Small Lines
		 * 	L=Large
		 * 	-->G=Green Text in Large Lines
		 * 	-->M=Magenta Text in Large Lines
		 * 	-->I=Inverse Text in Large Lines
		 * 	-->S=Small Text in Large Lines
		 */

		// normal large lines
		if (size == "L") {
			line = (line) * 2;
			// zibo sends " " when it means clear the entire line
			value.resize(24, ' ');
			Screen::getInstance()->drawLine(0, line, value);
		}

		// normal small lines
		else if (size == "X") {
			line = 1 + ((line - 1) * 2);
			// zibo sends " " when it means clear the entire line
			value.resize(24, ' ');
			Screen::getInstance()->drawLine(0, line, value);
		}

		// overlay small font in large line overlay
		else if (size == "S") {
			line = (line) * 2;
			Screen::getInstance()->drawLine(0, line, value, false);
		}

		// overlay magenta font in large line
		else if (size == "M") {
			line = (line) * 2;
			Screen::getInstance()->drawLine(0, line, value, false, 'M');
		}

		// overlay green font in large line
		else if (size == "G") {
			line = (line) * 2;
			Screen::getInstance()->drawLine(0, line, value, false, 'G');
		}

	}

	else if (dataref == "laminar/B738/fmc" + side + "/Line_entry") {
		value.resize(24, ' ');
		Screen::getInstance()->drawLine (0, 13, value);
		cerr << "Line_entry [" << value << "]" << endl;

	}

	else if (dataref == "laminar/B738/indicators/fmc_exec_lights" || dataref == "laminar/B738/indicators/fmc_exec_lights_fo") {
		LEDs::getInstance()->setLED(LEDs::LED_EXEC, value == "1");
	}

	else if (dataref == "laminar/B738/indicators/fmc_message") {
		LEDs::getInstance()->setLED(LEDs::LED_MSG, value == "1");
	}

}


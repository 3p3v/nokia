/*
 * Process.cpp
 *
 *  Created on: 21 gru 2021
 *      Author: ADAM
 */

#include "Process.h"

Process::Process(int x, int y, int p, int z) {
	PID = p;
	a = x;
	s = y;
	prior = z;
	t = 0;
	st = 0;
	ft = 0;
	priorcounter = 0;
}

Alghoritm::Alghoritm(std::vector<Process>processes) {
	this->processes = processes;
	trn = 0;
	symended = false;
	wait = true;
}

Alghoritm::~Alghoritm() {
	for(int i = 0; i < ended.size(); i++){
		//delete ended.at(0);
	}
}

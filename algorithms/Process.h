/*
 * Process.h
 *
 *  Created on: 21 gru 2021
 *      Author: ADAM
 */

#ifndef PROCESS_H_
#define PROCESS_H_
#include <iostream>
#include <vector>
#include <tgmath.h>
#include <iostream>

class Process final {

public:
	int PID;
	int a;//CZAS WEJSCIA W KOLEJKE READY
	int s;//BURST TIME
	int prior;//PRIORYTET
	int priorcounter;//
	int t;//CZAS CZEKANIA
	int ft;//FINISH
	int st;//START

	Process(int x, int y, int p, int z);
};

class Alghoritm {
public:
	bool symended;
	bool wait;
	int trn;
	std::vector<Process>processes;
	std::vector<Process>ended;
	virtual void alg() = 0;
	virtual float t_mean() = 0;
	virtual float ta_mean(std::vector<Process>) = 0;

	Alghoritm(std::vector<Process>&);
	virtual ~Alghoritm();
};

#endif /* PROCESS_H_ */

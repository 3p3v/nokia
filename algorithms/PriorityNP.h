/*
 * PriorityNP.h
 *
 *  Created on: 3 sty 2022
 *      Author: ADAM
 */

#ifndef ALGORITHMS_PRIORITYNP_H_
#define ALGORITHMS_PRIORITYNP_H_
#include "Process.h"

class PriorityNP final : public Alghoritm{
public:
	int pchange;
	std::vector<Process>processes2;
	void alg();
	float t_mean();
	float ta_mean(std::vector<Process>);
	PriorityNP(std::vector<Process>, int);
};

#endif /* ALGORITHMS_PRIORITYNP_H_ */

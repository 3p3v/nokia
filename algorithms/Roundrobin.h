/*
 * Roundrobin.h
 *
 *  Created on: 25 gru 2021
 *      Author: ADAM
 */

#ifndef ALGORITHMS_ROUNDROBIN_H_
#define ALGORITHMS_ROUNDROBIN_H_
#include "Process.h"

class Roundrobin final : public Alghoritm {
public:
	int quant;
	std::vector<Process>processes2;
	Roundrobin(std::vector<Process>, int);
	void alg();
	float t_mean();
	float ta_mean(std::vector<Process> processes);
};

#endif /* ALGORITHMS_ROUNDROBIN_H_ */

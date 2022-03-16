/*
 * Fcfs.h
 *
 *  Created on: 21 gru 2021
 *      Author: ADAM
 */

#ifndef FCFS_H_
#define FCFS_H_
#include "Process.h"

class Fcfs final : public Alghoritm {
public:
	Fcfs(std::vector<Process>);
	void alg();
	float t_mean();
	float ta_mean(std::vector<Process>);
};

#endif /* FCFS_H_ */

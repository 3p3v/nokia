/*
 * Fcfs.cpp
 *
 *  Created on: 21 gru 2021
 *      Author: ADAM
 */

#include "Fcfs.h"

Fcfs::Fcfs(std::vector<Process>processes)
	: Alghoritm(processes){}

void Fcfs::alg()
{
	while(processes.size() > 1 )
	{
		//std::cin.ignore();
		while(wait == true)
		{

		}
		wait = true;

		//////////////////////WYBIERANIE NAJMNIEJSZEGO///////////////////////
		int index = 0;
		for(int i = 0; i < processes.size()-1; i++)
		{
			if(processes.at(index).a > processes.at(i+1).a)
				index = i + 1;
		}

		//////////////////////CZAS JESLI BRAK PROCESU PO ZAKONCZNIU WCZESNIEJSZEGO///////////////////////
		if(trn < processes.at(index).a)
			trn += processes.at(index).a - trn;

		/////////////////////////START/////////////////////////
		processes.at(index).st = trn;

		//////////////////////////CZAS PO ZAKONCZENIU PROCESU//////////////////////////////
		trn += processes.at(index).s;

		////////////////////////FINISH/////////////////////////
		processes.at(index).ft = trn;

		/////////////////PRZENOSZENIE PROCESU DO KOLEJKI ZAKONCZONYCH///////////////////////
		processes.at(index).s = 0;
		ended.push_back(processes.at(index));
		processes.erase(processes.begin() + index);

		/////////////////////ZAKTUALIZOWANIE CZASU OCZEKIWANIA t WSZYSTKICH PROCESOW//////////////////////////
		for(int i = 0; i < processes.size(); i++)
		{
			if(processes.at(i).a < trn)
				processes.at(i).t = trn - processes.at(i).a;
		}
	}

	//std::cin.ignore();
	while(wait == true)
	{

	}
	wait = true;
	///////////////////OBSLUGA OSTATNIEGO PROCESU//////////////////////////
	if(trn < processes.back().a)
		trn += processes.back().a - trn;

	/////////////////////////START/////////////////////////
	processes.at(0).st = trn;

	//////////////////////////CZAS PO ZAKONCZENIU PROCESU//////////////////////////////
	trn += processes.at(0).s;

	////////////////////////FINISH/////////////////////////
	processes.at(0).ft = trn;

	/////////////////PRZENOSZENIE PROCESU DO KOLEJKI ZAKONCZONYCH///////////////////////
	processes.at(0).s = 0;
	ended.push_back(processes.at(0));
	processes.erase(processes.begin());
	symended = true;
}

float Fcfs::t_mean()
{
	int sum = 0;
	for(int i = 0; i < ended.size(); i++)
		sum += ended.at(i).t;

	float result = static_cast<float>(sum) / static_cast<float>(ended.size());
	return result;
}

float Fcfs::ta_mean(std::vector<Process> processes)
{
	int sum = 0;

	for(int i = 0; i < ended.size(); i++)
		sum += ended.at(i).t + processes.at(i).s;

	float result = static_cast<float>(sum) / static_cast<float>(ended.size());
	return result;
}




/*
 * PriorityNP.cpp
 *
 *  Created on: 3 sty 2022
 *      Author: ADAM
 */

//ZMIENIONY KONSTRUKTOR ORAZ PETLE

#include "PriorityNP.h"

PriorityNP::PriorityNP(std::vector<Process>processes, int pc)
	: Alghoritm(processes), pchange(pc) {}

void PriorityNP::alg()
{
	/////////////////////SORTOWANIE//////////////////
	for(int i = 0; i < processes.size(); i++)
	{
		for(int j = 0; j < processes.size(); j++)
		{
			if(processes.at(i).a == processes.at(j).a)
			{
				if(processes.at(i).prior < processes.at(j).prior)
				{
					std::iter_swap(processes.begin() + i, processes.begin()+j);
				}
				else if(processes.at(i).PID < processes.at(j).PID)
				{
					std::iter_swap(processes.begin() + i, processes.begin()+j);
				}
			}
			else if(processes.at(i).a < processes.at(j).a)
			{
				std::iter_swap(processes.begin() + i, processes.begin()+j);
			}
		}
	}

	while(!processes.empty() || !processes2.empty())
	{
		if(!processes2.empty())
		{
			while(wait == true)
			{

			}
			wait = true;

			////////////////SORTOWANIE: Pmin -> Pmax//////////////
			for(int i = 0; i < processes2.size(); i++)
			{
				for(int j = i; j < processes2.size(); j++)//zmiana
				{
					if(processes2.at(i).prior == processes2.at(j).prior)
					{
						//std::cout << "error::" << processes2.at(i).prior << processes2.at(j).prior << std::endl;
						if(processes2.at(i).PID > processes2.at(j).PID)//zmiana
						{
							std::iter_swap(processes2.begin() + i, processes2.begin()+j);
						}
					}
					else if(processes2.at(i).prior > processes2.at(j).prior)//zmiana!!
					{
						//std::cout << "called\n";
						std::iter_swap(processes2.begin() + i, processes2.begin()+j);
					}
				}
			}

			//////////////////////CZAS JESLI BRAK PROCESU PO ZAKONCZNIU WCZESNIEJSZEGO///////////////////////
			if(trn < processes2.at(0).a)
				trn += processes2.at(0).a - trn;

			/////////////////////////START/////////////////////////
			processes2.at(0).st = trn;

			//////////////////////////CZAS PO ZAKONCZENIU PROCESU//////////////////////////////
			trn += processes2.at(0).s;

			////////////////////////FINISH/////////////////////////
			processes2.at(0).ft = trn;

			/////////////////PRZENOSZENIE PROCESU DO KOLEJKI ZAKONCZONYCH///////////////////////
			processes2.at(0).s = 0;
			ended.push_back(processes2.at(0));
			processes2.erase(processes2.begin() + 0);

			///////////////////CZY NOWY POJAWIL SIE///////////////
			for(int i = 0; i < processes.size(); i++)
			{
				if(processes.at(i).a <= trn)
				{
					processes2.push_back(processes.at(i));
					processes.erase(processes.begin()+i);
					i--;
				}
			}
			////////////////ZAKTUALIZOWANIE PRIORYTETU////////////
			for(int i = 0; i < processes2.size(); i++)
			{
				if(processes2.at(i).prior > 0)
				{
					int priorcounter = processes2.at(i).priorcounter + trn - processes2.at(i).a - processes2.at(i).t;
					int counter = floor(priorcounter / pchange);
					if((processes2.at(i).prior - counter) >= 0)
					{
						processes2.at(i).prior -= counter;
					}
					else
					{
						processes2.at(i).prior = 0;
					}
					processes2.at(i).priorcounter = priorcounter - (counter * pchange);
				}
			}

			/////////////////////ZAKTUALIZOWANIE CZASU OCZEKIWANIA t WSZYSTKICH PROCESOW//////////////////////////
			for(int i = 0; i < processes2.size(); i++)
			{
				processes2.at(i).t = trn - processes2.at(i).a;
			}

		}
		else
		{

			processes2.push_back(processes.at(0));
			processes.erase(processes.begin());
		}


	}
	symended = true;
}

float PriorityNP::t_mean()
{
	int sum = 0;
	for(int i = 0; i < ended.size(); i++)
		sum += ended.at(i).t;

	float result = static_cast<float>(sum) / static_cast<float>(ended.size());
	return result;
}

float PriorityNP::ta_mean(std::vector<Process> processes)
{
	int sum = 0;
	for(int i = 0; i < ended.size(); i++)
		sum += ended.at(i).t + processes.at(i).s;

	float result = static_cast<float>(sum) / static_cast<float>(ended.size());
	return result;
}


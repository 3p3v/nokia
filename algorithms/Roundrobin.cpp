/*
 * roundrobin.cpp
 *
 *  Created on: 25 gru 2021
 *      Author: ADAM
 */

#include "Roundrobin.h"

Roundrobin::Roundrobin(std::vector<Process>processes, int q)
	: Alghoritm(processes) {
	quant = q;
}


void Roundrobin::alg()
{
	/////////////////////SORTOWANIE//////////////////
	for(int i = 0; i < processes.size(); i++)
	{
		for(int j = 0; j < processes.size(); j++)
		{
			if(processes.at(i).a == processes.at(j).a)
			{
				if(processes.at(i).PID < processes.at(j).PID)
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

	while(processes.size() > 0 || processes2.size() > 0)
	{
		if(processes2.size() > 0)
		{
			while(wait == true)
			{

			}
			wait = true;

			///////////////START//////////////
			processes2.at(0).st = trn;

			if(processes2.at(0).s < quant)
			{
				trn += processes2.at(0).s;
				processes2.at(0).s = 0;
			}
			else
			{
				trn += quant;
				processes2.at(0).s -= quant;
			}

			//////////////FINISH////////////
			processes2.at(0).ft = trn;

			/////////////////PRZENOSZENIE PROCESU DO KOLEJKI ZAKONCZONYCH///////////////////////
			ended.push_back(processes2.at(0));

			///////////////////CZY NOWY POJAWIL SIE///////////////
			int counter = 0;
			for(int i = 0; i < processes.size(); i++)
			{
				if(processes.size() > 0)
				{
					if(processes.at(i).a <= trn)
					{
						processes2.push_back(processes.at(i));
						processes.erase(processes.begin()+i);
						i--;
						counter++;
					}
				}
			}

			/////////////////////ZAKTUALIZOWANIE CZASU OCZEKIWANIA t WSZYSTKICH PROCESOW//////////////////////////
			for(int j = 1; j < processes2.size(); j++)
			{
				//albo .ft==0 albo .ft!=0
				if(j >= processes2.size() - counter)
					processes2.at(j).t += processes2.at(0).ft - processes2.at(j).a;
				else
					processes2.at(j).t += processes2.at(0).ft - processes2.at(0).st;
			}

			/////////////////////NA KONIEC KOLEJKI//////////////////
			processes2.push_back(processes2.at(0));
			processes2.erase(processes2.begin()+0);

			/////////////USUWANIE JESLI ZAKONCZONY/////////////////
			if(processes2.back().s <= 0)
			{
				processes2.erase(processes2.begin() + processes2.size() - 1);
			}

		}
		else
		{
			processes2.push_back(processes.at(0));
			processes.erase(processes.begin());
			trn = processes2.at(0).a;
		}
	}
	symended = true;
}

float Roundrobin::t_mean()
{
	int sum = 0;
	int size = 0;
	for(int i = 0; i < ended.size(); i++)
	{
		if(ended.at(i).s == 0)
		{
			sum += ended.at(i).t;
			size++;
		}
	}


	float result = static_cast<float>(sum) / static_cast<float>(size);
	return result;
}

float Roundrobin::ta_mean(std::vector<Process> processes)
{
	int sum = 0;
	int size = 0;
	for(int i = 0; i < ended.size(); i++)
	{
		if(ended.at(i).s == 0)
		{
			sum += ended.at(i).t;
			size++;
		}
	}

	for(int i = 0; i < processes.size(); i++)
		sum += processes.at(i).s;

	float result = static_cast<float>(sum) / static_cast<float>(size);
	return result;
}


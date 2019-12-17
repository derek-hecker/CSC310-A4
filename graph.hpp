#pragma once
#include <cstddef>
#include <iostream>
#include <iomanip>
using namespace std;
#define SIZE 200
struct times
{
	int key;
	int dpt_time;
	int arvl_time;
	int delta_time;
};

class graph
{
public:
	graph();
	void add(int src, int dst, int weight, int time);
	void print_all(int station_count);
	void print_station_schedule(int id);
	bool non_stop_service_available(int src_id, int dst_id);
	bool service_available(int src_id, int dst_id);


private:
	times matrix[SIZE][SIZE];

};

graph::graph()
{
	//create an array of integer pointers, this takes care of
	//the first pointer in our double pointer
	//matrix = new int*[SIZE];
	//for each index in that array create an array of plain
	//integers, not pointers to integers
	//for(int i=0;i<SIZE;i++)
	//	matrix[i] = new int[SIZE];

	//initialize all of the elements in our matrix to 0
	for (int i = 0; i < SIZE; i++)
	{
		for (int x = 0; x < SIZE; x++)
		{
			matrix[i][x].key = 0;
			matrix[i][x].dpt_time = 0;
			matrix[i][x].arvl_time = 0;
			matrix[i][x].delta_time = 0;

		}
	}
}

void graph::add(int src, int dst, int dpt_time, int arvl_time)
{
	//set our edge
	matrix[src][dst].dpt_time = dpt_time;
	matrix[src][dst].arvl_time = arvl_time;
	matrix[src][dst].delta_time = (arvl_time - dpt_time);
	matrix[src][dst].key = 1;

}

void graph::print_all(int station_count)
{
	for (int i = 0; i <= station_count; i++)
	{
		for (int j = 0; j <= station_count; j++)
		{
			if (matrix[i][j].key == 1)
			{
				cout << "Departing from station " << i << " at " << matrix[i][j].dpt_time << " arriving to station " << j << " at " << matrix[i][j].arvl_time << endl;
			}
		}
	}

}
void graph::print_station_schedule(int id)
{
	for (int i = 0; i <= SIZE; i++)
	{
		if (matrix[id][i].key == 1)
		{
			cout << "Departing from station " << id << " at " << matrix[id][i].dpt_time << " arriving to station " << i << " at " << matrix[id][i].arvl_time << endl;
		}
	}
	for (int i = 0; i <= SIZE; i++)
	{
		if (matrix[i][id].key == 1)
		{
			cout << "Departing from station " << i << " at " << matrix[i][id].dpt_time << " arriving to station " << id << " at " << matrix[i][id].arvl_time << endl;
		}
	}
}
bool graph::non_stop_service_available(int src_id, int dst_id)
{
	if (matrix[src_id][dst_id].key == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool graph::service_available(int src_id, int dst_id)
{

}
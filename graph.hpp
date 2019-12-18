#pragma once
#include <cstddef>
#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <math.h>
using namespace std;
#define SIZE 200
#define INF 9999999
struct times
{
	int key;		   // 1 or zero value based on if there is an edge
	int dpt_time;	  //departure time
	int arvl_time;	 //arrival time
	float delta_time; //time on train
};

class graph
{
public:
	graph();
	void add(int src, int dst, int weight, int time);
	void print_all(int station_count);
	void print_station_schedule(int id);
	bool non_stop_service_available(int src_id, int dst_id);
	void service_available(int src_id, int dst_id, int station_count);
	bool empty(vector<bool> set);
	void dijikstra(int src, int dest, int station_count);

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
	float time1 = dpt_time;
	float time2 =  arvl_time;
	float minutes1, minutes2, hour1, hour2;
	minutes1 = fmod(time1, 100);
	minutes2 = fmod(time2, 100);
	hour1 = time1 - minutes1;
	hour2 = time2 - minutes2;
	hour1 = hour1 / 100;
	hour2 = hour2 / 100;
	minutes1 = minutes1 / 100;
	minutes2 = minutes2 / 100;
	time1 = hour1 + minutes1;
	time2 = hour2 + minutes2;
	matrix[src][dst].delta_time = time2 - time1;
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

void graph::service_available(int src, int dest, int station_count)
{
	vector<bool> vertexSet;
	float distances[station_count];
	int minNode;
	int minDistance;

	for (int i = 0; i <= station_count; i++)
	{
		distances[i] = INF;
		vertexSet.push_back(false);
	}

	distances[src] = 0;

	while (!empty(vertexSet))
	{
		minNode = INF;
		minDistance = INF;
		for (int vert = 0; vert <= station_count; vert++)
		{
			if (vertexSet[vert] == false && distances[vert] <= minDistance)
			{
				minDistance = distances[vert];
				minNode = vert;
			}
		}
		vertexSet[minNode] = true;
		for (int vert = 0; vert <= station_count; vert++)
		{
			if (vertexSet[vert] == false && matrix[minNode][vert].key == 1)
			{
				if ((distances[minNode] != INF && distances[minNode] + matrix[minNode][vert].delta_time) < distances[vert])
				{
					
					distances[vert] = distances[minNode] + matrix[minNode][vert].delta_time;
				}
			}
		}
	}
	if (distances[dest] == INF)
	{
		cout << "There is no available route from station " << src << " to station " << dest << endl;
	}
	else
	{
		cout << "Service is available from station " << src << " to station " << dest << endl;
	}
}


bool graph::empty(vector<bool> set)
{
	for (int i = 0; i < set.size(); i++)
	{
		if (set[i] == false)
		{
			return false;
		}
	}
	return true;
}

void graph::dijikstra(int src, int dest, int station_count)
{
	vector<bool> vertexSet;
	float distances[station_count];
	int minNode;
	int minDistance;

	for (int i = 0; i <= station_count; i++)
	{
		distances[i] = INF;
		vertexSet.push_back(false);
	}

	distances[src] = 0;

	while (!empty(vertexSet))
	{
		minNode = INF;
		minDistance = INF;
		for (int vert = 0; vert <= station_count; vert++)
		{
			if (vertexSet[vert] == false && distances[vert] <= minDistance)
			{
				minDistance = distances[vert];
				minNode = vert;
			}
		}
		vertexSet[minNode] = true;
		for (int vert = 0; vert <= station_count; vert++)
		{
			if (vertexSet[vert] == false && matrix[minNode][vert].key == 1)
			{
				if ((distances[minNode] != INF && distances[minNode] + matrix[minNode][vert].delta_time) < distances[vert])
				{
					//if (matrix[minNode][vert].dpt_time > matrix[vert][minNode].arvl_time)
					distances[vert] = distances[minNode] + matrix[minNode][vert].delta_time;
				}
			}
		}
	}
	if (distances[dest] == INF)
	{
		cout << "There is no available route from station " << src << " to station " << dest << endl;
	}
	else
	{
		cout << "Distance from station " << src << " to station " << dest << " is " << distances[dest] * 100 << endl;
	}
}
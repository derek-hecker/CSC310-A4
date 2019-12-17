#include <fstream>  // Include to open files
#include <cstddef>  // Include to use NULL, otherwise use nullptr
#include <iostream> // Include to print to the screen
#include <iomanip>
#include "graph.hpp"
#include "station.hpp"
#define SIZE 200
using namespace std;
station stationlist[SIZE];
graph adjacency_matrix;


string lookup_station_by_id(int id, int number)
{
    string name;
    for (int i = i; i <= number ; i++){
        if (stationlist[i].station_id == id){
            return stationlist[i].station_name;
        }
    }
    return "\0";
}
int lookup_station_by_name(string st_name, int number){
    int id = 0;
    for (int i = 0; i <= number; i++){
        if (stationlist[i].station_name == st_name){
            return stationlist[i].station_id;
        }
    }
    return 0;
}
int main(int argc, char **argv)
{

    std::fstream input;
    int src_station, dst_station, dpt_time, arvl_time, station_input, ret, station_in;
    string name;

    if (argc < 3)
    {
        cout << "useage: ./graph.out <stations.dat><trains.dat>\n";
        return 0;
    }

    //Create Struture for holding station name and ids
    int station_counter = 0;

    for (int i = 0; i < SIZE; i++)
    {
        stationlist[i].station_id = 0;
        stationlist[i].station_name = '\0';
    }
    //open stations.dat file
    input.open(argv[1]);
    while (input >> station_input)
    {
        input >> name;
        stationlist[station_counter].station_id = station_input;

        stationlist[station_counter].station_name = name;
        station_counter++;
    }
    input.close();
    input.open(argv[2]);
    while (input >> src_station){
        input >> dst_station;
        input >> dpt_time;
        input >> arvl_time;
        adjacency_matrix.add(src_station, dst_station, dpt_time, arvl_time);
    }

    int choice = 0;
    //print menu options
    cout << "============================================================" << endl;
    cout << "Reading Railways Scheduler" << endl;
    cout << "============================================================" << endl;
    cout << "Options: Enter the number of your selected option" << endl;
    cout << "(1) - Print full schedule" << endl;
    cout << "(2) - Print station schedule" << endl;
    cout << "(3) - Look up station id" << endl;
    cout << "(4) - Look up station name" << endl;
    cout << "(5) - Service available" << endl;
    cout << "(6) - Nonstop service available" << endl;
    cout << "(7) - Find route (Shortest riding time)" << endl;
    cout << "(8) - Find route (Shortest overall travel time)" << endl;
    cout << "(9) - Exit" << endl;
    while (choice != 9)
    {
        //Menu Loop
        cout << "Enter Option: ";
        cin >> choice;
        cout << endl;
        //Program Driver if branches
        if (choice == 1)
        {
           adjacency_matrix.print_all(station_counter);
        }
        else if (choice == 2)
        {
            int stid;
            cout << "Enter the id of the station you would like to see the schedule of: ";
            cin >> stid;
            adjacency_matrix.print_station_schedule(stid);

        }
        else if (choice == 3)
        {
            string searching_name;
            cout << "Enter the name of the station: ";
            cin >> searching_name;
            cout << endl;
            int searched_id = 0;
            searched_id = lookup_station_by_name(searching_name, station_counter);
            if (searched_id == 0){
                cout << "Station does not exist";
            } else {
                cout << "The station id for " << searching_name << " is " << searched_id << endl;
            }
        }
        else if (choice == 4)
        {
            int id = 0;
            cout << "Enter the station id: ";
            cin >> id;
            cout << endl;
            string searched_name;
            searched_name = lookup_station_by_id(id, station_counter);
            if (searched_name == "\0"){
                cout << "Station does not exist" << endl;
            } else {
                cout << "The station name for id=" << id << " is " << searched_name << endl;
            }
        }
        else if (choice == 5)
        {

        }
        else if (choice == 6)
        {
            bool non_stop_service;
            int src, dst;
            cout << "Enter departing station: ";
            cin >> src;
            cout << endl;
            cout << "Enter destination station: ";
            cin >> dst;
            cout << endl;
            non_stop_service = adjacency_matrix.non_stop_service_available(src, dst);
            string station1 = lookup_station_by_id(src, station_counter);
            string station2 = lookup_station_by_id(dst, station_counter);
            if (non_stop_service){
                cout << "Non-stop Service is available from " << station1  << " to " << station2  << endl;
            } else {
                cout << "Service is not available or incorrect station ids were entered" << endl;
            }
        }
        else if (choice == 7)
        {

        }
        else if (choice == 8)
        {
        }
        else if (choice == 9)
        {
            exit;
        }
        else
        {
            cout << "Option entered is invalid, please enter a number between 1 and 9" << endl;
            continue;
        }
    
    }
    return 0;
}

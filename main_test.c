#include <stdio.h>
#include "include/base_functions.h"

#define FILEPATH "data/merged_everything.csv"
#define MAX_POINTS 3440 // total number of records in FILEPATH
					 	// change to 3440

int main(int argc, char* argv[]) {

		if(argc < 5){
		printf("Invalid arguments.\n");
		return 1;
	}
		
	double lat1 = atof(argv[1]);
	//printf("lat1: %lf", lat1);
	if(lat1 < START_LAT || lat1 > END_LAT){
		printf("Point out of bounds.\n");
		return 1;
	}
	double long1 = atof(argv[2]);
	//printf("long1: %lf", long1);
	if(long1 < START_LON || long1 > END_LON){
		printf("Point out of bounds.\n");
		return 1;
	}
	double lat2 = atof(argv[3]);
	//printf("lat2: %lf", lat2);
	if(lat2 < START_LAT || lat2 > END_LAT){
		printf("Point out of bounds.\n");
		return 1;
	}
	double long2 = atof(argv[4]);
	//printf("long2: %lf", long2);
	if(long2 < START_LON || long2 > END_LON){
		printf("Point out of bounds.\n");
		return 1;
	}


	// INITIALIZE GRAPH
	Graph g;
	initialize(&g, MAX_POINTS);

	// CREATE GRAPH
	readPointsFromCSV(FILEPATH, &g);

	int start_index = calculate_index(lat1, long1);
	//printf("%d start index\n", start_index);
	int end_index = calculate_index(lat2, long2);

	//printf("in main test\n");

	if(isNull(g.adjList[start_index])){
		printf("Starting point is on land.\n");
		return 1;
	}

	if(isNull(g.adjList[end_index])){
		printf("Ending point is on land.\n");
		return 1;
	}	
	
	initEdges(&g);
	//printGraph(&g);
	
	/*for (int i = 0; i < 1000; i++) {
		printPoint(g.adjList[i], i);
	}*/






	a_star(&g, start_index, end_index);
	return 0;
	
}


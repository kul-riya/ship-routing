#include <stdio.h>
#include "include/base_functions.h"

#define FILEPATH "data/merged_everything.csv"
#define MAX_POINTS 5 // total number of records in FILEPATH

int main() {
	// INITIALIZE GRAPH
	Graph g;
	initialize(&g, MAX_POINTS);

	// CREATE GRAPH
	readPointsFromCSV(FILEPATH, &g);
	printGraph(&g);

	return 0;
	
}


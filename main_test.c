#include <stdio.h>
#include "include/base_functions.h"

#define FILEPATH "data/merged_everything.csv"
#define MAX_POINTS 3440 // total number of records in FILEPATH
					 	// change to 3440

int main() {
	// INITIALIZE GRAPH
	Graph g;
	initialize(&g, MAX_POINTS);

	// CREATE GRAPH
	readPointsFromCSV(FILEPATH, &g);
	initEdges(&g);
	//printGraph(&g);
	
	//for (int i = 0; i < 1000; i++) {
		//printPoint(g.adjList[i], i);
	//}
/*	for (int i = 45; i < 50; i++) {
		printPoint(g.adjList[i], i);
	}

	for (int i = 3430; i < 3440; i++) {
		printPoint(g.adjList[i], i);
	}
*/

	a_star(&g, 21, 233);
	return 0;
	
}


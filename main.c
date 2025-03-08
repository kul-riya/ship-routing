#include <stdio.h>
#include "include/base_functions.h"
#include <ncurses.h>

#define FILEPATH "data/merged_everything.csv"
#define MAX_POINTS 3440 // total number of records in FILEPATH
					 	// change to 3440

// Function to display the path and coordinates in ncurses window
void display_path_in_ncurses(int *prev, double top, double left, double bottom, double right, Graph *g, int startIndex, int endIndex) {
	initscr();              // Initialize ncurses
    raw();                  // Disable line buffering
    keypad(stdscr, TRUE);   // Enable special keys
    noecho();               // Disable echoing of characters


    int height = 80;        // Grid height
    int width = 43;         // Grid width
    char grid[height][width];
	Point** points = g->adjList;

    // Fill the grid with empty spaces
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            grid[y][x] = '.';
        }
    }

    // Plot path points on the grid
    int current = endIndex;
    while (current != startIndex) {
        int x = (int)((points[current]->longitude - left) / (right - left) * (width - 1));
        int y = (int)((top - points[current]->latitude) / (top - bottom) * (height - 1));

        if (x >= 0 && x < width && y >= 0 && y < height) {
            grid[y][x] = 'X'; // Mark path with '*'
        }

        current = prev[current];
    }
    int x = (int)((points[current]->longitude - left) / (right - left) * (width - 1));
    int y = (int)((top - points[current]->latitude) / (top - bottom) * (height - 1));
    grid[y][x] = 'X'; // Mark path with '*'


    // Display the grid
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            mvaddch(y, x, grid[y][x]);
        }
    }

    // Print path points
    /*move(height + 1, 0);
    printw("\nPath coordinates:\n");
    current = endIndex;
    int i = 1;
    while (current != startIndex) {
        printw(" %.2lf N, %.2lf E <--", points[current]->latitude, points[current]->longitude);
        //printw("Point %d: Latitude = %.2f, Longitude = %.2f\n", i++, points[current]->latitude, points[current]->longitude);
        current = prev[current];
    }*/

    refresh();  // Update the screen
    getch();    // Wait for user input to exit

    endwin();   // End ncurses mode
}

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
	int end_index = calculate_index(lat2, long2);


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






    int *prev = a_star(&g, start_index, end_index);

    // Display the map and path in the terminal
    double top = 4.0, left = 68.0, bottom = 23.75, right = 89.0;
    display_path_in_ncurses(prev, top, left, bottom, right, &g, start_index, end_index);
	return 0;
	
}


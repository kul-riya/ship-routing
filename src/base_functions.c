#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/base_functions.h"
#include "../include/edges.h"

#define MAX_LINE_LENGTH 240
#define DATE_LEN 24

#define START_LON 68.0
#define END_LON 89.0
#define START_LAT 4.0
#define END_LAT 23.75
#define RESOLUTION 0.5

# define LON_COUNT 43

// initialize graph
void initialize(Graph *g, int sizeLimit) {
	g->adjList = calloc(sizeLimit, sizeof(Point *)); // creates list of sizeLimit pointers to struct Point
							 						 // initialized to NULL.
	g->sizeLimit = sizeLimit;
}

// Create a new point
Point* createPoint(char *date, double time, double latitude, double longitude, double windspeedNorth,
                   double windspeedEast, double waveCurrentNorth, double waveCurrentEast) {
    Point* newPoint = (Point*)malloc(sizeof(Point));
    
	newPoint->date = date;
	newPoint->time = time;
    newPoint->latitude = latitude;
    newPoint->longitude = longitude;
    newPoint->windspeedNorth = windspeedNorth;
    newPoint->windspeedEast = windspeedEast;
    newPoint->waveCurrentNorth = waveCurrentNorth;
    newPoint->waveCurrentEast = waveCurrentEast;
    newPoint->edges = NULL;
    if (isNull(newPoint)) {
    	free(newPoint);
    	return NULL;
    }

//	printf("point created\n");
    return newPoint;
}

// Create a new edge
Edge* createEdge(Point* dest, double forward, double backward) {
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->dest = dest;
    newEdge->forward = forward;
    newEdge->backward = backward;
    newEdge->next = NULL;
//	printf("created edge: dest->lat = %lf, dest->lon = %lf\n", dest->latitude, dest->longitude);
    return newEdge;
}

// Add an edge to a point's adjacency list
void addEdge(Point* src, Point* dest) {
//	printf("adding edge: dest->lat = %lf, dest->lon = %lf\n", dest->latitude, dest->longitude);
    Edge* newEdge = createEdge(dest, find_edge(*src, *dest), find_edge(*dest, *src));
    newEdge->next = src->edges;
    src->edges = newEdge;
}

void printPoint(Point *p, int i) {
	if (!p) {
		printf("%d: NULL point\n\n", i);
		return;
	}
	printf("Point %d (Lat: %.2f, Lon: %.2f):\n", i, p->latitude, p->longitude);
    Edge* edge = p->edges;
    while (edge) {
        printf("  -> Point (Lat: %.2f, Lon: %.2f) [Forward: %.2f, Backward: %.2f]\n",
               edge->dest->latitude, edge->dest->longitude, edge->forward, edge->backward);
        edge = edge->next;
    }
    printf("\n");
}

// Print the graph (adjacency list)
void printGraph(Graph *g) {
	Point **points = g->adjList;
	int maxPoints = g->sizeLimit;
    //for (int i = 0; points[i]; i++) {
    for (int i = 0; i < g->sizeLimit; i++) {
        printPoint(points[i], i);
    }
}

// Read points from a CSV file
int readPointsFromCSV(const char* filename, Graph *g) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening CSV file");
	}
    
    char line[MAX_LINE_LENGTH];
    int count = 0;
	//printf("reading points from csv\n");
	Point **points = g->adjList;
	int maxPoints = g->sizeLimit;
	fgets(line, MAX_LINE_LENGTH, file); // omit header line
//	printf("%s", line);
	
    while (fgets(line, MAX_LINE_LENGTH, file) && count < maxPoints) {
		char *date = malloc(DATE_LEN);
        double time, latitude, longitude, windspeedNorth, windspeedEast, waveCurrentNorth, waveCurrentEast;
		//printf("%d\t%s", count, line);
        if (sscanf(line, "%[^,],%lf,%lf,%lf,%lf,%lf,%lf,%lf",
				   date, &time, &longitude, &latitude, 
				   &windspeedNorth, &windspeedEast,
                   &waveCurrentNorth, &waveCurrentEast)) {
            points[count] = createPoint(date, time, latitude, longitude, windspeedNorth, windspeedEast, waveCurrentNorth, waveCurrentEast);
            
            
        }
        if (calculate_index(latitude, longitude) != count) {
            	printf("%d ERROR ERROR ERROR\n", count);
            	return 0;
            }
        count++;
    }

    fclose(file);
	printf("file closed\n");
    return count;
}

int remove_float_error(double num) {
	if (num - (int)num > 0.5) return (int)num + 1;
	return (int)num;
}

// Hash function
/*int calculate_index(double latitude, double longitude) {
    int lat_index = (int)((latitude - START_LAT) * 4);
    int lon_index = (int)((longitude - START_LON) * 2);
    return lat_index * LON_COUNT + lon_index;
} */

// Hash function
int calculate_index(double latitude, double longitude) {
    int lat_index = remove_float_error((latitude - START_LAT) * 4);
    int lon_index = remove_float_error((longitude - START_LON) * 2);
    int index = lat_index * LON_COUNT + lon_index;
    //printf("index = %d\n", index);
    return index;
}

// Point has no data
int isNull(Point *p) {
	return p->windspeedNorth <= -1e+10 || p->windspeedEast <= -1e+10 || p->waveCurrentNorth <= -1e+10 || p->waveCurrentEast <= -1e+10;
}

// Function to retrieve data from the hash table (graph)
Point *retrieve(Graph *g, double latitude, double longitude) {
	if (latitude < START_LAT || latitude > END_LAT || longitude < START_LON || longitude > END_LON) return NULL;
    int index = calculate_index(latitude, longitude);
//    || isNull(g->adjList[index])
    if (index < 0 || index >=  g->sizeLimit || g->adjList[index] == NULL || isNull(g->adjList[index])) {
        return NULL;
    }
    return g->adjList[index];
}

// adding all required edges to each point
void initEdges(Graph *g) {
	printf("Initializing edges\n");
	Point **points = g->adjList;
	Point *destPoint;
	int adjacent[3] = {-1, 0, 1};
	double lon, lat, destLat, destLon;
	for (int i = 0; i < g->sizeLimit; i++) {
	//for (int i = 230; i < 235; i++) {
		if (!points[i]) continue;
		lat = points[i]->latitude;
		lon = points[i]->longitude;
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				int count = 2;
				if (j == 1 && k == 1) continue;
//				printf("%f, %f\n", lat + adjacent[j] * RESOLUTION, lon + adjacent[k] * RESOLUTION);
				destLat = lat + adjacent[j] * (0.25); destLon = lon + adjacent[k] * 0.5;
				destPoint = retrieve(g, destLat, destLon);
				while (!destPoint && count--) {
					destLat = destLat + adjacent[j] * (0.25); destLon = destLon + adjacent[k] * 0.5;
					destPoint = retrieve(g, destLat, destLon);
				}
				if (destPoint) addEdge(points[i], destPoint);
			}
		}
//		printf("\n");

	}
		
			
}


// TODO: implement A star

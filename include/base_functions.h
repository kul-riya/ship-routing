#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#ifndef BASE_FUNC
#define BASE_FUNC

#define MAX_LINE_LENGTH 240
#define DATE_LEN 24

#define START_LON 68.0
#define END_LON 89.0
#define START_LAT 4.0
#define END_LAT 23.75
#define RESOLUTION 0.5

# define LON_COUNT 43

// Point structure
typedef struct Point {
	char *date;
	double time;
    double latitude;           // Latitude of the point
    double longitude;          // Longitude of the point
    double windspeedNorth;     // Northward wind speed
    double windspeedEast;      // Eastward wind speed
    double waveCurrentNorth;   // Northward wave current
    double waveCurrentEast;    // Eastward wave current
    struct Edge* edges;        // Head of the adjacency list for this point
} Point;

// Edge structure
typedef struct Edge {
    struct Point* dest;        // Pointer to the destination point
    double forward;            // Weight for direction: point1 -> point2
    double backward;           // Weight for direction: point2 -> point1
    struct Edge* next;         // Pointer to the next edge in the adjacency list
} Edge;

// Graph structure
typedef struct Graph {
	struct Point **adjList;// -> __				  -edges-		  -next-
						   //   |__| -> struct Point -> struct Edge -> struct Edge...
  						   //   |__| -> struct Point -> struct Edge -> struct Edge...
						   //   |__|
	int sizeLimit;
} Graph;



// Function prototypes

void initialize(Graph *g, int);

Point* createPoint(char *, double, double latitude, double longitude, double windspeedNorth,
                   double windspeedEast, double waveCurrentNorth, double waveCurrentEast);
                   
int isNull(Point *p);

int * a_star(Graph *g, int startIndex, int endIndex);

int calculate_index(double latitude, double longitude);

int remove_float_error(double num);

Edge* createEdge(Point* dest, double forward, double backward);

void addEdge(Point* src, Point* dest);

void printPoint(Point *p, int i);

void printGraph(Graph *);

void initEdges(Graph *);

int readPointsFromCSV(const char* filename, Graph *);

// void dijkstra(Point* points[], int numPoints, int srcIndex, int destIndex);

#endif



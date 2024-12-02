#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/base_functions.h"
#include "../include/edges.h"

#define MAX_LINE_LENGTH 70
#define DATE_LEN 23.75

#define START_LON 68.0
#define END_LON 89.0
#define START_LAT 4.0
#define END_LAT 23.75
#define INTERVAL 43

// initialize graph
void initialize(Graph *g, int sizeLimit) {
	g->adjList = calloc(sizeLimit, sizeof(Point *)); // creates list of sizeLimit pointers to struct Point
													 // initialized to NULL.
	g->sizeLimit = sizeLimit;
//	printf("Graph initialized\n");
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

// Print the graph (adjacency list)
void printGraph(Graph *g) {
	Point **points = g->adjList;
	int maxPoints = g->sizeLimit;
    //for (int i = 0; points[i]; i++) {
	//TODO: change maxpoints
    for (int i = 0; i < 5 && points[i]; i++) {
        printf("Point %d (Lat: %.2f, Lon: %.2f):\n", i, points[i]->latitude, points[i]->longitude);
        Edge* edge = g->adjList[i]->edges;
        while (edge) {
            printf("  -> Point (Lat: %.2f, Lon: %.2f) [Forward: %.2f, Backward: %.2f]\n",
                   edge->dest->latitude, edge->dest->longitude, edge->forward, edge->backward);
            edge = edge->next;
        }
        printf("\n");
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
//		printf("%d\t%s", count, line);
        if (sscanf(line, "%[^,],%lf,%lf,%lf,%lf,%lf,%lf,%lf",
				   date, &time, &longitude, &latitude, 
				   &windspeedNorth, &windspeedEast,
                   &waveCurrentNorth, &waveCurrentEast) == 8) {
            points[count] = createPoint(date, time, latitude, longitude, windspeedNorth, windspeedEast, waveCurrentNorth, waveCurrentEast);
            count++;
        }
    }

    fclose(file);
	printf("file closed\n");
    return count;
}

// 
int isNull(Point *p) {
	return !p->windspeedNorth && !p->windspeedEast && !p->waveCurrentNorth && !p->waveCurrentEast;
}

// adding all required edges to each point
void initEdges(Graph *g) {
	printf("Initializing edges\n");
	Point **points = g->adjList;
	double lon, lat;
	for (int i = 0; i < g->sizeLimit && points[i]; i++) {
//	for (int i = 42; i == 42; i++) {
		lat = points[i]->latitude;
		lon = points[i]->longitude;
//		printf("%lf %lf\n", lat, lon);
		if (lon != START_LON) {
			addEdge(points[i], points[i - 1]); // left
			if (lat != START_LAT) {
				addEdge(points[i], points[i - INTERVAL - 1]); // top left
			} if (lat != END_LAT) addEdge(points[i], points[i + INTERVAL - 1]); // bottom left
		} if (lon != END_LON) {
			 addEdge(points[i], points[i + 1]); // right
			if (lat != START_LAT) {
				addEdge(points[i], points[i - INTERVAL + 1]); // top right
			}
			if (lat != END_LAT) addEdge(points[i], points[i + INTERVAL + 1]); // bottom right

		} if (lat != START_LAT) {
			addEdge(points[i], points[i - INTERVAL]); // up
		} if (lat != END_LAT) {
			addEdge(points[i], points[i + INTERVAL]); // down
		}
	}
		
			
}

// Dijkstra's algorithm
/*void dijkstra(Point* points[], int numPoints, int srcIndex, int destIndex) {
    double dist[numPoints];
    int prev[numPoints];
    int visited[numPoints];

    for (int i = 0; i < numPoints; i++) {
        dist[i] = DBL_MAX;
        prev[i] = -1;
        visited[i] = 0;
    }
    dist[srcIndex] = 0;

    for (int i = 0; i < numPoints; i++) {
        int u = -1;
        for (int j = 0; j < numPoints; j++) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        if (dist[u] == DBL_MAX)
            break;

        visited[u] = 1;

        Edge* edge = points[u]->edges;
        while (edge) {
            int v = edge->dest - points[0];  // Calculate index
            double weight = dist[u] + edge->forward;
            if (weight < dist[v]) {
                dist[v] = weight;
                prev[v] = u;
            }
            edge = edge->next;
        }
    }

    if (dist[destIndex] == DBL_MAX) {
        printf("No path from Point %d to Point %d\n", srcIndex, destIndex);
    } else {
        printf("Shortest path from Point %d to Point %d (Cost: %.2f):\n", srcIndex, destIndex, dist[destIndex]);
        int path[numPoints], pathIndex = 0;
        for (int at = destIndex; at != -1; at = prev[at]) {
            path[pathIndex++] = at;
        }
        for (int i = pathIndex - 1; i >= 0; i--) {
            printf("Point %d ", path[i]);
            if (i > 0) printf("-> ");
        }
        printf("\n");
    }
}*/

// TODO: replace with A star

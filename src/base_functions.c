#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/base_functions.h"

#define MAX_LINE_LENGTH 70
#define DATE_LEN 24

// initialize graph
void initialize(Graph *g, int sizeLimit) {
	g->adjList = calloc(sizeLimit, sizeof(Point *)); // creates list of sizeLimit pointers to struct Point
													 // initialized to NULL.
	g->sizeLimit = sizeLimit;
	printf("Graph initialized\n");
}

// Create a new point
Point* createPoint(char *date, double time, double latitude, double longitude, double windspeedNorth,
                   double windspeedEast, double waveCurrentNorth, double waveCurrentEast) {
    Point* newPoint = (Point*)malloc(sizeof(Point));
	printf("point created\n");
	newPoint->date = date;
	newPoint->time = time;
    newPoint->latitude = latitude;
    newPoint->longitude = longitude;
    newPoint->windspeedNorth = windspeedNorth;
    newPoint->windspeedEast = windspeedEast;
    newPoint->waveCurrentNorth = waveCurrentNorth;
    newPoint->waveCurrentEast = waveCurrentEast;
    newPoint->edges = NULL;
    return newPoint;
}

// Create a new edge
Edge* createEdge(Point* dest, double forward, double backward) {
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->dest = dest;
    newEdge->forward = forward;
    newEdge->backward = backward;
    newEdge->next = NULL;
    return newEdge;
}

// Add an edge to a point's adjacency list
void addEdge(Point* src, Point* dest, double forward, double backward) {
    Edge* newEdge = createEdge(dest, forward, backward);
    newEdge->next = src->edges;
    src->edges = newEdge;
}

// Print the graph (adjacency list)
void printGraph(Graph *g) {
	Point **points = g->adjList;
    //for (int i = 0; points[i]; i++) {
    for (int i = 0; i < 5; i++) {
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
	printf("reading points from csv\n");
	Point **points = g->adjList;
	int maxPoints = g->sizeLimit;
	fgets(line, MAX_LINE_LENGTH, file); // omit header line
	// testing
	char c1[10], c2[10], c3[10], c4[10];
	sscanf(line, "%*s,%*s,%*s,%*s,%s,%s,%s,%s", c1, c2, c3, c4);
	printf("yo what%s, %s, %s, %s\n", c1, c2, c3, c4);

    while (fgets(line, MAX_LINE_LENGTH, file) && count < maxPoints) {
		char *date = malloc(DATE_LEN);
        double time, latitude, longitude, windspeedNorth, windspeedEast, waveCurrentNorth, waveCurrentEast;
		if (date) printf("malloced date\n");
		printf("%s\n", line);
        if (sscanf(line, "%s,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
				   date, &time, &longitude, &latitude, 
				   &windspeedNorth, &windspeedEast,
                   &waveCurrentNorth, &waveCurrentEast) == 8) {
            points[count] = createPoint(date, time, latitude, longitude, windspeedNorth, windspeedEast, waveCurrentNorth, waveCurrentEast);
            count++;
        }
    }

    fclose(file);
    return count;
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

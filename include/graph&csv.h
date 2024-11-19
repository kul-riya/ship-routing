#ifndef GRAPH_CSV_H
#define GRAPH_CSV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

// Constants
#define MAX_LINE_LENGTH 1024
#define MAX_POINTS 100

// Edge structure
typedef struct Edge {
    struct Point* dest;        // Pointer to the destination point
    double forward;            // Weight for direction: point1 -> point2
    double backward;           // Weight for direction: point2 -> point1
    struct Edge* next;         // Pointer to the next edge in the adjacency list
} Edge;

// Point structure
typedef struct Point {
    double latitude;           // Latitude of the point
    double longitude;          // Longitude of the point
    double windspeedNorth;     // Northward wind speed
    double windspeedEast;      // Eastward wind speed
    double windStress;         // Wind stress
    double waveCurrentNorth;   // Northward wave current
    double waveCurrentEast;    // Eastward wave current
    struct Edge* edges;        // Head of the adjacency list for this point
} Point;

// Function prototypes
Point* createPoint(double latitude, double longitude, double windspeedNorth,
                   double windspeedEast, double windStress,
                   double waveCurrentNorth, double waveCurrentEast);

Edge* createEdge(Point* dest, double forward, double backward);

void addEdge(Point* src, Point* dest, double forward, double backward);

void printGraph(Point* points[], int numPoints);

int readPointsFromCSV(const char* filename, Point* points[], int maxPoints);

void dijkstra(Point* points[], int numPoints, int srcIndex, int destIndex);

#endif

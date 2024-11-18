#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants
#define BAD_FLAG -1.0E+34
#define MAX_LINE_LENGTH 1024

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
    double windspeedNorth;     // Northward wind speed (vector)
    double windspeedEast;      // Eastward wind speed (vector)
    double windStress;         // Northward wind stress (scalar)
    double waveCurrentNorth;   // Northward wave current (vector)
    double waveCurrentEast;    // Eastward wave current (vector)
    int arrayIndex;            // Index of this point in the point array
    struct Edge* edges;        // Head of the list of edges connected to this point
} Point;

// Function prototypes
Point* createPoint(int index, double latitude, double longitude, double windspeedNorth, double windspeedEast,
                   double windStress, double waveCurrentNorth, double waveCurrentEast);
Edge* createEdge(Point* dest, double forward, double backward);
void addEdge(Point* src, Point* dest, double forward, double backward);
void printGraph(Point* points[], int numPoints);
int loadPointsFromCSV(const char* filename, Point* points[], int maxPoints);
void freeGraph(Point* points[], int numPoints);

#endif // HEADER_H

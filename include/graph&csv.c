#include "graph&csv.h"

// Function to create a new point
Point* createPoint(int index, double latitude, double longitude, double windspeedNorth, double windspeedEast,
                   double windStress, double waveCurrentNorth, double waveCurrentEast) {
    Point* newPoint = (Point*)malloc(sizeof(Point));
    newPoint->latitude = latitude;
    newPoint->longitude = longitude;
    newPoint->windspeedNorth = windspeedNorth;
    newPoint->windspeedEast = windspeedEast;
    newPoint->windStress = windStress;
    newPoint->waveCurrentNorth = waveCurrentNorth;
    newPoint->waveCurrentEast = waveCurrentEast;
    newPoint->arrayIndex = index;
    newPoint->edges = NULL;
    return newPoint;
}

// Function to create a new edge
Edge* createEdge(Point* dest, double forward, double backward) {
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->dest = dest;
    newEdge->forward = forward;
    newEdge->backward = backward;
    newEdge->next = NULL;
    return newEdge;
}

// Function to add an edge to a point's adjacency list
void addEdge(Point* src, Point* dest, double forward, double backward) {
    Edge* newEdge = createEdge(dest, forward, backward);
    newEdge->next = src->edges;
    src->edges = newEdge;
}

// Function to print the graph (adjacency list)
void printGraph(Point* points[], int numPoints) {
    for (int i = 0; i < numPoints; i++) {
        printf("Point %d (Lat: %.2f, Lon: %.2f):\n", points[i]->arrayIndex, points[i]->latitude, points[i]->longitude);
        Edge* edge = points[i]->edges;
        while (edge) {
            printf("  -> Point %d (Forward Weight: %.2f, Backward Weight: %.2f)\n",
                   edge->dest->arrayIndex, edge->forward, edge->backward);
            edge = edge->next;
        }
        printf("\n");
    }
}

// Function to load points from a CSV file
int loadPointsFromCSV(const char* filename, Point* points[], int maxPoints) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return -1;
    }

    char line[MAX_LINE_LENGTH];
    int index = 0;

    // Read each line of the CSV file
    while (fgets(line, MAX_LINE_LENGTH, file) && index < maxPoints) {
        double latitude, longitude, windspeedNorth, windspeedEast, windStress, waveCurrentNorth, waveCurrentEast;
        sscanf(line, "%lf,%lf,%lf,%lf,%lf,%lf,%lf",
               &latitude, &longitude, &windspeedNorth, &windspeedEast, &windStress, &waveCurrentNorth, &waveCurrentEast);

        points[index] = createPoint(index, latitude, longitude, windspeedNorth, windspeedEast, windStress, waveCurrentNorth, waveCurrentEast);
        index++;
    }

    fclose(file);
    return index;
}

// Function to free allocated memory for the graph
void freeGraph(Point* points[], int numPoints) {
    for (int i = 0; i < numPoints; i++) {
        Edge* edge = points[i]->edges;
        while (edge) {
            Edge* temp = edge;
            edge = edge->next;
            free(temp);
        }
        free(points[i]);
    }
}

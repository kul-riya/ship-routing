#include "graph&csv.h"

// Create a new point
Point* createPoint(double latitude, double longitude, double windspeedNorth,
                   double windspeedEast, double windStress,
                   double waveCurrentNorth, double waveCurrentEast) {
    Point* newPoint = (Point*)malloc(sizeof(Point));
    newPoint->latitude = latitude;
    newPoint->longitude = longitude;
    newPoint->windspeedNorth = windspeedNorth;
    newPoint->windspeedEast = windspeedEast;
    newPoint->windStress = windStress;
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
void printGraph(Point* points[], int numPoints) {
    for (int i = 0; i < numPoints; i++) {
        printf("Point %d (Lat: %.2f, Lon: %.2f):\n", i, points[i]->latitude, points[i]->longitude);
        Edge* edge = points[i]->edges;
        while (edge) {
            printf("  -> Point (Lat: %.2f, Lon: %.2f) [Forward: %.2f, Backward: %.2f]\n",
                   edge->dest->latitude, edge->dest->longitude, edge->forward, edge->backward);
            edge = edge->next;
        }
        printf("\n");
    }
}

// Read points from a CSV file
int readPointsFromCSV(const char* filename, Point* points[], int maxPoints) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening CSV file");
        return 0;
    }

    char line[MAX_LINE_LENGTH];
    int count = 0;

    while (fgets(line, MAX_LINE_LENGTH, file) && count < maxPoints) {
        double latitude, longitude, windspeedNorth, windspeedEast, windStress, waveCurrentNorth, waveCurrentEast;
        if (sscanf(line, "%lf,%lf,%lf,%lf,%lf,%lf,%lf",
                   &latitude, &longitude, &windspeedNorth, &windspeedEast,
                   &windStress, &waveCurrentNorth, &waveCurrentEast) == 7) {
            points[count] = createPoint(latitude, longitude, windspeedNorth, windspeedEast,
                                        windStress, waveCurrentNorth, waveCurrentEast);
            count++;
        }
    }

    fclose(file);
    return count;
}

// Dijkstra's algorithm
void dijkstra(Point* points[], int numPoints, int srcIndex, int destIndex) {
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
}

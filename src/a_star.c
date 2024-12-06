#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h> // For DBL_MAX
#include <stdbool.h>

// Constants
#define INF DBL_MAX  // Infinite value for unreachable nodes

#include "../include/base_functions.h"
#include "../include/edges.h"


void a_star(Graph *g, int startIndex, int endIndex) {
	printf("in a_star\n");
    int numPoints = g->sizeLimit;
    Point** points = g->adjList;
    double dist[numPoints];  // Distance from start to each point
    int prev[numPoints];     // Previous node in the optimal path
    bool visited[numPoints]; // To mark visited nodes
    
    // Initialize distances, previous nodes, and visited status
    for (int i = 0; i < numPoints; i++) {
        dist[i] = INF;
        prev[i] = -1;
        visited[i] = false;
    }
    dist[startIndex] = 0.0;

    while (true) {
        // Find the node with the smallest tentative distance
        int u = -1;
        double minDist = INF;
        for (int i = 0; i < numPoints; i++) {
            if (points[i] && !visited[i] && dist[i] + haversine_distance(points[i]->latitude, points[i]->longitude, points[endIndex]->latitude, points[endIndex]->longitude) < minDist) {
                u = i;
                minDist = dist[i];
            }
        }
        if (u == -1) {
            break;  // All reachable nodes are visited
        }
        visited[u] = true;
        
        // Relaxation step for each edge
        Edge* edge = points[u]->edges;
        while (edge) {
            int v = calculate_index(edge->dest->latitude, edge->dest->longitude);
            double weight = edge->forward;  // Forward direction weight (for direction u -> v)
            
            // Relaxation: if a shorter path is found
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
            }
            edge = edge->next;
        }
    }

    // Print the shortest path from startIndex to endIndex
    if (dist[endIndex] == INF) {
        printf("No path exists between Point %d and Point %d\n", startIndex, endIndex);
        return;
    }
    
    printf("\nShortest path from Point %d to Point %d:\n", startIndex, endIndex);
    int current = endIndex;
    while (current != startIndex) {
        printf("Point %d <- ", calculate_index(points[current]->latitude, points[current]->longitude));
        current = prev[current];
    }
    printf("  Point %d\n", startIndex);
}

typedef struct Node {
    double latitude;            // Latitude of the node in radians
    double longitude;           // Longitude of the node in radians
    double windspeedNorth;    // Northward wind speed (vector)
    double windspeedEast;     // Eastward wind speed (vector)
	double waveCurrentNorth;    // Northward wave current (vector)
    double waveCurrentEast;     // Eastward wave current (vector)
    double windStress;     // Northward wind stress (scalar)
    int arrayIndex;             // Index of this node in the node array
    char dateTime[20];          // Date and time string (e.g., "YYYY-MM-DD HH:MM:SS")
    struct Edge* edges;         // Head of the list of edges connected to this node
} Node;

typedef struct Edge {
    Node* dest;                // Pointer to the second node
    double forward;  // Weight for direction: node1 -> node2
    double backward;  // Weight for direction: node2 -> node1
    struct Edge* next;          // Pointer to the next edge in the adjacency list
} Edge;

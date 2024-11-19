#include <math.h>
#include "graph&csv.h"

#define STILL_WATER_RESISTANCE 1500 // average still water resistance for large container ships
#define EARTH_RADIUS_KM 6371.0  // Earth radius in kilometers
#define R_CX 1 //resistance coefficients
#define R_CY 1
#define R_AX 1
#define R_AY 1

double find_resistance(double ship_bearing, double east_curr, double north_curr, double east_wind, double north_wind);
double find_bearing(double lat1, double lon1, double lat2, double lon2);
double haversine_distance(double lat1, double lon1, double lat2, double lon2);
double average(double x, double y);
double find_edge(Point start, Point end);

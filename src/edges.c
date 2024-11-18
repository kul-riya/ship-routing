#include "edges.h"


double find_resistance(double ship_bearing, double east_curr, double north_curr, double east_wind, double north_wind){
    // resistance force is proportional to the square of the current / wind velocity
    // ship bearing calculated from the start coordinate and end coordinate of the edge
    // ship bearing in radians
    double curr_resistance_x = R_CX * -1 * (north_curr * north_curr * cos(ship_bearing) + east_curr * east_curr * sin(ship_bearing));
    // resistance force parallel to ship's bearing and towards the stern (behind)
    double curr_resistance_y = R_CY * (-1 * north_curr * north_curr * sin(ship_bearing) + east_curr * east_curr * cos(ship_bearing));
    // resistance force perpendicular to ship's bearing and towards the starboard (right)
    double wind_resistance_x = R_AX * -1 * (north_wind * north_wind * cos(ship_bearing) + east_wind * east_wind * sin(ship_bearing));
    // resistance force parallel to ship's bearing and towards the stern (behind)
    double wind_resistance_y = R_AY * (-1 * north_wind * north_wind * sin(ship_bearing) + east_wind * east_wind * cos(ship_bearing));
    // resistance force perpendicular to ship's bearing and towards the starboard (right)
    double resistance_x = STILL_WATER_RESISTANCE + curr_resistance_x + wind_resistance_x; // total resistance toward stern
    double resistance_y = curr_resistance_y + wind_resistance_y;
    return sqrt(resistance_x * resistance_x + resistance_y * resistance_y); // resultant resistance force
}

// INPUT ALL ANGLES IN RADIANS

double find_bearing(double lat1, double lon1, double lat2, double lon2){ // returns the initial bearing in radians going 
    double y = sin(lon2 - lon1) * cos(lat2);                             // from lat1, long1 to lat2, long2
    double x = cos(lat1) * sin(lat2) - sin(lat1) * cos(lat2) * cos(lon2 - lon1);
    return atan2(y, x);
} // initial bearing is approximately equal to final bearing for short distances.

double haversine_distance(double lat1, double lon1, double lat2, double lon2){ // returns the great-circle distance between two points
    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;
    double a = pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlon / 2), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return EARTH_RADIUS_KM * c;
}

double average(double x, double y){ // returns the mean value of two double inputs
    return (x + y) / 2;
}
 
double find_edge(Node start, Node end){ // returns the edge value of an edge between two nodes
    double bearing = find_bearing(start.latitude, start.longitude, end.latitude, end.longitude);
    double avg_north_curr = average(start.waveCurrentNorth, end.waveCurrentNorth);
    double avg_east_curr = average(start.waveCurrentEast, end.waveCurrentEast);
    double avg_north_wind = average(start.windspeedNorth, end.windspeedNorth);
    double avg_east_wind = average(start.windspeedEast, end.windspeedEast);
    double resistance = find_resistance(bearing, avg_east_curr, avg_north_curr, avg_east_wind, avg_north_wind);
    double distance = haversine_distance(start.latitude, start.longitude, end.latitude, end.longitude);
    return distance * resistance;
}

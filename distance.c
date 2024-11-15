#include <math.h>


#define EARTH_RADIUS_KM 6371.0  // Earth radius in kilometers

// Converts degrees to radians
double deg2rad(double degrees) {
    return degrees * M_PI / 180.0;
}

// Haversine formula to calculate the great-circle distance between two points
double haversine(double lat1, double lon1, double lat2, double lon2) {
    // Convert latitude and longitude from degrees to radians
    lat1 = deg2rad(lat1);
    lon1 = deg2rad(lon1);
    lat2 = deg2rad(lat2);
    lon2 = deg2rad(lon2);

    // Haversine formula
    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    double a = pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlon / 2), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    // Distance in kilometers
    return EARTH_RADIUS_KM * c;
}


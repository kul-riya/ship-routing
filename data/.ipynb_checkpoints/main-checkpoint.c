#include <math.h>
#include <stdio.h>


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

int main() {
	printf("distance between 0.125 lon and 0.125 lat= %lf\n", haversine(4.125, 68.125, 4, 68));
	printf("distance between 0.5 lon and 0 lat= %lf\n", haversine(4, 68, 4, 68.5));

	return 0;
}

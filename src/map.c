#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <champlain/champlain.h>
#include "map.h"

// Function to plot points from a CSV file
void plot_points_from_csv(const char *csv_file, ChamplainView *map_view) {
    FILE *file = fopen(csv_file, "r");
    if (!file) {
        perror("Error opening CSV file");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        // Parse latitude and longitude from CSV
        double latitude, longitude;
        if (sscanf(line, "%lf,%lf", &latitude, &longitude) == 2) {
            ChamplainMarker *marker = champlain_marker_new_full(NULL, latitude, longitude);
            champlain_layer_add_feature(CHAMPLAIN_LAYER(map_view), CHAMPLAIN_FEATURE(marker));
        }
    }

    fclose(file);
}

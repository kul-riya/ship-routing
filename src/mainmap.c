#include <gtk/gtk.h>
#include <champlain/champlain.h>
#include "map.h"

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Create main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Map Visualization");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create and configure Champlain map view
    ChamplainView *map_view = CHAMPLAIN_VIEW(champlain_view_new());
    champlain_view_set_map_source(map_view, champlain_map_source_factory_create_cached_source(CHAMPLAIN_MAP_SOURCE_OSM_MAPNIK));
    champlain_view_set_zoom_level(map_view, 4.0);
    champlain_view_center_on(map_view, -20.0, 80.0); // Center on the Indian Ocean

    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(map_view));

    // Plot points from the CSV file
    plot_points_from_csv("data/merged_everything-checkpoint.csv", map_view);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

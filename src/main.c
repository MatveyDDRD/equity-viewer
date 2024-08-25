#include <stdio.h>
#include <gtk/gtk.h>
#include <curl/curl.h>

#include "interface.h"

int main(int argc, char **argv) {

    curl_global_init(CURL_GLOBAL_ALL);

    GtkApplication *app;
    int status;
    app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);


    void testFunc();
    testFunc();
    return status;
    return 0;
};
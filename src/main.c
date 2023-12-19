//بسم الله الرحمن الرحيم

#include <gtk/gtk.h>
#include "../include/task_tree.h"
#include "../include/task_tree_gtk.h"

void activate(GtkApplication* app, gpointer data);

int main()
{
    GtkApplication* app = gtk_application_new("BismiAllah.BismiAllah.BismiAllah", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), 0, NULL);
    g_object_unref(app);
    return status;
}

void activate(GtkApplication* app, gpointer data)
{
    GtkWidget* window = gtk_application_window_new(app);

    struct task_t* task =  task_tree_task_new("BismiAllah");
    GtkWidget* task_widget = task_tree_gtk_task_widget(task);
    gtk_window_set_child(GTK_WINDOW(window), task_widget);

    gtk_widget_show(window);
}


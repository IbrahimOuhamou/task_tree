//بسم الله الرحمن الرحيم

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gtk-4.0/gtk/gtk.h>

#include "../include/ui_view_focus.h"
#include "../include/task_tree.h"

const char* names_list[5] = {"BismiAllah", "Allah Akbar", "la ilaha illa Allah", "sub7an Allah", "astaghfiro Allah"};

struct tlist_t tlist;

int main(int argc, char* argv[])
{
    printf("in the name of Allah\n");

    task_tree_tlist_init(&tlist);
    gtk_init();


    GtkApplication* app = gtk_application_new("BismiAllah.BismiAllah.BismiAllah", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(task_tree_ui_view_focus_init), &tlist);

    g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(app);
}


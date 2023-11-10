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

    task_tree_tlist_task_add(&tlist, task_tree_task_new("la ilaha illa Allah wa Allah Akbar"));
    for(uint32_t i = 1; i < 20; i++)
    {
        task_tree_tlist_task_add(&tlist, task_tree_task_new(names_list[i % 5]));
    }

    for(uint32_t i = 3; i < tlist.size / 2; i++)
    {
        task_tree_tlist_task_child_add(&tlist, 0, i);
    }

    for(uint32_t i = tlist.size / 2; i < tlist.size; i++)
    {
        task_tree_tlist_task_parent_add(&tlist, 0, i);
    }

    GtkApplication* app = gtk_application_new("BismiAllah.BismiAllah.BismiAllah", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(task_tree_ui_view_focus_init), &tlist);

    g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(app);
}


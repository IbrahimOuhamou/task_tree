//in the name of Allah

#include <gtk-4.0/gtk/gtk.h>
#include "../include/task_tree.h"

//returns a widget pointer (mostly a GtkFrame)
//
//should be used in the 'focus view' and 'canvas  view' when the task is selected.
GtkWidget* task_tree_ui_task_widget_new(struct task_t* task)
{
    GtkWidget* task_widget = gtk_frame_new();
}



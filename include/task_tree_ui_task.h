//in the name of Allah
#ifndef TASK_TREE_UI_TASK_H
#define TASK_TREE_UI_TASK_H

#include <gtk-4.0/gtk/gtk.h>
#include "task_tree.h"

//returns a widget pointer (mostly a GtkFrame)
//
//should be used in the 'focus view' and 'canvas  view' when the task is selected.
GtkWidget* task_tree_ui_task_widget_new(struct task_t* task);

#endif


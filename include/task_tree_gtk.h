//بسم الله الرحمن الرحيم

#ifndef TASK_TREE_GTK_H
#define TASK_TREE_GTK_H
#include <stdint.h>

#include "task_tree.h"
#include <gtk-4.0/gtk/gtk.h>

void task_tree_gtk_main_menu();

GtkWidget* task_tree_gtk_task_widget(struct task_t* task);

#endif


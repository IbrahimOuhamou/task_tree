//بسم الله الرحمن الرحيم

#ifndef TASK_TREE_UI_H
#define TASK_TREE_UI_H
#include <stdint.h>

#include "task_tree.h"
#include <gtk-4.0/gtk/gtk.h>

void task_tree_ui_main_menu();

GtkWidget* task_tree_ui_task_widget(struct task_t* task);

#endif


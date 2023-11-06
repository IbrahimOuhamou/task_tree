//بسم الله الرحمن الرحيم
#ifndef TASK_TREE_UI_VIEW_FOCUS_H
#define TASK_TREE_UI_VIEW_FOCUS_H

#include "task_tree.h"
#include <gtk-4.0/gtk/gtk.h>
#include <stdint.h>

static GtkWidget* ui_view_focus;

int8_t task_tree_ui_view_focus_init(GtkApplication* app, struct tlist_t* tlist);
int8_t task_tree_ui_view_focus_task_select(GtkWidget *widget, struct task_t* task);

#endif

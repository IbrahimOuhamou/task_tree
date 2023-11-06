//بسم الله الرحمن الرحيم

#include "../include/ui_view_focus.h"
#include "../include/task_tree.h"

int8_t task_tree_ui_view_focus_init(GtkApplication* app, struct tlist_t* tlist)
{
    GtkWidget* window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "BismiAllah focus view");

    gtk_widget_show(window);
    return 0;
}

int8_t task_tree_ui_view_focus_task_select(GtkWidget *widget, struct task_t* task)
{
    return -1;
}

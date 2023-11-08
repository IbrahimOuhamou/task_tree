//بسم الله الرحمن الرحيم

#include "../include/ui_view_focus.h"
#include "../include/task_tree.h"

int8_t task_tree_ui_view_focus_init(GtkApplication* app, struct tlist_t* tlist)
{
    /*BismiAllah*/
    GtkWidget* window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "BismiAllah focus view");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 600);

    /*BismiAllah*/
    /*setting up the box that is gonna be the parent of other boxes by the will of Allah*/
    GtkWidget* box = gtk_scrolled_window_new();
    gtk_window_set_child(GTK_WINDOW(window), box);

    /*BismiAllah*/
    /*setting up the box for parent tasks*/
    GtkWidget* box_parent_tasks = gtk_scrolled_window_new();
    gtk_box_append(GTK_BOX(box), box_parent_tasks);
    gtk_widget_set_halign(box_parent_tasks, GTK_ALIGN_FILL);

    for(uint32_t i = 0; i < tlist->size; i++)
    {
        GtkWidget* button = gtk_button_new_with_label(tlist->data[i]->name);
        gtk_box_append(GTK_BOX(box_parent_tasks), button);
    }



    gtk_widget_show(window);
    return 0;
}

int8_t task_tree_ui_view_focus_task_select(GtkWidget *widget, struct task_t* task)
{
    return -1;
}

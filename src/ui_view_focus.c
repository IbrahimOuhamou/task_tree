//بسم الله الرحمن الرحيم

#include "../include/ui_view_focus.h"
#include "../include/task_tree.h"

GtkWidget* window;
struct tlist_t* ui_tlist;

int8_t task_tree_ui_view_focus_init(GtkApplication* app, struct tlist_t* tlist)
{
    /*BismiAllah*/
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "BismiAllah focus view");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 600);

    ui_tlist = tlist;
    task_tree_ui_view_focus_task_select(NULL, ui_tlist->data[0]);

    gtk_widget_show(window);
    return 0;
}

int8_t task_tree_ui_view_focus_task_select(GtkWidget *widget, struct task_t* task)
{
    g_print("BismiAllah: will select task: %u %s %p\n", task->id, task->name, task);
    /*BismiAllah*/
    /*setting up the box that is gonna be the parent of other boxes by the will of Allah*/
    GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_window_set_child(GTK_WINDOW(window), box);

    /*BismiAllah*/
    /*setting up the box for parent tasks*/
    GtkWidget* box_parent_tasks = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_append(GTK_BOX(box), box_parent_tasks);
    gtk_widget_set_halign(box_parent_tasks, GTK_ALIGN_FILL);

    /*for(uint32_t i = 0; i < task->parents_id_list_size; i++)
    {
        GtkWidget* button = gtk_button_new_with_label(ui_tlist->data[i]->name);
        g_signal_connect(button, "clicked", G_CALLBACK(task_tree_ui_view_focus_task_select), ui_tlist->data[task->parents_id_list[i]]);
        gtk_box_append(GTK_BOX(box_parent_tasks), button);
    }*/

    /*BismiAllah*/
    /*setting up the selected task*/
    GtkWidget* task_button = gtk_button_new_with_label(task->name);
    gtk_widget_set_halign(task_button, GTK_ALIGN_START);
    gtk_box_append(GTK_BOX(box), task_button);

    /*BismiAllah*/
    GtkWidget* box_child_tasks = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_append(GTK_BOX(box), box_child_tasks);
    gtk_widget_set_halign(box_child_tasks, GTK_ALIGN_FILL);

    /*for(uint32_t i = 0; i < ui_tlist->data[0]->children_id_list_size; i++)
    {
        GtkWidget* button = gtk_button_new_with_label(ui_tlist->data[task->children_id_list[i]]->name);
        g_signal_connect(button, "clicked", G_CALLBACK(task_tree_ui_view_focus_task_select), ui_tlist->data[task->children_id_list[i]]);
        gtk_box_append(GTK_BOX(box_child_tasks), button);
    }*/

    return 0;
}

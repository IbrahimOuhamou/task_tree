//بسم الله الرحمن الرحيم

#include "../include/ui_view_focus.h"
#include "../include/task_tree.h"

GtkWidget* window;
struct tlist_t* ui_tlist;

//keep it static
static void task_tree_ui_view_focus_task_name_set(GtkWidget* widget, gpointer new_name);
static struct task_t* ui_view_focus_task;

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
    ui_view_focus_task = task;
    /*BismiAllah*/
    /*setting up the box that is gonna be the parent of other boxes by the will of Allah*/
    GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_window_set_child(GTK_WINDOW(window), box);

    /*BismiAllah*/
    /*setting up the box for parent tasks*/
    GtkWidget* box_parent_tasks = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_append(GTK_BOX(box), box_parent_tasks);
    gtk_widget_set_halign(box_parent_tasks, GTK_ALIGN_FILL);

    for(uint32_t i = 0; i < task->parents_id_list_size; i++)
    {
        GtkWidget* button = gtk_button_new_with_label(ui_tlist->data[task->parents_id_list[i]]->name);
        g_signal_connect(button, "clicked", G_CALLBACK(task_tree_ui_view_focus_task_select), ui_tlist->data[task->parents_id_list[i]]);
        gtk_box_append(GTK_BOX(box_parent_tasks), button);
    }

    /*BismiAllah*/
    /*setting up the selected task*/
    GtkWidget* box_focus = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_append(GTK_BOX(box), box_focus);

    /*BismiAllah*/
    /*setting the text*/
    GtkWidget* box_task_name = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_append(GTK_BOX(box_focus), box_task_name);

    GtkWidget* text_task_name = gtk_text_new();
    gtk_text_set_max_length(GTK_TEXT(text_task_name), sizeof(task->name));
    gtk_text_set_placeholder_text(GTK_TEXT(text_task_name), task->name);
    gtk_box_append(GTK_BOX(box_task_name), text_task_name);

    GtkWidget* button_task_name_set = gtk_button_new_with_label("set task name");
    g_signal_connect(button_task_name_set, "clicked", G_CALLBACK(task_tree_ui_view_focus_task_name_set), gtk_text_get_buffer(GTK_TEXT(text_task_name)));
    gtk_box_append(GTK_BOX(box_task_name), button_task_name_set);

    /*BismiAllah*/
    /*setting up children tasks*/
    GtkWidget* box_child_tasks = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_append(GTK_BOX(box), box_child_tasks);
    gtk_widget_set_halign(box_child_tasks, GTK_ALIGN_FILL);

    for(uint32_t i = 0; i < task->children_id_list_size; i++)
    {
        GtkWidget* button = gtk_button_new_with_label(ui_tlist->data[task->children_id_list[i]]->name);
        g_signal_connect(button, "clicked", G_CALLBACK(task_tree_ui_view_focus_task_select), ui_tlist->data[task->children_id_list[i]]);
        gtk_box_append(GTK_BOX(box_child_tasks), button);
    }

    return 0;
}

static void task_tree_ui_view_focus_task_name_set(GtkWidget* widget, gpointer new_name)
{
    g_print("set name from: '%s' to: '%s'\n", ui_view_focus_task->name, gtk_entry_buffer_get_text(new_name));
    memcpy(ui_view_focus_task->name, gtk_entry_buffer_get_text(new_name), sizeof(ui_view_focus_task->name));
}


//بسم الله الرحمن الرحيم

#include "../include/task_tree.h"
#include "../include/task_tree_ui.h"

#include <gtk-4.0/gtk/gtk.h>
#include <stdio.h>
#include <unistd.h>
//static bvriables
static struct task_t* static_task;
//end of static variables

//static functions
static int8_t task_tree_ui_task_set_name(GtkWidget* button,  GtkWidget* name_buff);
// end of static functions

GtkWidget* task_tree_ui_task_widget(struct task_t* task)
{
    if (NULL == task) {return NULL;}
    static_task = task;

    GtkWidget* frame = gtk_frame_new(task->name);
    GtkWidget* grid = gtk_grid_new();

    {//name (row=0)
        GtkWidget* label = gtk_label_new("name: ");
        gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);
        GtkWidget* name_buff = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(grid), name_buff, 1, 0, 1, 1);
        GtkWidget* button = gtk_button_new_with_label("change name");
        gtk_grid_attach(GTK_GRID(grid), button, 2, 0, 1, 1);
        g_signal_connect(button, "clicked", G_CALLBACK(task_tree_ui_task_set_name), name_buff);
    }
    {//progress (row=1)
        GtkWidget* label = gtk_label_new("progress :");
        gtk_grid_attach(GTK_GRID(grid), label, 0, 1, 1, 1);
        //GtkWidget* scale = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, NULL);
        GtkWidget* scale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, 100, 1);
        gtk_scale_set_value_pos(GTK_SCALE(scale), GTK_POS_LEFT);
        gtk_grid_attach(GTK_GRID(grid), scale, 1, 1, 2, 1);
    }
    gtk_frame_set_child(GTK_FRAME(frame), grid);
    return frame;
}

/*
void task_tree_ui_main_menu()
{

}
*/


//static functions
static int8_t task_tree_ui_task_set_name(GtkWidget* button, GtkWidget* name_buff)
{
    if(NULL == static_task) {return -1;}

    //I don't know why but it produces a bug otherwise
    const char* name = gtk_entry_buffer_get_text(GTK_ENTRY_BUFFER(gtk_entry_get_buffer(GTK_ENTRY(name_buff))));
    int8_t status = task_tree_task_set_name(static_task, name);
    return status;
}
// end of static functions


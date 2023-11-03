//بسم الله الرحمن الرحيم

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../submodules/task_tree_lib/include/task_t.h"
#include "../submodules/task_tree_lib/include/tlist.h"

const char* names_list[5] = {"BismiAllah", "Alah Akbar", "la ilaha illa Allah", "sub7an Allah", "astaghfiro Allah"};

int main()
{
    printf("in the name of Allah\n");
    struct tlist_t tlist;
    task_tree_tlist_init(&tlist);

    //printf("task id: %d\ntask name %s\n", tlist.data[0]->id, tlist.data[0]->name);

}


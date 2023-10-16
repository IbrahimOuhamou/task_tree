//بسم الله الرحمن الرحيم

#include <stdio.h>
#include <stdlib.h>
#include "../include/task_t.h"
#include "../include/tlist.h"

const char* names_list[5] = {"BismiAllah", "Alah Akbar", "la ilaha illa Allah", "sub7an Allah", "astaghfiro Allah"};

int main()
{
    printf("in the name of Allah\n");
    struct tlist_t tlist;
    tlist_init(&tlist);

    srand(time(NULL));

    for(int i = 0; i < 100; i++)
    {
        tlist_add_task(&tlist, newtask(names_list[rand() % 5]));
	tlist.data[i]->progress = rand() % 101;
    }

    for (int i = 0; i < tlist.size; i++)
    {
        printf("tlist[%d]: \n", i);
	printf("    id = %d\n", tlist.data[i]->id);
	printf("    name = %s\n", tlist.data[i]->name);
	printf("    progress = %u\n", tlist.data[i]->progress);
    }

    //printf("task id: %d\ntask name %s\n", tlist.data[0]->id, tlist.data[0]->name);

}


//بسم الله الرحمن الرحيم

#include <stdio.h>
#include "../include/task_t.h"
#include "../include/tlist.h"

int main()
{
    printf("in the name of Allah\n");
    struct tlist_t tlist;
    tlist_init(&tlist);
    tlist_add_task(&tlist, newtask("BismiAllah"));
    printf("Al7amdo li Allah: task added\n");

    //printf("task id: %d\ntask name %s\n", tlist.data[0]->id, tlist.data[0]->name);

}


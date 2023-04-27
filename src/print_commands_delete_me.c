
#include "../inc/minishell.h"
#include "../inc/parsing.h"

void print_comands()
{
    t_cmd *head;

    head = data.cmd_lst;
    int i = 0;
    while (head)
    {
        printf("command %d\n", i++);
        int i = 0;
        while (*(head->args))
        {
            printf("arg %d = %s\n", i++, *(head->args));
            head->args++;
        }
        printf("\n");
        head = head->next;
    }
}

// Do not forget to delete this file before submit the project

#include "../inc/minishell.h"
#include "../inc/parsing.h"

void print_tokens(t_elem *list)
{
    printf("%19s%10s%19s%14s\n", "CONTENT", "LEN", "TYPE", "STATE");
    printf("%*s-----------------------------------------------------\n", 10, " ");
    while (list)
    {
        int padding = 15 - list->len;
        printf("%*s::%s::", padding, " ", list->content);
        printf("%9d", list->len);
        switch (list->type)
        {
        case WORD:
            printf("%20s", "WORD");
            break;
        case REDIR_OUT:
            printf("%20s", "REDIR_OUT");
            break;
        case REDIR_IN:
            printf("%20s", "REDIR_IN");
            break;
        case DREDIR_OUT:
            printf("%20s", "DREDIR_OUT");
            break;
        case PIPE:
            printf("%20s", "PIPE");
            break;
        case HERE_DOC:
            printf("%20s", "HERE_DOC");
            break;
        case ENV:
            printf("%20s", "ENV");
            break;
        case D_QUOTE:
            printf("%20s", "D_QUOTES");
            break;
        case S_QUOTE:
            printf("%20s", "S_QUOTES");
            break;
        case WHITE_SPACE:
            printf("%20s", "WHITE_SPACE");
            break;
            case EMPTY:
            printf("%20s", "EMPTY");
            break;
        default:
            break;
        }

        switch (list->state)
        {
        case IN_DQUOTE:
            printf("%15s\n", "IN_DQUOTE");
            break;
        case IN_QUOTE:
            printf("%15s\n", "IN_QUOTE");
            break;
        case GENERAL:
            printf("%15s\n", "GENERAL");
            break;
        default:
            break;
        }
        list = list->next;
    }
        printf("%*s-----------------------------------------------------\n", 10, " ");
}
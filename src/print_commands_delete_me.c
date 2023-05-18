/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_commands_delete_me.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbin-nas <mbin-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:32:38 by mbin-nas          #+#    #+#             */
/*   Updated: 2023/05/16 14:32:41 by mbin-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void print_comands()
{
    t_cmd *head;

    head = data.cmd_lst;
    int i = 0;
    while (head)
    {
        printf("command %d\n", i++);
        int i = 0;
        // printf("arg %d = %s\n", i++, *(head->args));
        while (*(head->args))
        {
            printf("arg %d = %s\n", i++, *(head->args));
            head->args++;
        }
        printf("\n");
        head = head->next;
    }
}
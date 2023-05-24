/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbin-nas <mbin-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:33:26 by mbin-nas          #+#    #+#             */
/*   Updated: 2023/05/24 18:14:36 by mbin-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_ptr(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	free_str_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			if (tab[i])
			{
				free_ptr(tab[i]);
				tab[i] = NULL;
			}
			i++;
		}
		free(tab);
		tab = NULL;
	}
}

void	close_fds(t_cmd *cmds, bool close_backups)
{
	if (cmds->io_fds)
	{
		if (cmds->io_fds->fd_in != -1 && cmds->io_fds->fd_in != STDIN_FILENO)
			close(cmds->io_fds->fd_in);
		if (cmds->io_fds->fd_out != -1 && cmds->io_fds->fd_out != STDOUT_FILENO)
			close(cmds->io_fds->fd_out);
		if (close_backups)
			restore_io(cmds->io_fds);
	}
	if (g_data.heredoc_fd != -1)
	{
		close(g_data.heredoc_fd);
		g_data.heredoc_fd = -1;
	}
	close_pipe_fds(cmds, NULL);
}

void	lstdelone_token(t_elem *lst, void (*del)(void *))
{
	if (del && lst && lst->type != EMPTY)
	{
		(*del)(lst->content);
		lst->content = NULL;
	}
	if (lst->prev)
		lst->prev->next = lst->next;
	if (lst->next)
		lst->next->prev = lst->prev;
	free_ptr(lst);
}

void	lstclear_token(t_elem **lst, void (*del)(void *))
{
	t_elem	*tmp;

	tmp = NULL;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		lstdelone_token(*lst, del);
		*lst = tmp;
	}
}

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
		if (cmds->io_fds->fd_in != -1)
			close(cmds->io_fds->fd_in);
		if (cmds->io_fds->fd_out != -1)
			close(cmds->io_fds->fd_out);
		if (close_backups)
			restore_io(cmds->io_fds);
	}
	close_pipe_fds(cmds, NULL);
}

void close_child_fds(t_cmd *cmds)
{
    if (cmds->io_fds)
    {
        if (cmds->io_fds->fd_in != -1)
            close(cmds->io_fds->fd_in);
        if (cmds->io_fds->fd_out != -1)
            close(cmds->io_fds->fd_out);
    }
    close_pipe_fds(cmds, NULL);
}

void close_parent_fds(t_cmd *cmds)
{
    if (cmds->io_fds)
    {
        if (cmds->io_fds->stdin_backup != -1)
            close(cmds->io_fds->stdin_backup);
        if (cmds->io_fds->stdout_backup != -1)
            close(cmds->io_fds->stdout_backup);
        restore_io(cmds->io_fds); // Add this line
    }
}


void	free_io(t_io_fds *io)
{
	if (!io)
		return ;
	restore_io(io);
	if (io->infile)
		free_ptr(io->infile);
	if (io->outfile)
		free_ptr(io->outfile);
	if (io)
		free_ptr(io);
}

//free data ---> pending

void	lstdelone_token(t_elem *lst, void (*del)(void *))
{
	if (del && lst && lst->content)
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


void free_commands(t_cmd *cmds)
{
	t_cmd *tmp_cmd;
	char **tmp_str;
	
	if(cmds->io_fds)
		free_io(cmds->io_fds);
	while (cmds)
	{
		tmp_cmd = cmds;
		tmp_str = cmds->args;
		while (*(cmds->args))
			free(*(cmds->args)++);
		free(tmp_str);
		cmds = cmds->next;
		free(tmp_cmd);
	}
}


void free_data(t_data *data, t_cmd *cmds, bool flag)
{
    t_cmd *temp;

    if (data && data->input)
    {
        free(data->input);
        data->input = NULL;
    }
    if (data && data->tokens)
        lstclear_token(&data->tokens, &free_ptr);

    // Add the loop here to free io_fds for each command
    while (cmds)
    {
        free_io(cmds->io_fds);
        temp = cmds;
        cmds = cmds->next;
        free(temp);
    }

    if (flag == true)
    {
        if (data && data->current_dir)
            free_ptr(data->current_dir);
        if (data && data->old_working_dir)
            free_ptr(data->old_working_dir);
        if (data && data->env)
            free_str_tab(data->env);
        rl_clear_history();
    }
}

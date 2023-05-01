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
	if (io->heredoc_delimiter)
	{
		unlink(io->infile);
		free_ptr(io->heredoc_delimiter);
	}
	if (io->infile)
		free_ptr(io->infile);
	if (io->outfile)
		free_ptr(io->outfile);
	if (io)
		free_ptr(io);
}

//free data ---> pending
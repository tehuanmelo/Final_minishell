// #include "../../inc/minishell.h"
// void print_t_cmd(t_cmd *cmd) {

//     printf(COLOR_RED "------ We are inside of the CMD LIST ---- \n");
//     if (cmd == NULL) {
//         printf("Command is NULL\n");
//         printf(COLOR_RED "- ~~~~~~~~~~~~~ ~~~~~~~~~~~~ \n" COLOR_RESET);
//         return;
//     }

//     printf("command: %s\n", cmd->command);
//     printf("path: %s\n", cmd->path);
//     printf("pipe_fd[0]: %d\n", cmd->pipe_fd[0]);
//     printf("pipe_fd[1]: %d\n", cmd->pipe_fd[1]);

//     // if (cmd->io_fds != NULL) {
//     //     printf("io_fds->infile: %s\n", cmd->io_fds->infile);
//     //     printf("io_fds->outfile: %s\n", cmd->io_fds->outfile);
//     //     printf("io_fds->heredoc_delimiter: %s\n", cmd->io_fds->heredoc_delimiter);
//     //     printf("io_fds->heredoc_quotes: %d\n", cmd->io_fds->heredoc_quotes);
//     //     printf("io_fds->fd_in: %d\n", cmd->io_fds->fd_in);
//     //     printf("io_fds->fd_out: %d\n", cmd->io_fds->fd_out);
//     //     printf("io_fds->stdin_backup: %d\n", cmd->io_fds->stdin_backup);
//     //     printf("io_fds->stdout_backup: %d\n", cmd->io_fds->stdout_backup);
//     // }
//     // else {
//     //     printf("io_fds is NULL\n");
//     // }

//     if (cmd->args != NULL) {
//         printf("args: ");
//         for (int i = 0; cmd->args[i] != NULL; i++) {
//             printf("%s ", cmd->args[i]);
//         }
//         printf("\n");
//     }
//     else {
//         printf("args is NULL\n");
//     }

//     if (cmd->prev != NULL) {
//         printf("prev command: %s\n", cmd->prev->command);
//     }
//     else {
//         printf("prev command is NULL\n");
//     }

//     if (cmd->next != NULL) {
//         printf("next command: %s\n", cmd->next->command);
//     }
//     else {
//         printf("next command is NULL\n");
//     }
//     printf(COLOR_RED "- ~~~~~~~~~~~~~ ~~~~~~~~~~~~ \n" COLOR_RESET);
// }

// void print_t_elem(t_elem *elem) {

// printf(COLOR_BLUE "------ We are inside of the ELEM LIST ---- \n");
    
//     if (elem == NULL) {
//         printf("Element is NULL\n");
//         return;
//     }

//     printf("content: %s\n", elem->content);
//     // printf("content_backup: %s\n", elem->content_backup);
//     printf("len: %d\n", elem->len);
//     printf("type: %d\n", elem->type);
//     printf("state: %d\n", elem->state);

//     if (elem->next != NULL) {
//         printf("next element: %s\n", elem->next->content);
//     }
//     else {
//         printf("next element is NULL\n");
//     }

//     if (elem->prev != NULL) {
//         printf("prev element: %s\n", elem->prev->content);
//     }
//     else {
//         printf(COLOR_RESET "prev element is NULL\n");
//     }
// }


// void print_env_variables(char **env)
// {
//     for (int i = 0; env[i] != NULL; i++)
//     {
//         printf("env[%d]: %s\n", i, env[i]);
//     }
// }


// void print_t_data(t_data *data) {
//     printf(COLOR_MAGENTA "-------- We are inside of the Data list ---- \n");
//     printf("input: %s\n", data->input);
//     // printf("nb_cmd: %d\n", data->nb_cmd);
//     // printf("exit_code: %d\n", data->exit_code);
//     // printf("env:\n");
//     // for (int i = 0; data->env[i] != NULL; i++) {
//     //     printf("\t%s\n", data->env[i]);
//     // }
//     printf("current_dir: %s\n", data->current_dir);
//     printf("old_working_dir: %s\n", data->old_working_dir);
//     // print_t_elem(data->tokens);
//     // printf("pid: %d\n", data->pid);
//     print_t_cmd(data->cmd_lst);
// }

// // Assuming print_t_elem and print_t_cmd functions are already defined

// void print_file_contents(const char *filename)
// {
//     FILE *file;
//     int c;

//     file = fopen(filename, "r");
//     if (file == NULL)
//     {
//         //frprintf(stderr, "Error: unable to open file %s\n", filename);
//         return;
//     }

//     while ((c = fgetc(file)) != EOF)
//     {
//         putchar(c);
//     }

//     fclose(file);
// }

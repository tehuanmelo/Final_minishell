#include "../../inc/minishell.h"


/* create_memory_for_env_var
# @brief: 
* A new env variable will be stored by duplciating the env variable to the new_env
# @return: 
* A new_env_var_stored to be used 
* ----> To be used in the setting_the_envr when appending the new path or creating it  
*/

static char **create_memory_for_env_var(t_data *data, int size)
{
    char **new_env_var_stored;
    int    i;

    new_env_var_stored = ft_calloc(size + 1, sizeof * new_env_var_stored);
    if(!new_env_var_stored)
        return (NULL);
    i = 0;
    while(data->env[i] && i < size)
    {
        new_env_var_stored[i] = ft_strdup(data->env[i]);
        free(data->env[i]); //may have to check this leak 
        i++;
    }
    free(data->env);
    return (new_env_var_stored);
}

/* setting_the_env_var
# @brief: 
* This function can be used in export when new env vars are added
# @return: 
* a new set of env var maybe given by the user, therefore a new entry
* If the value exsist it will overwrite it therefore, no need for new entry
* -----> needs to be called for the cd built in or maybe other function
# @example
--> if create....(&data, "MY_VALUE", "myvalue")...........
--> will create ---> MY_VAR=my_value in the enviornment 
*/

bool create_the_new_env_var(t_data *data, char *env_key, char *value)
{
    int index; 
    char *temp; 

    index = fetch_env_variable_index(data->env, env_key);
    if(value == NULL)
        value = "";
    temp = ft_strjoin("=", value);
    if(!temp)
        return (false);
    if(index != -1 && data->env[index])
    {
        free(data->env[index]);
        data->env[index] = ft_strjoin(env_key, temp);
    }
    else
    {
        index = count_env_variables(data->env);
        data->env = create_memory_for_env_var(data, index + 1);
        if(!data->env)
            return (false);
        data->env[index] = ft_strjoin(env_key, temp);
    } 
    free(temp); //need to check this
    return (true);
}



/* delete_the_env_var
# @brief: 
* This function is used to delete the env variables
# @return: 
* Deletes the env variable path 
*/

bool delete_the_env_variables(t_data *data, int index)
{
    int i;
    int count;

    printf(COLOR_CYAN "Deleting the env \n");
    if(index > count_env_variables(data->env))
        return (false);
    free(data->env[index]);
    i = index;
    count = index;
    while(data->env[i + 1])
    {
        data->env[i] = ft_strdup(data->env[i + 1]);
        free(data->env[i + 1]); //may have to check for this
        count++;
        i++;
    }
    data->env = create_memory_for_env_var(data, count);
   
//    for (int i = 0; i < count; i++) {
//     printf(COLOR_MAGENTA "env[%d]: %s\n", i, data->env[i]);
//     }

    if(!data->env)
        return(false);
    return (true);
}

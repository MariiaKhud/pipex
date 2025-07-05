/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:02:37 by makhudon          #+#    #+#             */
/*   Updated: 2025/07/04 14:32:03 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../src/pipex.h"

/* Print perror(msg) then exit(EXIT_FAILURE) */
void	error_exit(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

/* Print msg to stderr then exit(EXIT_FAILURE) */
void	error_msg_exit(const char *msg)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd((char *)msg, 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

/* Join dir + "/" + cmd */
static char	*join_path(const char *dir, const char *cmd)
{
	size_t	len;
	char	*full;

	len = ft_strlen(dir) + 1 + ft_strlen(cmd) + 1;
	full = malloc(len);
	if (!full)
		return (NULL);
	ft_strlcpy(full, dir, len);
	ft_strlcat(full, "/", len);
	ft_strlcat(full, cmd, len);
	return (full);
}

/* Given cmd (e.g. "ls") and array of PATH dirs, return full path or NULL */
char	*find_cmd_path(char *cmd, char **paths)
{
	char	*full;
	int		i;

	i = 0;
	while (paths && paths[i])
	{
		full = join_path(paths[i], cmd);
		if (!full)
			error_exit("malloc");
		if (access(full, X_OK) == 0)
			return (full);
		free(full);
		i++;
	}
	return (ft_strdup(cmd));
}

/* Free a NULL-terminated array of strings */
void	free_split(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

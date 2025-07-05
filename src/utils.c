/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:02:37 by makhudon          #+#    #+#             */
/*   Updated: 2025/07/05 15:34:41 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../src/pipex.h"

void	error_exit(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	error_msg_exit(const char *msg)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	ft_putstr_fd((char *)msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
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

char	*find_cmd_path(char *cmd, char **path_dirs)
{
	char	*full;
	int		i;

	i = 0;
	while (path_dirs && path_dirs[i])
	{
		full = join_path(path_dirs[i], cmd);
		if (!full)
			error_exit("malloc");
		if (access(full, X_OK) == 0)
			return (full);
		free(full);
		i++;
	}
	return (ft_strdup(cmd));
}

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

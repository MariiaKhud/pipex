/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:55:56 by makhudon          #+#    #+#             */
/*   Updated: 2025/07/04 14:31:26 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../src/pipex.h"

static void	handle_execve_error(char *cmd_path, char **args, char **paths)
{
	int	exit_status;

	if (errno == ENOENT)
	{
		write(STDERR_FILENO, cmd_path, ft_strlen(cmd_path));
		write(STDERR_FILENO, " : command not found\n", 22);
		exit_status = 127;
	}
	else
	{
		perror(cmd_path);
		exit_status = 1;
	}
	free_split(paths);
	free_split(args);
	free(cmd_path);
	exit(exit_status);
}

static void	execute_cmd(char *cmd_p, char **args, char **paths, char **envp)
{
	if (!cmd_p)
	{
		free_split(paths);
		free_split(args);
		error_msg_exit(args[0]);
	}
	execve(cmd_p, args, envp);
	handle_execve_error(cmd_p, args, paths);
}

/* Split PATH into an array of directories */
static char	**get_paths(char **envp)
{
	int		i;
	char	*path_value;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	path_value = envp[i] + 5;
	return (ft_split(path_value, ':'));
}

void	run_last_child(int pipe_fd[2], char **argv, char **envp)
{
	int		output_fd;
	char	**args;
	char	**paths;
	char	*cmd_path;

	output_fd = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (output_fd < 0)
		error_exit(argv[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	dup2(output_fd, STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(output_fd);
	args = ft_split(argv[0], ' ');
	if (!args || !*args)
		error_msg_exit("command parse error");
	paths = get_paths(envp);
	cmd_path = find_cmd_path(args[0], paths);
	execute_cmd(cmd_path, args, paths, envp);
}

void	run_first_child(int pipe_fd[2], char **argv, char **envp)
{
	int		input_fd;
	char	**args;
	char	**paths;
	char	*cmd_path;

	input_fd = open(argv[0], O_RDONLY);
	if (input_fd < 0)
		error_exit(argv[0]);
	dup2(input_fd, STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(input_fd);
	args = ft_split(argv[1], ' ');
	if (!args || !*args)
		error_msg_exit("command parse error");
	paths = get_paths(envp);
	cmd_path = find_cmd_path(args[0], paths);
	execute_cmd(cmd_path, args, paths, envp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:09:59 by makhudon          #+#    #+#             */
/*   Updated: 2025/07/04 14:24:55 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../src/pipex.h"

static int	wait_for_children(pid_t first_pid, pid_t last_pid)
{
	int	status;

	waitpid(first_pid, NULL, 0);
	waitpid(last_pid, &status, 0);
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

static int	last_child(int pipe_fd[2], char **argv, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (pid);
	if (pid == 0)
		run_last_child(pipe_fd, argv, envp);
	return (pid);
}

static int	first_child(int pipe_fd[2], char **argv, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (pid);
	if (pid == 0)
		run_first_child(pipe_fd, argv, envp);
	return (pid);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	pid_t	first_pid;
	pid_t	last_pid;

	if (argc != 5)
		error_msg_exit("Usage: ./pipex file1 cmd1 cmd2 file2");
	if (pipe(pipe_fd) == -1)
		error_exit("pipe");
	first_pid = first_child(pipe_fd, argv + 1, envp);
	if (first_pid < 0)
		error_exit("fork first");
	last_pid = last_child(pipe_fd, argv + 3, envp);
	if (last_pid < 0)
	{
		waitpid(first_pid, NULL, 0);
		error_exit("fork second");
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (wait_for_children(first_pid, last_pid));
}

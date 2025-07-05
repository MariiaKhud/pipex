/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:10:15 by makhudon          #+#    #+#             */
/*   Updated: 2025/07/04 14:31:14 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/wait.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>

void	error_exit(const char *msg);
void	error_msg_exit(const char *msg);
char	*find_cmd_path(char *cmd, char **paths);
void	free_split(char **array);
void	run_first_child(int pipe_fd[2], char **argv, char **envp);
void	run_last_child(int pipe_fd[2], char **argv, char **envp);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 08:00:56 by aben-hss          #+#    #+#             */
/*   Updated: 2024/07/30 19:39:34 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>

void	command_not_found(char *command);
void	error_exit(char *message);
int		open_infile(char *file);
int		open_outfile(char *file);
char	**get_env_paths(char **env);
char	*get_path(char **env, char *av);
void	child1(char **env, char **av, int *fd);
void	child2(char **env, char **av, int *fd);
void	error_exit(char *message);

#endif
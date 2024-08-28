/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 19:21:48 by aben-hss          #+#    #+#             */
/*   Updated: 2024/08/15 06:26:54 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_infile(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_exit(ft_strdup(file));
	return (fd);
}

int	open_outfile(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		error_exit(ft_strdup(file));
	return (fd);
}

char	**get_env_paths(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (ft_split(ft_strchr(env[i], '=') + 1, ':'));
		i++;
	}
	return (NULL);
}

char	*get_path(char **env, char *av)
{
	char	**env_paths;
	char	*cmnd;
	char	*temp;
	int		i;

	if (ft_strchr(av, '/'))
		return (ft_strdup(av));
	env_paths = get_env_paths(env);
	if (!env_paths)
		return (NULL);
	cmnd = ft_strjoin("/", av);
	i = 0;
	while (env_paths[i])
	{
		temp = ft_strjoin(env_paths[i], cmnd);
		if (!access(temp, X_OK))
			return (dealloc(env_paths), free(cmnd), temp);
		free (temp);
		i++;
	}
	free(cmnd);
	dealloc(env_paths);
	return (NULL);
}

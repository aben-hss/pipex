/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 08:21:51 by aben-hss          #+#    #+#             */
/*   Updated: 2024/08/17 04:58:55 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Function to handle and display "command not found" errors
void    command_not_found(char *command)
{
    ft_putstr_fd("pipex: ", 2);
    ft_putstr_fd(command, 2);
    ft_putstr_fd(": command not found\n", 2);
}

// Function to handle and display general errors, then exit the program
void    error_exit(char *message)
{
    ft_putstr_fd("pipex: ", 2);
    perror(message);
    free(message);
    exit(1);
}

// Function to handle the first child process
void    child1(char **env, char **av, int *fd)
{
    int     infile;
    char    *full_cmd;
    char    **args;

    close(fd[0]);  // Close read end of pipe
    args = ft_split(av[2], ' ');  // Split the command and its arguments
    infile = open_infile(av[1]);  // Open input file
    if (dup2(infile, 0) == -1)
        exit(1);  // Redirect stdin to input file
    close(infile);
    if (dup2(fd[1], 1) == -1)
        exit(1);  // Redirect stdout to write end of pipe
    close(fd[1]);
    full_cmd = get_path(env, *args);  // Get full path of the command
    if (!full_cmd)
        return (command_not_found(*args), dealloc(args));
    if (execve(full_cmd, args, env) == -1)
        return (dealloc(args), error_exit(full_cmd));
}

// Function to handle the second child process
void    child2(char **env, char **av, int *fd)
{
    int     outfile;
    char    *full_cmd;
    char    **args;

    close(fd[1]);  // Close write end of pipe
    args = ft_split(av[3], ' ');  // Split the command and its arguments
    outfile = open_outfile(av[4]);  // Open output file
    if (dup2(outfile, 1) == -1)
        exit(1);  // Redirect stdout to output file
    close(outfile);
    if (dup2(fd[0], 0) == -1)
        exit(1);  // Redirect stdin to read end of pipe
    close(fd[0]);
    full_cmd = get_path(env, *args);  // Get full path of the command
    if (!full_cmd)
        return (command_not_found(*args), dealloc(args));
    if (execve(full_cmd, args, env) == -1)
        return (dealloc(args), error_exit(full_cmd));
}

int main(int ac, char **av, char **env)
{
    int fd[2];
    int pid;
    int pid2;

    if (ac != 5 || env == NULL)
        return (1);  // Check for correct number of arguments and environment
    if (pipe(fd) == -1)
        exit(1);  // Create pipe
    pid = fork();
    if (!pid)
    {
        child1(env, av, fd);  // First child process
        exit(0);
    }
    else
    {
        pid2 = fork();
        if (!pid2)
        {
            child2(env, av, fd);  // Second child process
            exit(0);
        }
    }
    // Parent process
    return (close(fd[0]), close(fd[1]), wait(NULL), wait(NULL), 0);
}

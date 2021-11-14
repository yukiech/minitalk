/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuber <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 08:49:32 by ahuber            #+#    #+#             */
/*   Updated: 2021/11/14 15:25:06 by ahuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	char_sender(pid_t pid, char c)
{
	int	bit;

	bit = 7;
	while (bit != -1)
	{
		if (c & (1 << bit))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		bit--;
		usleep(100);
	}
}

static void	input_sender(pid_t pid, char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		char_sender(pid, input[i]);
		i++;
	}
	char_sender(pid, '\0');
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	char	*input;

	if (argc != 3)
		return (0);
	pid = ft_atoi(argv[1]);
	input = argv[2];
	input_sender(pid, input);
	return (0);
}

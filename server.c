/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuber <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 08:58:25 by ahuber            #+#    #+#             */
/*   Updated: 2021/11/14 15:22:22 by ahuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	send_bit(int signal)
{
	static char	buffer[10000000] = {'\0', };
	static int	bit = 7;
	static int	i = 0;

	if (signal == SIGUSR1)
		buffer[i] = buffer[i] | (1 << bit);
	if (signal == SIGUSR2)
		buffer[i] = buffer[i] & ~(1 << bit);
	bit -= 1;
	if (bit == -1)
	{
		bit = 7;
		if (buffer[i] == '\0')
		{
			write(1, buffer, i);
			i = 0;
		}
		else
			i++;
	}
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	signal(SIGUSR1, send_bit);
	signal(SIGUSR2, send_bit);
	while (1)
		sleep(1000);
	return (0);
}

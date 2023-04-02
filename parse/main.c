/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 18:48:00 by mmourdal          #+#    #+#             */
/*   Updated: 2023/04/02 19:52:17 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int main(int argc, char **argv)
{
	(void)argc;
	printf("-> %d\n\n", ft_atoi(argv[1]));
	ft_putnbr_fd(ft_atoi(argv[1]), 1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 22:17:23 by mmourdal          #+#    #+#             */
/*   Updated: 2023/04/08 16:54:17 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * La fonction split découpe une chaine de caractère (*s) suivant un délimiteur
 * donner en parametre (c), elle retourne un tableau de chaines de caractères
 * alloué dynamiquement et qui termine par un '\0'.
*/

static int	is_c(char chr, char c)
{
	if (chr == c || c == '\t')
		return (1);
	return (0);
}

static int	get_size(char const *s, char c)
{
	size_t	i;
	size_t	cpt;

	cpt = 1;
	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (is_c(c, s[i]) == 1 && s[i])
			i++;
		if (s[i] == '\0')
			break ;
		while (is_c(c, s[i]) == 0 && s[i])
			i++;
		cpt++;
	}
	return (cpt);
}

static char	**in_case(char **tab, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = 0;
	return (tab);
}

char	**ft_split(char const *s, char c, int *size)
{
	char	**tab;
	int		i;
	int		j;
	int		start;

	j = 0;
	i = 0;
	*size = get_size(s, c) - 1;
	tab = malloc(sizeof(char *) * (*size + 1));
	if (!tab || !s)
		return (NULL);
	while (j < (*size + 1) && s[i])
	{
		while (is_c(c, s[i]) == 1 && s[i])
			i++;
		if (s[i] == '\0')
			break ;
		start = i;
		while (is_c(c, s[i]) == 0 && s[i])
			i++;
		tab[j] = ft_substr(s, start, i - start);
		if (!tab[j++])
			return (in_case(tab, j - 1));
	}
	tab[j] = 0;
	return (tab);
}

/*
int	main(void)
{
	char	**result;
	int		i;
	printf("\n************ FT_SPLIT ***********\n");
	printf("Separateur : '-' | Chaine : \"Salut----Les----Terriens----\" : \n");
	result = ft_split("Salut----Les----Terriens----", '-');
	i = -1;
	while (result[++i])
		printf("Index : %d => %s\n", i, result[i]);
	printf("\nSeparateur : '/' | Chaine : \"4242 1///42!!42 2//42 3\" : \n");
	result = ft_split("4242 1///42!!42 2//42 3", '/');
	i = -1;
	while (result[++i])
		printf("Index : %d => %s\n", i, result[i]);
	printf("*********************************\n\n");
}
*/

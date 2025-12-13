/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luimarti <luimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:29:33 by luimarti          #+#    #+#             */
/*   Updated: 2025/11/25 09:38:05 by luimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

size_t	ft_strlen_and_find_newline(const char *str, int *find_newline)
{
	size_t	len;

	len = 0;
	*find_newline = 0;
	if (!str)
		return (0);
	while (str[len])
	{
		if (str[len] == '\n')
			*find_newline = 1;
		len++;
	}
	return (len);
}

char	*ft_strdup(const char *s)
{
	size_t		length;
	size_t		i;
	char		*copy;

	length = 0;
	i = 0;
	if (!s)
		return (NULL);
	while (s[length] != '\0')
	{
		length++;
	}
	copy = (char *)malloc((length + 1) * sizeof(char));
	if (copy == NULL)
		return (NULL);
	while (i <= length)
	{
		copy[i] = s[i];
		i++;
	}
	return (copy);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	if (!src)
		return (NULL);
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcat(char *dest, char *src)
{
	char	*beginning;

	beginning = dest;
	while (*dest != '\0')
		dest++;
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (beginning);
}

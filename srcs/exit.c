/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:02:34 by ablanar           #+#    #+#             */
/*   Updated: 2020/02/26 21:00:07 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		isnum(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!((str[i] >= '0' && str[i] <= '9') || str[i] == '-' ||
									str[i] == '+'))
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int		nbr;
	int		sign;

	nbr = 0;
	sign = 1;
	while ((*str) == '\t' || (*str) == '\n' || (*str) == '\v' || (*str) == '\f'
			|| (*str) == '\r' || (*str) == ' ')
		str++;
	if ((*str) == '-' || (*str) == '+')
	{
		sign *= ((*str) == '-' ? -1 : 1);
		str++;
	}
	while ((*str) != '\0' && (*str) >= '0' && (*str) <= '9')
	{
		nbr *= 10;
		nbr += (*str) - '0';
		str++;
	}
	return (nbr * sign);
}

void 	clean_quotes(char **tokens)
{
	int i;
	int spec;

	i = 0;
	spec = next_spec(tokens);
	if (spec == -1)
		spec = ft_tablen(tokens);
	while (i < spec)
	{
		tokens[i] = ft_copy_without_quotes(tokens[i]);
		i++;
	}
}

void	ft_exit(char **tokens, int status, t_info *info)
{
	char ret;
	int special;

	special = next_redir(tokens);
	clean_quotes(tokens);
	if (special != -1)
		recursive_madness(tokens, -1, 1, info, 0);
	if (tokens[1] == NULL)
		status = 0;
	else if (isnum(tokens[1]))
		status = ft_atoi(tokens[1]);
	else
		status = 255;

	write(1, "exit\n", 5);
	if (status == 255)
	{
		ft_puterr("our sh: exit: ");
		ft_puterr(tokens[1]);
		ft_puterr(": numeric argument required\n");
	}
	else if (tokens[2] != NULL && (special > 2 || special == -1))
	{
		ft_puterr("our sh: exit: ");
		ft_puterr(tokens[1]);
		ft_puterr(": too many arguments\n");
		info->status = 1;
		return ;
	}
	ret = (char) status;
	exit(ret);
}

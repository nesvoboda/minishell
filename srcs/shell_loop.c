/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 13:10:45 by ashishae          #+#    #+#             */
/*   Updated: 2020/03/02 16:31:26 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_count_without_quotes(char *token)
{
	int		i;
	int		q[3];
	int		count;
	char	prev;

	i = 0;
	ft_set_to_zero(&i, q, &count, &prev);
	while (token[i])
	{
		if ((token[i] != '\'' || (q[2] > 0 || q[1])) &&
			(token[i] != '"' || (q[2] > 0 || q[0])) &&
			(token[i] != '\\' || (q[2] > 0 || q[0] ||
			(q[1] && !double_cond(token[i + 1])))))
			count++;
		else if (token[i] == '\\' && (double_cond(token[i + 1])) && q[1] != 0
							&& q[2] == 0 && q[0] != 1)
			count++;
		if ((token[i] == '\'' || token[i] == '"' || token[i] == '\\') &&
																	q[2] == 0)
			set_quotes(&token[i], q, i);
		if (q[2] != i + 1)
			q[2] = 0;
		i++;
	}
	return (count);
}

void	copy_without(char *token, char *new, int *q, char prev)
{
	int i;
	int j;

	prev = '\0';
	i = 0;
	j = 0;
	while (token[i])
	{
		if ((token[i] != '\'' || (q[2] > 0 || q[1])) && (token[i] != '"' ||
			(q[2] > 0 || q[0])) && (token[i] != '\\' || (q[2] > 0 || q[0] ||
					(q[1] && !double_cond(token[i + 1])))))
			new[j++] = token[i];
		else if (token[i] == '\\' && (double_cond(token[i + 1])) &&
									q[1] != 0 && q[2] == 0 && q[0] != 1)
			new[j++] = token[++i];
		else if ((token[i] == '\'' || token[i] == '"' || token[i] == '\\')
																&& q[2] == 0)
			set_quotes(&token[i], q, i);
		if (q[2] != i + 1)
			q[2] = 0;
		i++;
	}
	new[j] = '\0';
}

char	*ft_copy_without_quotes(char *token)
{
	int		quote[3];
	char	*new;
	char	prev;

	quote[0] = 0;
	quote[1] = 0;
	quote[2] = 0;
	prev = '\0';
	if (!(new = malloc(sizeof(char) * ft_count_without_quotes(token) + 1)))
		return (NULL);
	copy_without(token, new, quote, prev);
	free(token);
	return (new);
}

void	vpered(char **com, int fd, int output, t_info *info)
{
	char **new_com;

	new_com = ft_tabdup(com);
	check_var(&new_com, info->our_env, info);
	if (new_com[0] != NULL)
		new_com[0] = ft_copy_without_quotes(new_com[0]);
	if (new_com[0] != NULL)
		execute(new_com, fd, output, info);
	free_split(new_com);
}

void	shell_loop_2(t_info *info)
{
	char	**com;
	int		i;

	i = 0;
	info->last_char = 0;
	while (1)
	{
		write(1, "> ", 2);
		g_flag = 1;
		signal(SIGINT, inthandler);
		signal(SIGQUIT, quit_handler);
		com = ft_get_command(info);
		if (com && com[0] && check_last_fd(com, &info->status) == 0)
			vpered(com, -1, 1, info);
		if (com[0])
		{
			free_split(com);
		}
		else
			free(com);
	}
}

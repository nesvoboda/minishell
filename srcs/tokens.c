#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
void ft_tabcpy(char **dst, char **src)
{
	int i;

	i = 0;
	if (src == NULL)
		return ;
	while (src[i] != NULL)
	{
		dst[i] = strdup(src[i]);
		free(src[i]);
		i++;
	}
}

int		ft_tablen(char **tab)
{
	int i;

	i = 0;
	if (tab == NULL)
		return (0);
	while (tab[i] != NULL)
		i++;
	return (i);
}
int ft_strlen(char *line)
{
	int i;

	i = 0;
	if (line == NULL)
		return (0);
	while (line[i])
		i++;
	return (i);
}

char  *ft_add_char(char **line, char c)
{
	char *new;
	int i;


	if (!(new = malloc(sizeof(char) * ft_strlen(*line) + 2)))
	{
		free(*line);
		return (NULL);
	}
	i = 0;
	if (*line != NULL)
	{
		while ((*line)[i])
		{
			new[i] = (*line)[i];
			i++;
		}
	}

	new[i] = c;
	new[i + 1] = '\0';
	if (line != NULL)
		free(*line);
	*line = new;
	return (*line);
}

void ft_start_input(char **input, char *prev, char ***tokens)
{
	*input = NULL;
	*prev = '\0';
	*tokens = NULL;
}

char **ft_create_token(char ***tokens, char *buf, char **input)
{
	char **new;
	int size;
	char *delim;

	size = ft_tablen(*tokens);
	new = malloc(sizeof(char *) * (size + 3));
	ft_tabcpy(new, *tokens);
	if (*input != NULL)
	{
		new[size] = *input;
		if (*buf != '\n' && *buf != ' ')
		{
			delim = malloc(sizeof(char) * 2);
			delim[0] = buf[0];
			delim[1] = '\0';
			new[size + 1] = delim;
			new[size + 2] = NULL;
		}
		else
			new[size + 1] = NULL;
	}
	else
	{
		if (*buf != '\n' && *buf != ' ')
		{
			delim = malloc(sizeof(char) * 2);
			delim[0] = buf[0];
			delim[1] = '\0';
			new[size] = delim;
			new[size + 1] = NULL;
		}
		else
			new[size] = NULL;
	}


	*input = NULL;
	if (*tokens != NULL)
		free(*tokens);
	*tokens = new;
	buf[0] = ' ';
	return (*tokens);
}

char **ft_get_command()
{
	char buf;
	char prev;
	char *input;
	int sq = 0;
	int dq = 0;
	char **tokens;

	ft_start_input(&input, &prev, &tokens);
	while (read(0, &buf, 1))
	{

		if (buf == '\n' && prev != '\\' && sq == 0 && dq == 0)
			return (ft_create_token(&tokens, &buf, &input));
		if (buf == '\n' && (sq == 1 || dq == 1))
			write(1, "> ", 2);
		if ((buf == ';' || (buf == '>') || buf == '<' || buf == '|' || buf == ' ') && (dq == 0 && sq == 0 && prev != '\\'))
			ft_create_token(&tokens, &buf, &input);
		if (buf == '\'' && sq == 0 && prev != '\\')
			sq = 1;
		else if (buf == '\'' && sq == 1)
			sq = 0;
		if (buf == '\"' && dq == 0 && prev != '\\')
			dq = 1;
		else if (buf == '\"' && dq == 1 && prev != '\\')
			dq = 0;
		if (!((buf == ';' || (buf == '>') || buf == '<' || buf == '|' || buf == ' ' || buf == '\\' || buf == '\n')) || sq == 1 || dq == 1)
			ft_add_char(&input, buf);
		prev = buf;
	}
	return (tokens);
}

int main()
{
	char **com;
	int i;

	i = 0;
	while (1)
	{
		write(1, "> ", 2);
		com = ft_get_command();
		while (com[i] != NULL)
		{
			printf("token%d %s\n",i, com[i]);
			i++;
		}
		i = 0;
	}
	return (0);
}

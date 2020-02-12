#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "../includes/minishell.h"

void redirect_all_std(void);

Test(tokens, tabcpy)
{
	char **src = malloc(sizeof(char *) * 3);
	src[0] = strdup("Hello ");
	src[1] = strdup("world");
	src[2] = NULL;
	char **dst = malloc(sizeof(char *) * 3);

	ft_tabcpy(dst, src);
	cr_assert_str_eq(dst[0], "Hello ");
	cr_assert_str_eq(dst[1], "world");
	cr_assert_eq(dst[2], NULL);
}

Test(tokens, tabcpy2)
{
	char **src = NULL;
	char *dst[] = {"Untouchable", NULL};

	ft_tabcpy(dst, src);
	cr_assert_str_eq(dst[0], "Untouchable");
	cr_assert_eq(dst[1], NULL);
}

Test(tokens, tablen)
{
	char *array[] = {"One", "Two", "Three", NULL};
	int actual;

	actual = ft_tablen(array);
	cr_assert_eq(actual, 3);
}

Test(tokens, strlen)
{
	char *str = "Hello world!";

	cr_assert_eq(ft_strlen(str), (int)strlen(str));
}

Test(tokens, ft_add_char)
{
	char *str = strdup("Hello worl");

	ft_add_char(&str, 'd');
	cr_assert_str_eq("Hello world", str);
}

Test(tokens, ft_start_input)
{
	char prev = 'a';
	char *input = "Yo what's up";
	char **tokens = &input;
	int q[2];

	ft_start_input(&input, &prev, &tokens, q);
	cr_assert_eq(input, NULL);
	cr_assert_eq(prev, 0);
	cr_assert_eq(tokens, NULL);
	cr_assert_eq(q[0], 0);
	cr_assert_eq(q[1], 0);
}
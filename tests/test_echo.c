#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "../includes/minishell.h"

void redirect_all_std(void);

Test(echo, e_t1, .init = redirect_all_std)
{
	char *tokens[3] = {"echo", "hello", NULL};
	ft_echo(tokens, 1);
	cr_assert_stdout_eq_str("hello\n");
}

Test(echo, e_t2, .init = redirect_all_std)
{
	char *tokens[4] = {"echo", "-n", "hello", NULL};
	ft_echo(tokens, 1);
	cr_assert_stdout_eq_str("hello");
}

Test(echo, e_t3, .init = redirect_all_std)
{
	char *tokens[4] = {"echo", "one", "two", NULL};
	ft_echo(tokens, 1);
	cr_assert_stdout_eq_str("one two\n");
}
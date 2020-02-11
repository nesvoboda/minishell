#include <criterion/criterion.h>

#include "../includes/minishell.h"

Test(compare_tokens, is)
{
	cr_assert_eq(is("a", "a"), 1);
	cr_assert_eq(is("a", "b"), 0);
	cr_assert_eq(is("ab", "b"), 0);
	cr_assert_eq(is("Hello world!", "Hello world!"), 1);
	cr_assert_eq(is("Hello world!", "Hello xorld!"), 0);
}

Test(compare_tokens, is_special)
{
	cr_assert_eq(is_special("a"), 0);
	cr_assert_eq(is_special(";"), 1);
	cr_assert_eq(is_special(">"), 1);
	cr_assert_eq(is_special(">>"), 1);
	cr_assert_eq(is_special("|"), 1);
	cr_assert_eq(is_special("<"), 1);
	cr_assert_eq(is_special(""), 0);
}

Test(compare_tokens, next_special)
{
	char *tokens[5] = {"a", "b", ";", "d", NULL};
	cr_assert_eq(next_special(tokens), 2);
}

Test(compare_tokens, next_special2)
{
	char *tokens[5] = {"a", "b", "c", "d", NULL};
	cr_assert_eq(next_special(tokens), -1);
}
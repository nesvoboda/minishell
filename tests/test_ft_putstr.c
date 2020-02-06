#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../includes/minishell.h"


void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(ft_putstr, tputstr_1, .init = redirect_all_std) {
    ft_putstr("Hello world!");
    cr_assert_stdout_eq_str("Hello world!");
}
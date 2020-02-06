#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "../includes/minishell.h"

void redirect_all_std(void);

// Test(exec, e_t1, .init=redirect_all_std)
// {
// 	char *tokens[3] = {"/bin/echo", "test", 0};

// 	ft_exec(tokens);
// 	cr_assert_stdout_eq_str("test\n");
// }

Test(exec, e_t2, .init=redirect_all_std)
{
	char *tokens[3] = {"nowhere", "test", 0};

	ft_exec(tokens);
	cr_assert_stderr_eq_str("No such file or directory\n");
}
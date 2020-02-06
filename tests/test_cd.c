#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "../includes/minishell.h"

void redirect_all_std(void);

Test(cd, c_t1)
{
	char *tokens[3] = {"cd", "/", NULL};
	ft_cd(tokens);
	cr_assert_str_eq("/", getcwd(NULL, 0));
}

Test(cd, c_t2, .init = redirect_all_std)
{
	char *tokens[3] = {"cd", "nowhere", NULL};
	ft_cd(tokens);
	cr_assert_stderr_eq_str("No such file or directory\n");
}
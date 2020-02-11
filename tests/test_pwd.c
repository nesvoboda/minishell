#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "../includes/minishell.h"

void redirect_all_std(void);
char	*ft_strjoin(char *s1, char *s2);

Test(pwd, pwd_t1) {
	cr_log_info("Actual path:   %s\n", pwd());
	cr_log_info("Expected path: %s\n", getcwd(NULL, 0));
	cr_assert_str_eq(pwd(), getcwd(NULL, 0));
}

Test(pwd, print_pwd, .init=redirect_all_std) {
	char *expected = ft_strjoin(getcwd(NULL, 0), "\n");
	print_pwd(1);
	cr_assert_stdout_eq_str(expected);
}
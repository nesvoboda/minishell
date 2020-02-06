#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../includes/minishell.h"
#include <fcntl.h>
#include <string.h>

void redirect_all_std(void);

Test(tokenize, t_t1)
{
	int fd = open("./tests/t_t1", O_RDONLY);
	char **tokens;
	int ret;
	cr_log_info("FD is %d\n", fd);
	tokens = tokenize(fd, &ret);
	cr_assert_str_eq(tokens[0], "hello");
	cr_assert_str_eq(tokens[1], "world!");
	cr_assert(tokens[2] == NULL);
}

Test(shell_loop, sl_t1, .init=redirect_all_std)
{
	int fd = open("./tests/sl_t1", O_RDONLY);
	shell_loop(fd);
	cr_assert_stdout_eq_str("> test\n> ");
}

Test(shell_loop, sl_t2, .init=redirect_all_std)
{
	int fd = open("./tests/sl_t2", O_RDONLY);
	char *pwd;
	char *expected;
	int		path_end;
	int		expected_size;

	pwd = getcwd(NULL, 0);
	expected_size = strlen(pwd) + 6;
	expected = malloc(sizeof(char) * (expected_size));

	expected[0] = '>';
	expected[1] = ' ';
	ft_strlcpy(&expected[2], pwd, expected_size-3);
	path_end = strlen(pwd)+1;
	expected[path_end+1] = '\n';
	expected[path_end+2] = '>';
	expected[path_end+3] = ' ';
	expected[path_end+4] = '\0';

	shell_loop(fd);
	cr_assert_stdout_eq_str(expected);
}
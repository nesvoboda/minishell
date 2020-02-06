#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../includes/minishell.h"
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

void redirect_all_std(void);

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_size;
	char	*result;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	total_size = strlen(s1) + strlen(s2) + 1;
	if ((result = malloc(sizeof(char) * total_size)) == NULL)
		return (NULL);
	memcpy(result, s1, strlen(s1));
	memcpy((result + strlen(s1)), s2, strlen(s2));
	result[total_size - 1] = '\0';
	return (result);
}

Test (ft_strjoin, fs_t1)
{
	char *result;
	result = ft_strjoin("hello ", "world");
	cr_assert_str_eq(result, "hello world");
	free(result);
	result = ft_strjoin(NULL, "test");
	cr_assert_eq(result, NULL);
	result = ft_strjoin("test", NULL);
	cr_assert_eq(result, NULL);
}

char *expected_pwd_output(char *custom_pwd)
{
	char *pwd;
	char *expected;
	int		path_end;
	int		expected_size;

	if (!custom_pwd)
		pwd = getcwd(NULL, 0);
	else
		pwd = custom_pwd;
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
	return (expected);
}


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
	close(fd);
}

Test(shell_loop, sl_t1, .init=redirect_all_std)
{
	int fd = open("./tests/sl_t1", O_RDONLY);
	shell_loop(fd);
	cr_assert_stdout_eq_str("> test\n> ");
	close(fd);
}

Test(shell_loop, sl_t2, .init=redirect_all_std)
{
	int fd = open("./tests/sl_t2", O_RDONLY);
	char *expected_pwd = expected_pwd_output(NULL);

	shell_loop(fd);
	cr_assert_stdout_eq_str(expected_pwd);
	free(expected_pwd);
	close(fd);
}

Test(shell_loop, sl_t3, .init=redirect_all_std)
{
	int fd = open("./tests/sl_t3", O_RDONLY);
	char *expected_pwd = expected_pwd_output("/");
	char *expected_output = ft_strjoin("> ", expected_pwd);

	shell_loop(fd);
	cr_assert_stdout_eq_str(expected_output);
	close(fd);
}

Test(shell_loop, sl_t4, .init=redirect_all_std)
{
	int fd = open("./tests/sl_t4", O_RDONLY);

	shell_loop(fd);
	cr_assert_stdout_eq_str("> exit\n");
	close(fd);
}

Test(shell_loop, sl_t5, .init=redirect_all_std)
{
	int fd = open("./tests/sl_t5", O_RDONLY);

	shell_loop(fd);
	cr_assert_stdout_eq_str("> test\n> ");
	close(fd);
}

Test(shell_loop, sl_t6, .init=redirect_all_std)
{
	shell_loop(-1);
	cr_assert_stdout_eq_str("> ");
}
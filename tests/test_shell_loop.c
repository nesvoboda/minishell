#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../includes/minishell.h"
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

void redirect_all_std(void);

char	*ft_strjoin(char const *s1, char const *s2);

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
#include <criterion/criterion.h>
#include "../includes/minishell.h"
#include <fcntl.h>

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
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../includes/minishell.h"
#include <fcntl.h>

void redirect_all_std(void);

Test(redirect, redir)
{
	int actual_fd;

	actual_fd = redir("test_file");
	write(actual_fd, "Hello", 5);
	close(actual_fd);
	FILE *fd = fopen("./test_file", "r");
	cr_assert_file_contents_eq_str(fd, "Hello");
	fclose(fd);
	unlink("./test_file");
}

Test(redirect, redir2, .init=redirect_all_std)
{
	int actual_fd;

	actual_fd = redir("./tests/unopenable");
	cr_assert(actual_fd < 0);
	cr_assert_stderr_eq_str("our shell: ./tests/unopenable: Permission denied\n");
}

Test(redirect, rredir)
{
	int actual_fd;

	actual_fd = rredir("test_file2");
	write(actual_fd, "Hello", 5);
	close(actual_fd);
	actual_fd = rredir("test_file2");
	write(actual_fd, " world", 6);
	close(actual_fd);
	FILE *fd = fopen("./test_file2", "r");
	cr_assert_file_contents_eq_str(fd, "Hello world");
	fclose(fd);
	unlink("./test_file2");
}

Test(redirect, rredir2, .init=redirect_all_std)
{
	int actual_fd;

	actual_fd = rredir("./tests/unopenable");
	cr_assert(actual_fd < 0);
	cr_assert_stderr_eq_str("our shell: ./tests/unopenable: Permission denied\n");
}

Test(redirect, left_redir)
{
	int actual_fd;
	char buf[20];
	bzero(buf, 20);
	
	actual_fd = left_redir("./tests/read_test");
	read(actual_fd, buf, 15);
	cr_assert_str_eq(buf, "Hello world\n");
}

Test(redirect, left_redir2, .init=redirect_all_std)
{
	int actual_fd;
	actual_fd = left_redir("nowhere");
	cr_assert_eq(actual_fd, -1);
	cr_assert_stderr_eq_str("our shell: nowhere: No such file or directory\n");
}
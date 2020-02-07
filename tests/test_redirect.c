#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../includes/minishell.h"
#include <fcntl.h>

Test(redirect, t_r1)
{	
	r_to_file("./test_output", "hello world");
	FILE *fd = fopen("./test_output", "r");
	cr_assert_file_contents_eq_str(fd, "hello world");
	fclose(fd);
	unlink("./test_output");
}

Test(redirect, t_r2)
{	
	r_to_file("./test_output2", "hello world");
	FILE *fd = fopen("./test_output2", "r");
	cr_assert_file_contents_eq_str(fd, "hello world");
	fclose(fd);
	unlink("./test_output2");
}

Test(redirect, t_rr1)
{	
	rr_to_file("./test_output3", "hello ");
	rr_to_file("./test_output3", "world");
	FILE *fd = fopen("./test_output3", "r");
	cr_assert_file_contents_eq_str(fd, "hello world");
	fclose(fd);
	unlink("./test_output3");
}
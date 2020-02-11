#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "../includes/minishell.h"

void redirect_all_std(void);

Test(execute, execute, .init=redirect_all_std)
{
	extern char **environ;
	char **our_env;
	init_env(&our_env, environ);

	char *tokens[3] = {"echo", "hello", NULL};
	execute(tokens, -1, 1, &our_env);
	cr_assert_stdout_eq_str("hello\n> ");
}

Test(execute, execute2, .init=redirect_all_std)
{
	extern char **environ;
	char **our_env;
	init_env(&our_env, environ);

	char *tokens[5] = {"echo", "hello", ">", "test_output", NULL};
	execute(tokens, -1, 1, &our_env);
	FILE *fd = fopen("./test_output", "r");
	cr_assert_file_contents_eq_str(fd, "hello\n");
	fclose(fd);
	unlink("./test_output");
}

Test(execute, execute3, .init=redirect_all_std)
{
	extern char **environ;
	char **our_env;
	init_env(&our_env, environ);

	char *tokens[5] = {"echo", "hello", "|", "cat", NULL};
	execute(tokens, -1, 1, &our_env);
	cr_assert_stdout_eq_str("hello\n> ");
}

Test(execute, execute4, .init=redirect_all_std)
{
	extern char **environ;
	char **our_env;
	init_env(&our_env, environ);

	char *tokens[10] = {"echo", "hello", ">", "test_output1", ";", 
	"echo", "world", ">>", "test_output1", NULL};
	execute(tokens, -1, 1, &our_env);
	FILE *fd = fopen("./test_output1", "r");
	cr_assert_file_contents_eq_str(fd, "hello\nworld");
	fclose(fd);
	unlink("./test_output1");
}


// Test(exec, e_t1, .init=redirect_all_std)
// {
// 	char *tokens[3] = {"/bin/echo", "test", 0};

// 	ft_exec(tokens, -1, 1, NULL);
// 	cr_assert_stdout_eq_str("test\n");
// }

// Test(exec, e_t2, .init=redirect_all_std)
// {
// 	char *tokens[3] = {"nowhere", "test", 0};

// 	ft_exec(tokens, -1, 2, NULL);
// 	cr_assert_stderr_eq_str("No such file or directory\n");
// }
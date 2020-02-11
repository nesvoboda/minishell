#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../includes/minishell.h"

void redirect_all_std(void);

Test(env_utils, check_key)
{
	cr_assert_eq(check_key("abc=def"), 1);
	cr_assert_eq(check_key("notkey"), 0);
}

Test(env_utils, find_equals)
{
	cr_assert_eq(find_equals("lol="), 3);
	cr_assert_eq(find_equals("notkey"), 6);
}

Test(env_utils, add_all_env)
{
	char **env;
	env = malloc(sizeof(char *) * 3);
	env[0] = strdup("Yo=Yo");
	env[1] = strdup("d=0");
	env[2] = NULL;

	char *tokens[6] = {"export", "a=b", "b=c", "lol", "d=42", NULL};
	add_all_env(&env, tokens);
	cr_assert_str_eq(env[0], "Yo=Yo");
	cr_assert_str_eq(env[1], "a=b");
	cr_assert_str_eq(env[2], "b=c");
	cr_assert_str_eq(env[3], "d=42");
	cr_assert_eq(env[4], NULL);
}

Test(env_utils, remove_all_env, .init=redirect_all_std)
{
	char **env;
	int ret;
	env = malloc(sizeof(char *) * 4);
	env[0] = strdup("Yo=Yo");
	env[0] = strdup("a=b");
	env[0] = strdup("c=d");
	env[1] = NULL;

	char *tokens[6] = {"unset", "a", "Yo", "lol", "c=d", NULL};
	ret = remove_all_env(&env, tokens);
	cr_assert_str_eq(env[0], "c=d");
	cr_assert_eq(env[1], NULL);
	cr_assert_stderr_eq_str("our sh: unset: `c=d': not a valid identifier\n");
	cr_assert_eq(ret, 1);
}

Test(env_utils, remove_all_env2)
{
	char **env;
	char *tokens[3] = {"unset", "Yo", NULL};
	int ret;
	env = malloc(sizeof(char *) * 3);
	env[0] = strdup("Yo=Yo");
	env[0] = strdup("lol=Yo");
	env[1] = NULL;

	ret = remove_all_env(&env, tokens);
	cr_assert_str_eq(env[0], "lol=Yo");
	cr_assert_eq(env[1], NULL);
	cr_assert_eq(ret, 0);
}

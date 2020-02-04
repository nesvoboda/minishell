/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_environ.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 17:52:44 by ashishae          #+#    #+#             */
/*   Updated: 2020/02/04 19:17:55 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include "minishell.h"
#include <criterion/redirect.h>

void redirect_all_std(void);

Test(environ, envsize_t1)
{
	char *test_env[3] = {"one", "two", NULL};
	cr_assert(envsize(test_env) == 2);
}

Test(environ, add_env_t1)
{
	char **actual_env = NULL;
	add_env(&actual_env, "one");
	add_env(&actual_env, "two");
	cr_assert_str_eq(actual_env[0], "one");
	cr_assert_str_eq(actual_env[1], "two");
	cr_assert_eq(actual_env[2], NULL);
}

Test(environ, init_env_t1)
{
	extern char **environ;
	int i;

	char **actual_env = NULL;
	init_env(&actual_env, environ);
	for (i = 0; environ[i]; i++)
	{
		cr_assert_str_eq(actual_env[i], environ[i]);
	}
	cr_assert_eq(actual_env[i], NULL);
}

Test(environ, find_env_t1)
{
	char *test_env[3] = {"one=1", "two=2", NULL};
	cr_assert_eq(find_env(test_env, "one"), 1);
	cr_assert_eq(find_env(test_env, "two"), 1);
	cr_assert_eq(find_env(test_env, "three"), 0);
}

Test(environ, remove_env_t1)
{
	char **test_env = NULL;
	add_env(&test_env, "one");
	add_env(&test_env, "two");
	add_env(&test_env, "three");
	cr_assert_eq(find_env(test_env, "three"), 1);
	cr_assert_eq(test_env[3], NULL);
	remove_env(&test_env, "three");
	cr_assert_eq(find_env(test_env, "three"), 0);
}

Test(environ, remove_env_t2)
{
	char **test_env = NULL;
	add_env(&test_env, "one");
	add_env(&test_env, "two");
	add_env(&test_env, "three");
	remove_env(&test_env, "four");
	cr_assert_str_eq(test_env[0], "one");
	cr_assert_str_eq(test_env[1], "two");
	cr_assert_str_eq(test_env[2], "three");
	cr_assert_eq(test_env[3], NULL);
}

Test(environ, print_env_t1, .init = redirect_all_std)
{
	char **test_env = NULL;
	add_env(&test_env, "one");
	add_env(&test_env, "two");
	print_env(test_env);
	cr_assert_stdout_eq_str("one\ntwo\n");
}
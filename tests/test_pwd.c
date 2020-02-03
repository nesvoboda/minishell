#include <criterion/criterion.h>
#include "../minishell.h"

Test(pwd, pwd_t1) {
	cr_log_info("Actual path:   %s\n", pwd());
	cr_log_info("Expected path: %s\n", getcwd(NULL, 0));
    cr_assert_str_eq(pwd(), getcwd(NULL, 0));
}
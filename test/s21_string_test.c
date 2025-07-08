#include "../s21_string.h"

#include <check.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_sprintf.c"
#include "../s21_sscanf.c"
#include "s21_sprintf_test.c"
#include "s21_sscanf_test.c"
#include "s21_stdfuncs_test.c"

int main() {
  int number_failed;
  SRunner *sr = srunner_create(s21_string_suite());

  srunner_add_suite(sr, s21_sprintf_suite());
  srunner_add_suite(sr, s21_sscanf_suite());

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

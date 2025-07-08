#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 0;
  int should_continue = 1;

  while (n > 0 && should_continue) {
    --n;
    unsigned char c1 = (unsigned char)*str1;
    unsigned char c2 = (unsigned char)*str2;

    if (c1 != c2) {
      result = c1 - c2;
      should_continue = 0;
    } else if (c1 == '\0') {
      should_continue = 0;
    } else {
      str1++;
      str2++;
    }
  }

  return result;
}

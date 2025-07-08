#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = S21_NULL;
  int found = 0;

  while (*str1 && !found) {
    const char *ptr = str2;
    while (*ptr && !found) {
      if (*str1 == *ptr) {
        result = (char *)str1;
        found = 1;
      }
      ptr++;
    }
    if (!found) {
      str1++;
    }
  }

  return result;
}

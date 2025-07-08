#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t result = 0;

  if (str1 != S21_NULL && str2 != S21_NULL) {
    const char *ptr1 = str1;
    s21_size_t count = 0;
    int found = 0;

    while (*ptr1 && !found) {
      const char *ptr2 = str2;
      int match = 0;

      while (*ptr2 && !match) {
        if (*ptr1 == *ptr2) {
          match = 1;
        }
        ptr2++;
      }

      if (match) {
        found = 1;
      } else {
        ptr1++;
        count++;
      }
    }

    result = count;
  }

  return result;
}

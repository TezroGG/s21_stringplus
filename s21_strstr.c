#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = S21_NULL;

  // Обработка особого случая пустой искомой строки
  if (*needle == '\0') {
    result = (char *)haystack;
  } else {
    int found = 0;

    while (*haystack != '\0' && !found) {
      const char *h = haystack;
      const char *n = needle;
      int match = 1;

      // Проверяем совпадение текущей позиции с needle
      while (*n != '\0' && match) {
        if (*h == '\0' || *h != *n) {
          match = 0;
        } else {
          h++;
          n++;
        }
      }

      if (match) {
        result = (char *)haystack;
        found = 1;
      } else {
        haystack++;
      }
    }
  }

  return result;
}

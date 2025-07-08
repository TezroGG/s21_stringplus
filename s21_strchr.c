#include "s21_string.h"

char *s21_strchr(const char *s, int c) {
  char *result = S21_NULL;
  int found = 0;

  while (*s != '\0' && !found) {
    if (*s == (char)c) {
      result = (char *)s;
      found = 1;
    } else {
      s++;
    }
  }

  // Проверка случая, когда ищем символ '\0'
  if (*s == '\0' && (char)c == '\0') {
    result = (char *)s;
  }

  return result;
}

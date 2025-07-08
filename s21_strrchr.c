#include "s21_string.h"

char *s21_strrchr(const char *str, int ch) {
  const char *last = S21_NULL;
  char *result;

  // Проходим по всей строке, запоминая последнее вхождение символа
  while (*str != '\0') {
    if (*str == (char)ch) {
      last = str;
    }
    str++;
  }

  // После цикла str указывает на завершающий нулевой символ
  if ((char)ch == '\0') {
    result = (char *)str;
  } else {
    result = (char *)last;
  }

  return result;
}

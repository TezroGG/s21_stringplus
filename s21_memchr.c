#include "s21_string.h"

void *s21_memchr(const void *ptr, int value, s21_size_t num) {
  const unsigned char *p = (const unsigned char *)ptr;
  unsigned char val = (unsigned char)value;
  void *result = S21_NULL;
  s21_size_t i = 0;

  while (i < num && result == S21_NULL) {
    if (p[i] == val) {
      result = (void *)(p + i);
    }
    i++;
  }

  return result;
}

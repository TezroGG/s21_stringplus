#include "s21_string.h"

void *s21_memset(void *ptr, int value, s21_size_t num) {
  unsigned char *p = (unsigned char *)ptr;
  unsigned char val = (unsigned char)value;

  for (s21_size_t i = 0; i < num; i++) {
    p[i] = val;
  }

  return ptr;
}

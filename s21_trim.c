#include "s21_string.h"

static int is_trim_char(char c, const char *trim_chars) {
  int result = 0;

  if (trim_chars == S21_NULL || *trim_chars == '\0') {
    result = (c == ' ' || c == '\t' || c == '\n');
  } else {
    const char *ptr = trim_chars;
    while (*ptr && !result) {
      if (c == *ptr) {
        result = 1;
      }
      ptr++;
    }
  }

  return result;
}

void *s21_trim(const char *src, const char *trim_chars) {
  void *result = S21_NULL;

  if (src != S21_NULL) {
    s21_size_t len = s21_strlen(src);

    if (len == 0) {
      char *empty = (char *)malloc(1);
      if (empty != S21_NULL) {
        *empty = '\0';
        result = empty;
      }
    } else {
      // Находим начало строки после удаления начальных символов
      s21_size_t start = 0;
      while (start < len && is_trim_char(src[start], trim_chars)) {
        start++;
      }

      // Находим конец строки до удаляемых символов
      s21_size_t end = len - 1;
      while (end > start && is_trim_char(src[end], trim_chars)) {
        end--;
      }

      // Вычисляем длину результирующей строки
      s21_size_t new_len = (end >= start) ? end - start + 1 : 0;

      // Выделяем память и копируем результат
      char *temp_result = (char *)malloc(new_len + 1);
      if (temp_result != S21_NULL) {
        if (new_len > 0) {
          s21_memcpy(temp_result, src + start, new_len);
        }
        temp_result[new_len] = '\0';
        result = temp_result;
      }
    }
  }

  return result;
}

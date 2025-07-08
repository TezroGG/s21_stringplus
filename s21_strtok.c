#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *next_token = S21_NULL;
  char *token_start = S21_NULL;

  // Инициализация указателя при первом вызове или новой строке
  if (str != S21_NULL) {
    next_token = str;
  }

  // Проверка, имеем ли мы строку для обработки
  if (next_token != S21_NULL) {
    // Пропуск начальных разделителей
    while (*next_token && s21_strchr(delim, *next_token) != S21_NULL) {
      next_token++;
    }

    // Если не достигнут конец строки, у нас есть токен
    if (*next_token != '\0') {
      token_start = next_token;

      // Поиск конца токена (следующего разделителя или конца строки)
      while (*next_token && s21_strchr(delim, *next_token) == S21_NULL) {
        next_token++;
      }

      // Завершение текущего токена и настройка для следующего вызова
      if (*next_token) {
        *next_token = '\0';
        next_token++;
      } else {
        // Если достигнут конец строки, следующий вызов вернет NULL
        next_token = S21_NULL;
      }
    }
  }

  return token_start;
}

#include "s21_string.h"

void *s21_to_lower(const char *str) {
  void *result = S21_NULL;

  if (str != S21_NULL) {
    s21_size_t len = s21_strlen(str);
    char *temp_result = (char *)malloc((len + 1) * sizeof(char));

    if (temp_result != S21_NULL) {
      for (s21_size_t i = 0; i < len; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
          temp_result[i] = str[i] + 32;  // Преобразование в нижний регистр
        } else {
          temp_result[i] = str[i];
        }
      }
      temp_result[len] = '\0';
      result = (void *)temp_result;
    }
  }

  return result;
}

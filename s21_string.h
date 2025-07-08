#ifndef S21_STRING_H
#define S21_STRING_H

#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>

// Определение типа s21_size_t
typedef unsigned long s21_size_t;

// Определение NULL
#define S21_NULL ((void *)0)

// Прототипы функций
void *s21_memchr(const void *ptr, int value, s21_size_t num);
int s21_memcmp(const void *ptr1, const void *ptr2, s21_size_t num);
void *s21_memcpy(void *destination, const void *source, s21_size_t num);
void *s21_memset(void *ptr, int value, s21_size_t num);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int ch);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int ch);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);
int s21_sprintf(char *str, const char *format, ...);
int s21_sscanf(const char *str, const char *format, ...);

#endif // S21_STRING_H

void *safe_memchr(const void *str, int c, size_t n) {
  if (str == NULL && n == 0) {
    return NULL;
  }
  return memchr(str, c, n);
}

int safe_memcmp(const void *str1, const void *str2, size_t n) {
  printf("\n--- safe_memcmp debug ---\n");
  printf("str1 pointer: %p, str2 pointer: %p, n: %zu\n", str1, str2, n);

  if (n == 0) {
    printf("n is 0, returning 0\n");
    return 0;
  }

  if (str1 == NULL || str2 == NULL) {
    printf("Warning: NULL pointer detected! str1: %p, str2: %p\n", str1, str2);
    return 0;
  }

  printf("First bytes of str1: ");
  for (size_t i = 0; i < n && i < 10; i++) {
    unsigned char c = ((const unsigned char *)str1)[i];
    printf("%02X (%c) ", c, (c >= 32 && c <= 126) ? c : '.');
  }
  printf("\n");

  printf("First bytes of str2: ");
  for (size_t i = 0; i < n && i < 10; i++) {
    unsigned char c = ((const unsigned char *)str2)[i];
    printf("%02X (%c) ", c, (c >= 32 && c <= 126) ? c : '.');
  }
  printf("\n");

  int result = memcmp(str1, str2, n);
  printf("memcmp result: %d\n", result);
  printf("--- end debug ---\n");

  return result;
}

void *safe_memset(void *str, int c, size_t n) {
  if (str == NULL && n == 0) {
    return NULL;
  }
  return memset(str, c, n);
}

int safe_strncmp(const char *str1, const char *str2, size_t n) {
  if (n == 0) {
    return 0;
  }
  while (*str1 && (*str1 == *str2) && --n > 0) {
    str1++;
    str2++;
  }
  return (unsigned char)*str1 - (unsigned char)*str2;
}

char *safe_strtok(char *str, const char *delim) {
  if (delim == NULL) {
    return NULL;
  }
  return strtok(str, delim);
}

char *safe_strpbrk(const char *str1, const char *str2) {
  if (str1 == NULL || str2 == NULL) {
    return NULL;
  }
  return strpbrk(str1, str2);
}

char *safe_strrchr(const char *str, int c) {
  if (str == NULL) {
    return NULL;
  }
  return strrchr(str, c);
}

size_t safe_strcspn(const char *str1, const char *str2) {
  if (str1 == NULL || str2 == NULL) {
    return 0;
  }
  return strcspn(str1, str2);
}

char *safe_strstr(const char *haystack, const char *needle) {
  if (haystack == NULL || needle == NULL) {
    return NULL;
  }
  if (*needle == '\0') {
    return (char *)haystack;
  }
  return strstr(haystack, needle);
}

char *safe_strncpy(char *dest, const char *src, size_t n) {
  if (n == 0) {
    return dest;
  }
  return strncpy(dest, src, n);
}

START_TEST(test_memchr) {
  char str[] = "Hello, world!";
  ck_assert_ptr_eq(s21_memchr(str, 'o', 13), safe_memchr(str, 'o', 13));
  ck_assert_ptr_eq(s21_memchr(str, 'z', 13), safe_memchr(str, 'z', 13));
  ck_assert_ptr_eq(s21_memchr(str, 'H', 1), safe_memchr(str, 'H', 1));
  ck_assert_ptr_eq(s21_memchr(S21_NULL, 'o', 0), safe_memchr(NULL, 'o', 0));
  ck_assert_ptr_eq(s21_memchr("", 'o', 1), safe_memchr("", 'o', 1));
  ck_assert_ptr_eq(s21_memchr("\0 ", ' ', 2), safe_memchr("\0 ", ' ', 2));
  ck_assert_ptr_eq(s21_memchr("\0 ", '\0', 2), safe_memchr("\0 ", '\0', 2));
  ck_assert_ptr_eq(s21_memchr("abcdef", 'f', 6), safe_memchr("abcdef", 'f', 6));
  ck_assert_ptr_eq(s21_memchr("abc\0def", 'c', 6),
                   safe_memchr("abc\0def", 'c', 6));
  ck_assert_ptr_eq(s21_memchr("abc\0def", '\0', 7),
                   memchr("abc\0def", '\0', 7));
}
END_TEST

START_TEST(test_memcmp) {
  char str1[] = "abcdef";
  char str2[] = "abcdeg";

  int result1_s21 = s21_memcmp(str1, str2, 5);
  int result1_safe = safe_memcmp(str1, str2, 5);
  ck_assert_int_eq(result1_s21, result1_safe);

  int result2_s21 = s21_memcmp(str1, str2, 6);
  int result2_safe = safe_memcmp(str1, str2, 6);
  ck_assert_int_eq(result2_s21 < 0, result2_safe < 0);

  int result3_s21 = s21_memcmp(str1, str1, 6);
  int result3_safe = safe_memcmp(str1, str1, 6);
  ck_assert_int_eq(result3_s21, result3_safe);

  int result4_s21 = s21_memcmp(S21_NULL, S21_NULL, 0);
  int result4_safe = safe_memcmp(NULL, NULL, 0);
  ck_assert_int_eq(result4_s21, result4_safe);

  int result5_s21 = s21_memcmp("", "", 0);
  int result5_safe = safe_memcmp("", "", 0);
  ck_assert_int_eq(result5_s21, result5_safe);

  int result6_s21 = s21_memcmp("", "", 1);
  int result6_safe = safe_memcmp("", "", 1);
  ck_assert_int_eq(result6_s21, result6_safe);

  int result7_s21 = s21_memcmp("abc\0def", "abc\0xyz", 7);
  int result7_safe = safe_memcmp("abc\0def", "abc\0xyz", 7);
  ck_assert_int_eq(result7_s21 < 0, result7_safe < 0);

  int result8_s21 = s21_memcmp("  ", "  ", 2);
  int result8_safe = safe_memcmp("  ", "  ", 2);
  ck_assert_int_eq(result8_s21, result8_safe);

  int result9_s21 = s21_memcmp("\n ", "  ", 2);
  int result9_safe = safe_memcmp("\n ", "  ", 2);
  ck_assert_int_eq((result9_s21 < 0), (result9_safe < 0));
}
END_TEST

START_TEST(test_null_cases) {
  ck_assert_ptr_eq(s21_memchr(S21_NULL, 'a', 0), safe_memchr(NULL, 'a', 0));

  ck_assert_ptr_eq(s21_strtok(S21_NULL, " /"), NULL);

  ck_assert_ptr_eq(s21_strstr("abc", ""), strstr("abc", ""));
  ck_assert_str_eq(s21_strerror(9999), strerror(9999));
}
END_TEST

START_TEST(test_memcpy) {
  char src[] = "Test memcpy";
  char dest1[20], dest2[20];

  s21_memcpy(dest1, src, 12);
  memcpy(dest2, src, 12);
  ck_assert_mem_eq(dest1, dest2, 12);

  char zero_src[1] = {'\0'};
  char zero_dest1[1], zero_dest2[1];

  s21_memcpy(zero_dest1, zero_src, 1);
  memcpy(zero_dest2, zero_src, 1);

  ck_assert_mem_eq(zero_dest1, zero_dest2, 1);

  char src2[] = "\n ";
  char dest3[3], dest4[3];
  s21_memcpy(dest3, src2, 2);
  memcpy(dest4, src2, 2);
  ck_assert_mem_eq(dest3, dest4, 2);

  char src3[] = "\0 ";
  char dest5[3], dest6[3];
  s21_memcpy(dest5, src3, 2);
  memcpy(dest6, src3, 2);
  ck_assert_mem_eq(dest5, dest6, 2);
}
END_TEST

START_TEST(test_memset) {
  char str1[10], str2[10];

  s21_memset(str1, 'A', 10);
  memset(str2, 'A', 10);
  ck_assert_mem_eq(str1, str2, 10);

  ck_assert_ptr_eq(s21_memset(S21_NULL, 'A', 0), safe_memset(NULL, 'A', 0));

  s21_memset(str1, '\0', 10);
  memset(str2, '\0', 10);
  ck_assert_mem_eq(str1, str2, 10);

  s21_memset(str1, 'A', 5);
  memset(str2, 'A', 5);
  ck_assert_mem_eq(str1, str2, 10);

  s21_memset(str1, '#', 10);
  memset(str2, '#', 10);
  ck_assert_mem_eq(str1, str2, 10);

  s21_memset(str1, 'X', 7);
  memset(str2, 'X', 7);
  ck_assert_mem_eq(str1, str2, 10);
}
END_TEST

START_TEST(test_strncat) {
  char dest1[20] = "Hello ", dest2[20] = "Hello ";
  char src[] = "World!";

  s21_strncat(dest1, src, 6);
  strncat(dest2, src, 6);
  ck_assert_str_eq(dest1, dest2);

  char dest3[20] = "Test";
  char dest4[20] = "Test";
  s21_strncat(dest3, "", 5);
  strncat(dest4, "", 5);
  ck_assert_str_eq(dest3, dest4);

  char dest5[20] = "123";
  char dest6[20] = "123";
  s21_strncat(dest5, "456789", 3);
  strncat(dest6, "456789", 3);
  ck_assert_str_eq(dest5, dest6);

  char dest7[20] = "ABC";
  char dest8[20] = "ABC";
  s21_strncat(dest7, "DE", 10);
  strncat(dest8, "DE", 10);
  ck_assert_str_eq(dest7, dest8);

  char dest9[10] = "Hi";
  char dest10[10] = "Hi";
  s21_strncat(dest9, "There!", 7);
  strncat(dest10, "There!", 7);
  ck_assert_str_eq(dest9, dest10);
}
END_TEST

START_TEST(test_strchr) {
  const char str[] = "abcdef";

  ck_assert_ptr_eq(s21_strchr(str, 'c'), strchr(str, 'c'));
  ck_assert_ptr_eq(s21_strchr(str, 'z'), strchr(str, 'z'));
  ck_assert_ptr_eq(s21_strchr("", 'c'), strchr("", 'c'));
  ck_assert_ptr_eq(s21_strchr(str, 'a'), strchr(str, 'a'));
  ck_assert_ptr_eq(s21_strchr(str, 'f'), strchr(str, 'f'));
  ck_assert_ptr_eq(s21_strchr(str, '\0'), strchr(str, '\0'));

  char str2[] = "banana";
  ck_assert_ptr_eq(s21_strchr(str2, 'a'), strchr(str2, 'a'));

  char str3[] = "x";
  ck_assert_ptr_eq(s21_strchr(str3, 'x'), strchr(str3, 'x'));
  ck_assert_ptr_eq(s21_strchr(str3, 'y'), strchr(str3, 'y'));

  char str4[] = "hello world!";
  ck_assert_ptr_eq(s21_strchr(str4, ' '), strchr(str4, ' '));
  ck_assert_ptr_eq(s21_strchr(str4, '!'), strchr(str4, '!'));
}
END_TEST

START_TEST(test_strncmp) {
  char str1[] = "abcdef";
  char str2[] = "abcdeg";

  ck_assert_int_eq(s21_strncmp(str1, str2, 5), safe_strncmp(str1, str2, 5));
  ck_assert_int_eq(s21_strncmp(str1, str2, 6), safe_strncmp(str1, str2, 6));
  ck_assert_int_eq(s21_strncmp(S21_NULL, S21_NULL, 0),
                   safe_strncmp(NULL, NULL, 0));
  ck_assert_int_eq(s21_strncmp("", "", 1), safe_strncmp("", "", 1));
  ck_assert_int_eq(s21_strncmp("hello", "hello", 5),
                   safe_strncmp("hello", "hello", 5));
  ck_assert_int_eq(s21_strncmp("abcxyz", "abcdef", 3),
                   safe_strncmp("abcxyz", "abcdef", 3));
  ck_assert_int_eq(s21_strncmp("abc", "abcdef", 6),
                   safe_strncmp("abc", "abcdef", 6));
  ck_assert_int_eq(s21_strncmp("", "abc", 3), safe_strncmp("", "abc", 3));
  ck_assert_int_eq(s21_strncmp("abc", "", 3), safe_strncmp("abc", "", 3));
  ck_assert_int_eq(s21_strncmp("abc", "xyz", 0), safe_strncmp("abc", "xyz", 0));
  ck_assert_int_eq(s21_strncmp("12345xyz", "12345abc", 5),
                   safe_strncmp("12345xyz", "12345abc", 5));
  ck_assert_int_eq(s21_strncmp("helloXworld", "helloYworld", 6),
                   safe_strncmp("helloXworld", "helloYworld", 6));
}
END_TEST

START_TEST(test_strncpy) {
  {
    char src[] = "Hello";
    char dest1[10] = {0};
    char dest2[10] = {0};
    s21_strncpy(dest1, src, 10);
    strncpy(dest2, src, 10);
    ck_assert_mem_eq(dest1, dest2, 10);
  }

  {
    char src[] = "123456789";
    char dest1[10] = {0};
    char dest2[10] = {0};
    s21_strncpy(dest1, src, 9);
    strncpy(dest2, src, 9);
    ck_assert_mem_eq(dest1, dest2, 9);
  }

  {
    char src[] = "LongString";
    char dest1[6] = {0};
    char dest2[6] = {0};
    s21_strncpy(dest1, src, 5);
    strncpy(dest2, src, 5);
    ck_assert_mem_eq(dest1, dest2, 5);
  }

  {
    char src[] = "";
    char dest1[5] = {0};
    char dest2[5] = {0};

    dest1[0] = 'a';
    dest1[1] = 'b';
    dest1[2] = 'c';
    dest1[3] = 'd';
    dest2[0] = 'a';
    dest2[1] = 'b';
    dest2[2] = 'c';
    dest2[3] = 'd';

    s21_strncpy(dest1, src, 4);
    strncpy(dest2, src, 4);

    ck_assert_mem_eq(dest1, dest2, 4);
  }

  {
    char src[] = "Hello";
    char dest1[10] = {0};
    char dest2[10] = {0};
    memcpy(dest1, "abcdef", 6);
    memcpy(dest2, "abcdef", 6);
    s21_strncpy(dest1, src, 0);
    safe_strncpy(dest2, src, 0);
    ck_assert_mem_eq(dest1, dest2, 10);
  }

  {
    char src[] = "Hi";
    char dest1[10] = {0};
    char dest2[10] = {0};
    memcpy(dest1, "abcdefgh", 8);
    memcpy(dest2, "abcdefgh", 8);
    s21_strncpy(dest1, src, 10);
    strncpy(dest2, src, 10);
    ck_assert_mem_eq(dest1, dest2, 10);
  }
  {
    char src[] = "Test";
    char dest1[10] = {0};
    char dest2[10] = {0};
    s21_strncpy(dest1, src, 8);
    strncpy(dest2, src, 8);
    ck_assert_mem_eq(dest1, dest2, 8);
  }
}
END_TEST

START_TEST(test_strcspn) {
  char str1[] = "abcdef";
  char str2[] = "def";

  ck_assert_int_eq(s21_strcspn(str1, str2), safe_strcspn(str1, str2));
  ck_assert_int_eq(s21_strcspn("", ""), safe_strcspn("", ""));
  ck_assert_int_eq(s21_strcspn("abcdef", "xyz"), safe_strcspn("abcdef", "xyz"));
  ck_assert_int_eq(s21_strcspn("abcdef", "abcdef"),
                   safe_strcspn("abcdef", "abcdef"));
  ck_assert_int_eq(s21_strcspn("", "abc"), safe_strcspn("", "abc"));
  ck_assert_int_eq(s21_strcspn("abcdef", ""), safe_strcspn("abcdef", ""));
  ck_assert_int_eq(s21_strcspn("abcdef", "a"), safe_strcspn("abcdef", "a"));
  ck_assert_int_eq(s21_strcspn("hello world!", " "),
                   safe_strcspn("hello world!", " "));
  ck_assert_int_eq(s21_strcspn("!@#$^&*", "#$"), safe_strcspn("!@#$^&*", "#$"));
}
END_TEST

START_TEST(test_strlen) {
  char str[] = "Test length";

  ck_assert_int_eq(s21_strlen(str), strlen(str));
  ck_assert_int_eq(s21_strlen(""), strlen(""));
  ck_assert_int_eq(s21_strlen("A"), strlen("A"));
  ck_assert_int_eq(s21_strlen("     "), strlen("     "));

  char long_str[1001];
  memset(long_str, 'a', 1000);
  long_str[1000] = '\0';
  ck_assert_int_eq(s21_strlen(long_str), strlen(long_str));

  char str_with_null[] = "Hello\0World";
  ck_assert_int_eq(s21_strlen(str_with_null), strlen(str_with_null));
}
END_TEST

START_TEST(test_strpbrk) {
  char str_for_strpbrk[] = "Megalomania";
  char str_oneof[] = "yal";
  ck_assert_str_eq(s21_strpbrk(str_for_strpbrk, str_oneof), "alomania");
  ck_assert_str_eq(s21_strpbrk(str_for_strpbrk, str_oneof),
                   strpbrk(str_for_strpbrk, str_oneof));

  char *str = "Hello, world";
  char *empty = "";
  ck_assert(s21_strpbrk(str, empty) == S21_NULL);
  ck_assert_uint_eq((unsigned long)s21_strpbrk(str, empty),
                    (unsigned long)strpbrk(str, empty));
}
END_TEST

START_TEST(test_strrchr) {
  char test1[] = "0163456769";
  char test2[] = ";;;;;;H%%//#HH";
  char test3[] = "     /";
  ck_assert_uint_eq((unsigned long)s21_strrchr(test1, '6'),
                    (unsigned long)strrchr(test1, '6'));
  ck_assert_uint_eq((unsigned long)s21_strrchr(test1, ' '),
                    (unsigned long)strrchr(test1, ' '));
  ck_assert_uint_eq((unsigned long)s21_strrchr(test1, '6'),
                    (unsigned long)strrchr(test1, '6'));
  ck_assert_uint_eq((unsigned long)s21_strrchr(test2, 'H'),
                    (unsigned long)strrchr(test2, 'H'));
  ck_assert_uint_eq((unsigned long)s21_strrchr(test2, '$'),
                    (unsigned long)strrchr(test2, '$'));
  ck_assert_uint_eq((unsigned long)s21_strrchr(test2, ';'),
                    (unsigned long)strrchr(test2, ';'));
  ck_assert_uint_eq((unsigned long)s21_strrchr(test3, ' '),
                    (unsigned long)strrchr(test3, ' '));
  ck_assert_str_eq(s21_strrchr(test2, '\0'), strrchr(test2, '\0'));
}
END_TEST

START_TEST(test_strstr) {
  char test_1[] = "<<<5>>>";
  char test_2[] = "5";
  char test_3[] = "QwertyQwertyQwerty";
  char test_4[] = "Qwerty";
  char test_5[] = "abcd";
  char test_6[] = "";
  char test_7[] = "aaaaa123aaa1234aaa";
  char test_8[] = "1234";

  ck_assert_ptr_eq(s21_strstr(test_1, test_2), strstr(test_1, test_2));
  ck_assert_ptr_eq(s21_strstr(test_3, test_4), strstr(test_3, test_4));
  ck_assert_ptr_eq(s21_strstr(test_5, test_6), strstr(test_5, test_6));
  ck_assert_ptr_eq(s21_strstr(test_4, test_5), strstr(test_4, test_5));
  ck_assert_ptr_eq(s21_strstr(test_7, test_8), strstr(test_7, test_8));
}
END_TEST

START_TEST(test_strtok) {
  char str_strtok1[] = "one/two/three(four)five";
  char delim1[] = "/()";

  char str_strtok2[] = "one/two/three(four)five";
  char delim2[] = "/()";
  char *my_strtok = s21_strtok(str_strtok1, delim1);
  char *origin_strtok = strtok(str_strtok2, delim2);
  while (my_strtok != S21_NULL) {
    ck_assert_str_eq(my_strtok, origin_strtok);
    my_strtok = s21_strtok(S21_NULL, delim1);
    origin_strtok = strtok(S21_NULL, delim2);
  }
}
END_TEST

START_TEST(test_strerror) {
  ck_assert_str_eq(s21_strerror(EINVAL), strerror(EINVAL));
  ck_assert_str_eq(s21_strerror(ENOMEM), strerror(ENOMEM));
  ck_assert_str_eq(s21_strerror(EACCES), strerror(EACCES));
  ck_assert_str_eq(s21_strerror(ENOTDIR), strerror(ENOTDIR));
  ck_assert_str_eq(s21_strerror(0), strerror(0));
}
END_TEST

START_TEST(test_insert) {
  // Тест обычной вставки
  char *src1 = "Hello World";
  char *str1 = " my";
  void *result1 = s21_insert(src1, str1, 5);
  ck_assert_str_eq((char *)result1, "Hello my World");
  free(result1);

  // Тест вставки в начало строки
  char *src2 = "World";
  char *str2 = "Hello ";
  void *result2 = s21_insert(src2, str2, 0);
  ck_assert_str_eq((char *)result2, "Hello World");
  free(result2);

  // Тест вставки в конец строки
  char *src3 = "Hello";
  char *str3 = " World";
  void *result3 = s21_insert(src3, str3, 5);
  ck_assert_str_eq((char *)result3, "Hello World");
  free(result3);

  // Тест вставки пустой строки
  char *src4 = "HelloWorld";
  char *str4 = "";
  void *result4 = s21_insert(src4, str4, 5);
  ck_assert_str_eq((char *)result4, "HelloWorld");
  free(result4);

  // Тест вставки в пустую строку
  char *src5 = "";
  char *str5 = "Hello";
  void *result5 = s21_insert(src5, str5, 0);
  ck_assert_str_eq((char *)result5, "Hello");
  free(result5);

  // Тест с неверным start_index
  char *src6 = "Hello";
  char *str6 = " World";
  void *result6 = s21_insert(src6, str6, 10);
  ck_assert_ptr_eq(result6, S21_NULL);

  // Тест с NULL аргументами
  ck_assert_ptr_eq(s21_insert(S21_NULL, "test", 0), S21_NULL);
  ck_assert_ptr_eq(s21_insert("test", S21_NULL, 0), S21_NULL);
}
END_TEST

START_TEST(test_to_lower) {
  // Тест с обычной строкой
  char *src1 = "HELLO WORLD";
  void *result1 = s21_to_lower(src1);
  ck_assert_str_eq((char *)result1, "hello world");
  free(result1);

  // Тест со смешанными символами
  char *src2 = "Hello World 123";
  void *result2 = s21_to_lower(src2);
  ck_assert_str_eq((char *)result2, "hello world 123");
  free(result2);

  // Тест с пустой строкой
  char *src3 = "";
  void *result3 = s21_to_lower(src3);
  ck_assert_str_eq((char *)result3, "");
  free(result3);

  // Тест со специальными символами
  char *src4 = "HELLO!@#$%^&*()_+";
  void *result4 = s21_to_lower(src4);
  ck_assert_str_eq((char *)result4, "hello!@#$%^&*()_+");
  free(result4);

  // Тест со строкой, уже в нижнем регистре
  char *src5 = "hello world";
  void *result5 = s21_to_lower(src5);
  ck_assert_str_eq((char *)result5, "hello world");
  free(result5);

  // Тест с NULL
  ck_assert_ptr_eq(s21_to_lower(S21_NULL), S21_NULL);
}
END_TEST

START_TEST(test_to_upper) {
  // Тест с обычной строкой
  char *src1 = "hello world";
  void *result1 = s21_to_upper(src1);
  ck_assert_str_eq((char *)result1, "HELLO WORLD");
  free(result1);

  // Тест со смешанными символами
  char *src2 = "Hello World 123";
  void *result2 = s21_to_upper(src2);
  ck_assert_str_eq((char *)result2, "HELLO WORLD 123");
  free(result2);

  // Тест с пустой строкой
  char *src3 = "";
  void *result3 = s21_to_upper(src3);
  ck_assert_str_eq((char *)result3, "");
  free(result3);

  // Тест со специальными символами
  char *src4 = "hello!@#$%^&*()_+";
  void *result4 = s21_to_upper(src4);
  ck_assert_str_eq((char *)result4, "HELLO!@#$%^&*()_+");
  free(result4);

  // Тест со строкой, уже в верхнем регистре
  char *src5 = "HELLO WORLD";
  void *result5 = s21_to_upper(src5);
  ck_assert_str_eq((char *)result5, "HELLO WORLD");
  free(result5);

  // Тест с NULL
  ck_assert_ptr_eq(s21_to_upper(S21_NULL), S21_NULL);
}
END_TEST

START_TEST(test_trim) {
  // Тест с удалением пробелов с обеих сторон
  char *src1 = "  Hello World  ";
  void *result1 = s21_trim(src1, " ");
  ck_assert_str_eq((char *)result1, "Hello World");
  free(result1);

  // Тест с удалением указанных символов
  char *src2 = "***Hello World***";
  void *result2 = s21_trim(src2, "*");
  ck_assert_str_eq((char *)result2, "Hello World");
  free(result2);

  // Тест с несколькими разными символами для удаления
  char *src3 = "12345Hello World12345";
  void *result3 = s21_trim(src3, "12345");
  ck_assert_str_eq((char *)result3, "Hello World");
  free(result3);

  // Тест с пустой строкой
  char *src4 = "";
  void *result4 = s21_trim(src4, " ");
  ck_assert_str_eq((char *)result4, "");
  free(result4);

  // Тест с NULL в trim_chars (должен удалять пробелы, табуляции и новые строки)
  char *src5 = " \t\nHello World\t\n ";
  void *result5 = s21_trim(src5, S21_NULL);
  ck_assert_str_eq((char *)result5, "Hello World");
  free(result5);

  // Тест с пустой строкой trim_chars
  char *src6 = "Hello World";
  void *result6 = s21_trim(src6, "");
  ck_assert_str_eq((char *)result6, "Hello World");
  free(result6);

  // Тест с строкой, где все символы нужно удалить
  char *src7 = "12345";
  void *result7 = s21_trim(src7, "12345");
  ck_assert_str_eq((char *)result7, "");
  free(result7);

  // Тест с NULL в src
  ck_assert_ptr_eq(s21_trim(S21_NULL, " "), S21_NULL);
}
END_TEST

Suite *s21_string_suite(void) {
  Suite *s = suite_create("s21_string");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_memchr);
  tcase_add_test(tc_core, test_memcmp);
  tcase_add_test(tc_core, test_null_cases);
  tcase_add_test(tc_core, test_memcpy);
  tcase_add_test(tc_core, test_memset);
  tcase_add_test(tc_core, test_strncat);
  tcase_add_test(tc_core, test_strchr);
  tcase_add_test(tc_core, test_strncmp);
  tcase_add_test(tc_core, test_strncpy);
  tcase_add_test(tc_core, test_strcspn);
  tcase_add_test(tc_core, test_strerror);
  tcase_add_test(tc_core, test_strlen);
  tcase_add_test(tc_core, test_strpbrk);
  tcase_add_test(tc_core, test_strrchr);
  tcase_add_test(tc_core, test_strstr);
  tcase_add_test(tc_core, test_strtok);
  tcase_add_test(tc_core, test_insert);
  tcase_add_test(tc_core, test_to_lower);
  tcase_add_test(tc_core, test_to_upper);
  tcase_add_test(tc_core, test_trim);
  suite_add_tcase(s, tc_core);
  return s;
}

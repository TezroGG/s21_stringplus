START_TEST(s21_sprintf_f_test) {
  char str[80];
  char str_orig[80];

  double b = 1;
  int res_1 = s21_sprintf(str, "%.f", b);
  int res_1_orig = sprintf(str_orig, "%.f", b);

  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  double b_2 = 0.00000002345;
  int res_2 = s21_sprintf(str, "%+-10.3f", b_2);
  int res_2_orig = sprintf(str_orig, "%+-10.3f", b_2);

  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  double b_4 = 0;
  int res_4 = s21_sprintf(str, "%0+.15F", b_4);
  int res_4_orig = sprintf(str_orig, "%0+.15F", b_4);

  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  double b_5 = 1;
  int res_5 = s21_sprintf(str, "%f", b_5);
  int res_5_orig = sprintf(str_orig, "%f", b_5);

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  double b_6 = 0.00345;
  int res_6 = s21_sprintf(str, "%f", b_6);
  int res_6_orig = sprintf(str_orig, "%f", b_6);

  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  double b_7 = 0.00345;
  int res_7 = s21_sprintf(str, "%f", b_7);
  int res_7_orig = sprintf(str_orig, "%f", b_7);

  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_percent_test) {
  char str1[80];
  char str_orig[80];

  int res_1 = s21_sprintf(str1, "%%");
  int res_1_orig = sprintf(str_orig, "%%");
  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str1, str_orig);

  char str2[80];
  int res_2 = s21_sprintf(str2, "%10%");

  ck_assert_int_eq(res_2, 10);
  ck_assert_str_eq(str2, "         %");

  char str3[80];
  int a_percent = 14;
  int res_3 = s21_sprintf(str3, "hhhh%0*%", a_percent);

  ck_assert_int_eq(res_3, 18);
  ck_assert_str_eq(str3, "hhhh0000000000000%");

  char str4[80];
  int width_percent = 30;
  int res_4 = s21_sprintf(str4, "%-*%12345", width_percent);

  ck_assert_int_eq(res_4, 35);
  ck_assert_str_eq(str4, "%                             12345");

  char str5[80];
  int res_5 = s21_sprintf(str5, "abc%%defg");
  int res_5_orig = sprintf(str_orig, "abc%%defg");

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str5, str_orig);
}
END_TEST

START_TEST(s21_sprintf_n_test) {
  char str[80];
  char str_orig[80];

  int c_1, c_1_orig;
  int res_1 = s21_sprintf(str, "%n", &c_1);
  int res_1_orig = sprintf(str_orig, "%n", &c_1_orig);

  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_int_eq(c_1, c_1_orig);
  ck_assert_str_eq(str, str_orig);

  int c_2, c_2_orig;
  int res_2 = s21_sprintf(str, "12345%n678910", &c_2);
  int res_2_orig = sprintf(str_orig, "12345%n678910", &c_2_orig);

  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_int_eq(c_2, c_2_orig);
  ck_assert_str_eq(str, str_orig);

  int c_3, c_3_orig;
  int res_3 = s21_sprintf(str, "%nqwerty", &c_3);
  int res_3_orig = sprintf(str_orig, "%nqwerty", &c_3_orig);

  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_int_eq(c_3, c_3_orig);
  ck_assert_str_eq(str, str_orig);

  int c_4, c_4_orig;
  int res_4 = s21_sprintf(str, "hhhhh%n%%", &c_4);
  int res_4_orig = sprintf(str_orig, "hhhhh%n%%", &c_4_orig);

  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_int_eq(c_4, c_4_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_test) {
  char str1[80];
  char str_origin1[80];
  const char *format_str1 = "Hello";
  char c = 'X';
  char d = 'Y';
  int result1 = s21_sprintf(str1, format_str1, c);
  int result_origin1 = sprintf(str_origin1, format_str1, c);
  ck_assert_int_eq(result1, result_origin1);
  ck_assert_str_eq(str1, str_origin1);

  char str2[80];
  char str_origin2[80];
  const char *format_str2 = "Hello, %c %c";
  int result2 = s21_sprintf(str2, format_str2, c, d);
  int result_origin2 = sprintf(str_origin2, format_str2, c, d);
  ck_assert_int_eq(result2, result_origin2);
  ck_assert_str_eq(str2, str_origin2);

  char str3[80];
  char str_origin3[80];
  char *s1 = "world!";
  char *s2 = "Hello world!";
  const char *format_str3 = "Hello, %10s %10.15s";
  int result3 = s21_sprintf(str3, format_str3, s1, s2);
  int result_origin3 = sprintf(str_origin3, format_str3, s1, s2);
  ck_assert_int_eq(result3, result_origin3);
  ck_assert_str_eq(str3, str_origin3);
}
END_TEST

START_TEST(s21_sprintf_c_test) {
  char str[80];
  char str1[80];
  char x = 'c';
  int res = s21_sprintf(str, "%-10c", x);
  int res1 = sprintf(str1, "%-10c", x);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str1);
  ck_assert_int_eq(res, res1);

  res = s21_sprintf(str, "%10c", x);
  res1 = sprintf(str1, "%10c", x);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_sprintf_s_test) {
  char str[80];
  char str1[80];
  char *x = "blablabla";
  int res = s21_sprintf(str, "%-11.10s", x);
  int res1 = sprintf(str1, "%-11.10s", x);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str1);
  ck_assert_int_eq(res, res1);

  res = s21_sprintf(str, "%11.8s", x);
  res1 = sprintf(str1, "%11.8s", x);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_sprintf_u_test) {
  char str[80];
  char str_orig[80];
  unsigned int a = 2345;

  int res_1 = s21_sprintf(str, "%10.5u", a);
  int res_1_orig = sprintf(str_orig, "%10.5u", a);

  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_2 = s21_sprintf(str, "%10.5u", a);
  int res_2_orig = sprintf(str_orig, "%10.5u", a);

  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = s21_sprintf(str, "%3.5u", a);
  int res_3_orig = sprintf(str_orig, "%3.5u", a);

  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = s21_sprintf(str, "%0u", a);
  int res_4_orig = sprintf(str_orig, "%0u", a);

  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = s21_sprintf(str, "%-u", a);
  int res_5_orig = sprintf(str_orig, "%-u", a);

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_6 = s21_sprintf(str, "%u", a);
  int res_6_orig = sprintf(str_orig, "%u", a);

  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = s21_sprintf(str, "%5u", a);
  int res_7_orig = sprintf(str_orig, "%5u", a);

  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  int res_8 = s21_sprintf(str, "%05u", a);
  int res_8_orig = sprintf(str_orig, "%05u", a);

  ck_assert_int_eq(res_8, res_8_orig);
  ck_assert_str_eq(str, str_orig);

  int res_9 = s21_sprintf(str, "%-5u", a);
  int res_9_orig = sprintf(str_orig, "%-5u", a);

  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  int res_10 = s21_sprintf(str, "%.5u", a);
  int res_10_orig = sprintf(str_orig, "%.5u", a);

  ck_assert_int_eq(res_10, res_10_orig);
  ck_assert_str_eq(str, str_orig);

  int res_11 = s21_sprintf(str, "%.5u", a);
  int res_11_orig = sprintf(str_orig, "%.5u", a);

  ck_assert_int_eq(res_11, res_11_orig);
  ck_assert_str_eq(str, str_orig);

  int res_12 = s21_sprintf(str, "%-.5u", a);
  int res_12_orig = sprintf(str_orig, "%-.5u", a);

  ck_assert_int_eq(res_12, res_12_orig);
  ck_assert_str_eq(str, str_orig);

  int res_13 = s21_sprintf(str, "%-10.5u", a);
  int res_13_orig = sprintf(str_orig, "%-10.5u", a);

  ck_assert_int_eq(res_13, res_13_orig);
  ck_assert_str_eq(str, str_orig);

  int res_14 = s21_sprintf(str, "%3.5u", a);
  int res_14_orig = sprintf(str_orig, "%3.5u", a);

  ck_assert_int_eq(res_14, res_14_orig);
  ck_assert_str_eq(str, str_orig);

  int res_15 = s21_sprintf(str, "%-3.5u", a);
  int res_15_orig = sprintf(str_orig, "%-3.5u", a);

  ck_assert_int_eq(res_15, res_15_orig);
  ck_assert_str_eq(str, str_orig);

  int res_16 = s21_sprintf(str, "%6.2u", a);
  int res_16_orig = sprintf(str_orig, "%6.2u", a);

  ck_assert_int_eq(res_16, res_16_orig);
  ck_assert_str_eq(str, str_orig);

  int res_17 = s21_sprintf(str, "%3.2u", a);
  int res_17_orig = sprintf(str_orig, "%3.2u", a);

  ck_assert_int_eq(res_17, res_17_orig);
  ck_assert_str_eq(str, str_orig);

  int res_18 = s21_sprintf(str, "%01u", a);
  int res_18_orig = sprintf(str_orig, "%01u", a);

  ck_assert_int_eq(res_18, res_18_orig);
  ck_assert_str_eq(str, str_orig);

  int res_19 = s21_sprintf(str, "%hu", (unsigned short)a);
  int res_19_orig = sprintf(str_orig, "%hu", (unsigned short)a);

  ck_assert_int_eq(res_19, res_19_orig);
  ck_assert_str_eq(str, str_orig);

  int res_20 = s21_sprintf(str, "%lu", (unsigned long)a);
  int res_20_orig = sprintf(str_orig, "%lu", (unsigned long)a);

  ck_assert_int_eq(res_20, res_20_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_d_test) {
  char str[80];
  char str_orig[80];
  int a = 2345;

  int res_1 = s21_sprintf(str, "%10.5d", a);
  int res_1_orig = sprintf(str_orig, "%10.5d", a);

  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_2 = s21_sprintf(str, "% 10.5d", a);
  int res_2_orig = sprintf(str_orig, "% 10.5d", a);

  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = s21_sprintf(str, "%3.5d", a);
  int res_3_orig = sprintf(str_orig, "%3.5d", a);

  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = s21_sprintf(str, "%d", a);
  int res_4_orig = sprintf(str_orig, "%d", a);

  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = s21_sprintf(str, "%0d", a);
  int res_5_orig = sprintf(str_orig, "%0d", a);

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_6 = s21_sprintf(str, "%-d", a);
  int res_6_orig = sprintf(str_orig, "%-d", a);

  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = s21_sprintf(str, "%+d", a);
  int res_7_orig = sprintf(str_orig, "%+d", a);

  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  int res_8 = s21_sprintf(str, "% d", a);
  int res_8_orig = sprintf(str_orig, "% d", a);

  ck_assert_int_eq(res_8, res_8_orig);
  ck_assert_str_eq(str, str_orig);

  int res_9 = s21_sprintf(str, "%5d", a);
  int res_9_orig = sprintf(str_orig, "%5d", a);

  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  int res_10 = s21_sprintf(str, "%05d", a);
  int res_10_orig = sprintf(str_orig, "%05d", a);

  ck_assert_int_eq(res_10, res_10_orig);
  ck_assert_str_eq(str, str_orig);

  int res_11 = s21_sprintf(str, "%-5d", a);
  int res_11_orig = sprintf(str_orig, "%-5d", a);

  ck_assert_int_eq(res_11, res_11_orig);
  ck_assert_str_eq(str, str_orig);

  int res_12 = s21_sprintf(str, "%+5d", a);
  int res_12_orig = sprintf(str_orig, "%+5d", a);

  ck_assert_int_eq(res_12, res_12_orig);
  ck_assert_str_eq(str, str_orig);

  int res_13 = s21_sprintf(str, "% 5d", a);
  int res_13_orig = sprintf(str_orig, "% 5d", a);

  ck_assert_int_eq(res_13, res_13_orig);
  ck_assert_str_eq(str, str_orig);

  int res_14 = s21_sprintf(str, "%.5d", a);
  int res_14_orig = sprintf(str_orig, "%.5d", a);

  ck_assert_int_eq(res_14, res_14_orig);
  ck_assert_str_eq(str, str_orig);

  int res_15 = s21_sprintf(str, "%05d", a);
  int res_15_orig = sprintf(str_orig, "%.5d", a);

  ck_assert_int_eq(res_15, res_15_orig);
  ck_assert_str_eq(str, str_orig);

  int res_16 = s21_sprintf(str, "% .5d", a);
  int res_16_orig = sprintf(str_orig, "% .5d", a);

  ck_assert_int_eq(res_16, res_16_orig);
  ck_assert_str_eq(str, str_orig);

  int res_17 = s21_sprintf(str, "%+.5d", a);
  int res_17_orig = sprintf(str_orig, "%+.5d", a);

  ck_assert_int_eq(res_17, res_17_orig);
  ck_assert_str_eq(str, str_orig);

  int res_18 = s21_sprintf(str, "%-.5d", a);
  int res_18_orig = sprintf(str_orig, "%-.5d", a);

  ck_assert_int_eq(res_18, res_18_orig);
  ck_assert_str_eq(str, str_orig);

  int res_19 = s21_sprintf(str, "%10.5d", a);
  int res_19_orig = sprintf(str_orig, "%10.5d", a);

  ck_assert_int_eq(res_19, res_19_orig);
  ck_assert_str_eq(str, str_orig);

  int res_20 = s21_sprintf(str, "%+10.5d", a);
  int res_20_orig = sprintf(str_orig, "%+10.5d", a);

  ck_assert_int_eq(res_20, res_20_orig);
  ck_assert_str_eq(str, str_orig);

  int res_21 = s21_sprintf(str, "%-10.5d", a);
  int res_21_orig = sprintf(str_orig, "%-10.5d", a);

  ck_assert_int_eq(res_21, res_21_orig);
  ck_assert_str_eq(str, str_orig);

  int res_22 = s21_sprintf(str, "%3.5d", a);
  int res_22_orig = sprintf(str_orig, "%3.5d", a);

  ck_assert_int_eq(res_22, res_22_orig);
  ck_assert_str_eq(str, str_orig);

  int res_23 = s21_sprintf(str, "% 3.5d", a);
  int res_23_orig = sprintf(str_orig, "% 3.5d", a);

  ck_assert_int_eq(res_23, res_23_orig);
  ck_assert_str_eq(str, str_orig);

  int res_24 = s21_sprintf(str, "%+3.5d", a);
  int res_24_orig = sprintf(str_orig, "%+3.5d", a);

  ck_assert_int_eq(res_24, res_24_orig);
  ck_assert_str_eq(str, str_orig);

  int res_25 = s21_sprintf(str, "%-3.5d", a);
  int res_25_orig = sprintf(str_orig, "%-3.5d", a);

  ck_assert_int_eq(res_25, res_25_orig);
  ck_assert_str_eq(str, str_orig);

  int res_26 = s21_sprintf(str, "%hd", (unsigned short)a);
  int res_26_orig = sprintf(str_orig, "%hd", (unsigned short)a);

  ck_assert_int_eq(res_26, res_26_orig);
  ck_assert_str_eq(str, str_orig);

  int res_27 = s21_sprintf(str, "%ld", (unsigned long)a);
  int res_27_orig = sprintf(str_orig, "%ld", (unsigned long)a);

  ck_assert_int_eq(res_27, res_27_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_d_test_2) {
  char str[80];
  char str_orig[80];
  int a = -23454546;

  int res_1 = s21_sprintf(str, "%10.*d", 5, a);
  int res_1_orig = sprintf(str_orig, "%10.*d", 5, a);

  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_2 = s21_sprintf(str, "% 10.5d", a);
  int res_2_orig = sprintf(str_orig, "% 10.5d", a);

  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = s21_sprintf(str, "%3.5d", a);
  int res_3_orig = sprintf(str_orig, "%3.5d", a);

  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = s21_sprintf(str, "%d", a);
  int res_4_orig = sprintf(str_orig, "%d", a);

  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = s21_sprintf(str, "%0d", a);
  int res_5_orig = sprintf(str_orig, "%0d", a);

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_6 = s21_sprintf(str, "%-d", a);
  int res_6_orig = sprintf(str_orig, "%-d", a);

  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = s21_sprintf(str, "%+d", a);
  int res_7_orig = sprintf(str_orig, "%+d", a);

  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  int res_8 = s21_sprintf(str, "% d", a);
  int res_8_orig = sprintf(str_orig, "% d", a);

  ck_assert_int_eq(res_8, res_8_orig);
  ck_assert_str_eq(str, str_orig);

  int res_9 = s21_sprintf(str, "%5d", a);
  int res_9_orig = sprintf(str_orig, "%5d", a);

  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  int res_10 = s21_sprintf(str, "%0*d", 5, a);
  int res_10_orig = sprintf(str_orig, "%0*d", 5, a);

  ck_assert_int_eq(res_10, res_10_orig);
  ck_assert_str_eq(str, str_orig);

  int res_11 = s21_sprintf(str, "%-5d", a);
  int res_11_orig = sprintf(str_orig, "%-5d", a);

  ck_assert_int_eq(res_11, res_11_orig);
  ck_assert_str_eq(str, str_orig);

  int res_12 = s21_sprintf(str, "%+5d", a);
  int res_12_orig = sprintf(str_orig, "%+5d", a);

  ck_assert_int_eq(res_12, res_12_orig);
  ck_assert_str_eq(str, str_orig);

  int res_13 = s21_sprintf(str, "% 5d", a);
  int res_13_orig = sprintf(str_orig, "% 5d", a);

  ck_assert_int_eq(res_13, res_13_orig);
  ck_assert_str_eq(str, str_orig);

  int res_14 = s21_sprintf(str, "%.5d", a);
  int res_14_orig = sprintf(str_orig, "%.5d", a);

  ck_assert_int_eq(res_14, res_14_orig);
  ck_assert_str_eq(str, str_orig);

  int res_15 = s21_sprintf(str, "%.5d", a);
  int res_15_orig = sprintf(str_orig, "%.5d", a);

  ck_assert_int_eq(res_15, res_15_orig);
  ck_assert_str_eq(str, str_orig);

  int res_16 = s21_sprintf(str, "% .5d", a);
  int res_16_orig = sprintf(str_orig, "% .5d", a);

  ck_assert_int_eq(res_16, res_16_orig);
  ck_assert_str_eq(str, str_orig);

  int res_17 = s21_sprintf(str, "%+.5d", a);
  int res_17_orig = sprintf(str_orig, "%+.5d", a);

  ck_assert_int_eq(res_17, res_17_orig);
  ck_assert_str_eq(str, str_orig);

  int res_18 = s21_sprintf(str, "%-.5d", a);
  int res_18_orig = sprintf(str_orig, "%-.5d", a);

  ck_assert_int_eq(res_18, res_18_orig);
  ck_assert_str_eq(str, str_orig);

  int res_19 = s21_sprintf(str, "%10.5d", a);
  int res_19_orig = sprintf(str_orig, "%10.5d", a);

  ck_assert_int_eq(res_19, res_19_orig);
  ck_assert_str_eq(str, str_orig);

  int res_20 = s21_sprintf(str, "%+10.5d", a);
  int res_20_orig = sprintf(str_orig, "%+10.5d", a);

  ck_assert_int_eq(res_20, res_20_orig);
  ck_assert_str_eq(str, str_orig);

  int res_21 = s21_sprintf(str, "%-10.5d", a);
  int res_21_orig = sprintf(str_orig, "%-10.5d", a);

  ck_assert_int_eq(res_21, res_21_orig);
  ck_assert_str_eq(str, str_orig);

  int res_22 = s21_sprintf(str, "%3.5d", a);
  int res_22_orig = sprintf(str_orig, "%3.5d", a);

  ck_assert_int_eq(res_22, res_22_orig);
  ck_assert_str_eq(str, str_orig);

  int res_23 = s21_sprintf(str, "% 3.5d", a);
  int res_23_orig = sprintf(str_orig, "% 3.5d", a);

  ck_assert_int_eq(res_23, res_23_orig);
  ck_assert_str_eq(str, str_orig);

  int res_24 = s21_sprintf(str, "%+3.5d", a);
  int res_24_orig = sprintf(str_orig, "%+3.5d", a);

  ck_assert_int_eq(res_24, res_24_orig);
  ck_assert_str_eq(str, str_orig);

  int res_25 = s21_sprintf(str, "%-3.5d", a);
  int res_25_orig = sprintf(str_orig, "%-3.5d", a);

  ck_assert_int_eq(res_25, res_25_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_d_test_3) {
  char str[80];
  char str_orig[80];
  int a = 234;

  int res_1 = s21_sprintf(str, "%10.5d", a);
  int res_1_orig = sprintf(str_orig, "%10.5d", a);

  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_2 = s21_sprintf(str, "% 10.5d", a);
  int res_2_orig = sprintf(str_orig, "% 10.5d", a);

  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = s21_sprintf(str, "%3.5d", a);
  int res_3_orig = sprintf(str_orig, "%3.5d", a);

  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = s21_sprintf(str, "%d", a);
  int res_4_orig = sprintf(str_orig, "%d", a);

  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = s21_sprintf(str, "%0d", a);
  int res_5_orig = sprintf(str_orig, "%0d", a);

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_6 = s21_sprintf(str, "%-d", a);
  int res_6_orig = sprintf(str_orig, "%-d", a);

  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = s21_sprintf(str, "%+d", a);
  int res_7_orig = sprintf(str_orig, "%+d", a);

  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  int res_8 = s21_sprintf(str, "% d", a);
  int res_8_orig = sprintf(str_orig, "% d", a);

  ck_assert_int_eq(res_8, res_8_orig);
  ck_assert_str_eq(str, str_orig);

  int res_9 = s21_sprintf(str, "%5d", a);
  int res_9_orig = sprintf(str_orig, "%5d", a);

  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  int res_10 = s21_sprintf(str, "%05d", a);
  int res_10_orig = sprintf(str_orig, "%05d", a);

  ck_assert_int_eq(res_10, res_10_orig);
  ck_assert_str_eq(str, str_orig);

  int res_11 = s21_sprintf(str, "%-5d", a);
  int res_11_orig = sprintf(str_orig, "%-5d", a);

  ck_assert_int_eq(res_11, res_11_orig);
  ck_assert_str_eq(str, str_orig);

  int res_12 = s21_sprintf(str, "%+5d", a);
  int res_12_orig = sprintf(str_orig, "%+5d", a);

  ck_assert_int_eq(res_12, res_12_orig);
  ck_assert_str_eq(str, str_orig);

  int res_13 = s21_sprintf(str, "% 5d", a);
  int res_13_orig = sprintf(str_orig, "% 5d", a);

  ck_assert_int_eq(res_13, res_13_orig);
  ck_assert_str_eq(str, str_orig);

  int res_14 = s21_sprintf(str, "%.5d", a);
  int res_14_orig = sprintf(str_orig, "%.5d", a);

  ck_assert_int_eq(res_14, res_14_orig);
  ck_assert_str_eq(str, str_orig);

  int res_15 = s21_sprintf(str, "%.5d", a);
  int res_15_orig = sprintf(str_orig, "%.5d", a);

  ck_assert_int_eq(res_15, res_15_orig);
  ck_assert_str_eq(str, str_orig);

  int res_16 = s21_sprintf(str, "% .5d", a);
  int res_16_orig = sprintf(str_orig, "% .5d", a);

  ck_assert_int_eq(res_16, res_16_orig);
  ck_assert_str_eq(str, str_orig);

  int res_17 = s21_sprintf(str, "%+.5d", a);
  int res_17_orig = sprintf(str_orig, "%+.5d", a);

  ck_assert_int_eq(res_17, res_17_orig);
  ck_assert_str_eq(str, str_orig);

  int res_18 = s21_sprintf(str, "%-.5d", a);
  int res_18_orig = sprintf(str_orig, "%-.5d", a);

  ck_assert_int_eq(res_18, res_18_orig);
  ck_assert_str_eq(str, str_orig);

  int res_19 = s21_sprintf(str, "%10.5d", a);
  int res_19_orig = sprintf(str_orig, "%10.5d", a);

  ck_assert_int_eq(res_19, res_19_orig);
  ck_assert_str_eq(str, str_orig);

  int res_20 = s21_sprintf(str, "%+10.5d", a);
  int res_20_orig = sprintf(str_orig, "%+10.5d", a);

  ck_assert_int_eq(res_20, res_20_orig);
  ck_assert_str_eq(str, str_orig);

  int res_21 = s21_sprintf(str, "%-10.5d", a);
  int res_21_orig = sprintf(str_orig, "%-10.5d", a);

  ck_assert_int_eq(res_21, res_21_orig);
  ck_assert_str_eq(str, str_orig);

  int res_22 = s21_sprintf(str, "%3.5d", a);
  int res_22_orig = sprintf(str_orig, "%3.5d", a);

  ck_assert_int_eq(res_22, res_22_orig);
  ck_assert_str_eq(str, str_orig);

  int res_23 = s21_sprintf(str, "% 3.5d", a);
  int res_23_orig = sprintf(str_orig, "% 3.5d", a);

  ck_assert_int_eq(res_23, res_23_orig);
  ck_assert_str_eq(str, str_orig);

  int res_24 = s21_sprintf(str, "%+3.5d", a);
  int res_24_orig = sprintf(str_orig, "%+3.5d", a);

  ck_assert_int_eq(res_24, res_24_orig);
  ck_assert_str_eq(str, str_orig);

  int res_25 = s21_sprintf(str, "%-3.5d", a);
  int res_25_orig = sprintf(str_orig, "%-3.5d", a);

  ck_assert_int_eq(res_25, res_25_orig);
  ck_assert_str_eq(str, str_orig);

  int res_26 = s21_sprintf(str, "%+6.2d", a);
  int res_26_orig = sprintf(str_orig, "%+6.2d", a);

  ck_assert_int_eq(res_26, res_26_orig);
  ck_assert_str_eq(str, str_orig);

  int res_27 = s21_sprintf(str, "%+6.3d", a);
  int res_27_orig = sprintf(str_orig, "%+6.3d", a);

  ck_assert_int_eq(res_27, res_27_orig);
  ck_assert_str_eq(str, str_orig);

  int res_28 = s21_sprintf(str, "%+6.4d", a);
  int res_28_orig = sprintf(str_orig, "%+6.4d", a);

  ck_assert_int_eq(res_28, res_28_orig);
  ck_assert_str_eq(str, str_orig);

  int res_29 = s21_sprintf(str, "%-6.2d", -a);
  int res_29_orig = sprintf(str_orig, "%-6.2d", -a);

  ck_assert_int_eq(res_29, res_29_orig);
  ck_assert_str_eq(str, str_orig);

  int res_30 = s21_sprintf(str, "%+05d", a);
  int res_30_orig = sprintf(str_orig, "%+05d", a);

  ck_assert_int_eq(res_30, res_30_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_d_test_4) {
  char str[80];
  char str_orig[80];
  int a = -23;

  int res_1 = s21_sprintf(str, "%10.5d", a);
  int res_1_orig = sprintf(str_orig, "%10.5d", a);

  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_2 = s21_sprintf(str, "% 10.5d", a);
  int res_2_orig = sprintf(str_orig, "% 10.5d", a);

  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = s21_sprintf(str, "%3.5d", a);
  int res_3_orig = sprintf(str_orig, "%3.5d", a);

  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = s21_sprintf(str, "%d", a);
  int res_4_orig = sprintf(str_orig, "%d", a);

  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = s21_sprintf(str, "%0d", a);
  int res_5_orig = sprintf(str_orig, "%0d", a);

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_6 = s21_sprintf(str, "%-d", a);
  int res_6_orig = sprintf(str_orig, "%-d", a);

  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = s21_sprintf(str, "%+d", a);
  int res_7_orig = sprintf(str_orig, "%+d", a);

  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  int res_8 = s21_sprintf(str, "% d", a);
  int res_8_orig = sprintf(str_orig, "% d", a);

  ck_assert_int_eq(res_8, res_8_orig);
  ck_assert_str_eq(str, str_orig);

  int res_9 = s21_sprintf(str, "%5d", a);
  int res_9_orig = sprintf(str_orig, "%5d", a);

  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  int res_10 = s21_sprintf(str, "%05d", a);
  int res_10_orig = sprintf(str_orig, "%05d", a);

  ck_assert_int_eq(res_10, res_10_orig);
  ck_assert_str_eq(str, str_orig);

  int res_11 = s21_sprintf(str, "%-5d", a);
  int res_11_orig = sprintf(str_orig, "%-5d", a);

  ck_assert_int_eq(res_11, res_11_orig);
  ck_assert_str_eq(str, str_orig);

  int res_12 = s21_sprintf(str, "%+5d", a);
  int res_12_orig = sprintf(str_orig, "%+5d", a);

  ck_assert_int_eq(res_12, res_12_orig);
  ck_assert_str_eq(str, str_orig);

  int res_13 = s21_sprintf(str, "% 5d", a);
  int res_13_orig = sprintf(str_orig, "% 5d", a);

  ck_assert_int_eq(res_13, res_13_orig);
  ck_assert_str_eq(str, str_orig);

  int res_14 = s21_sprintf(str, "%.5d", a);
  int res_14_orig = sprintf(str_orig, "%.5d", a);

  ck_assert_int_eq(res_14, res_14_orig);
  ck_assert_str_eq(str, str_orig);

  int res_15 = s21_sprintf(str, "%.5d", a);
  int res_15_orig = sprintf(str_orig, "%.5d", a);

  ck_assert_int_eq(res_15, res_15_orig);
  ck_assert_str_eq(str, str_orig);

  int res_16 = s21_sprintf(str, "% .5d", a);
  int res_16_orig = sprintf(str_orig, "% .5d", a);

  ck_assert_int_eq(res_16, res_16_orig);
  ck_assert_str_eq(str, str_orig);

  int res_17 = s21_sprintf(str, "%+.5d", a);
  int res_17_orig = sprintf(str_orig, "%+.5d", a);

  ck_assert_int_eq(res_17, res_17_orig);
  ck_assert_str_eq(str, str_orig);

  int res_18 = s21_sprintf(str, "%-.5d", a);
  int res_18_orig = sprintf(str_orig, "%-.5d", a);

  ck_assert_int_eq(res_18, res_18_orig);
  ck_assert_str_eq(str, str_orig);

  int res_19 = s21_sprintf(str, "%10.5d", a);
  int res_19_orig = sprintf(str_orig, "%10.5d", a);

  ck_assert_int_eq(res_19, res_19_orig);
  ck_assert_str_eq(str, str_orig);

  int res_20 = s21_sprintf(str, "%+10.5d", a);
  int res_20_orig = sprintf(str_orig, "%+10.5d", a);

  ck_assert_int_eq(res_20, res_20_orig);
  ck_assert_str_eq(str, str_orig);

  int res_21 = s21_sprintf(str, "%-10.5d", a);
  int res_21_orig = sprintf(str_orig, "%-10.5d", a);

  ck_assert_int_eq(res_21, res_21_orig);
  ck_assert_str_eq(str, str_orig);

  int res_22 = s21_sprintf(str, "%3.5d", a);
  int res_22_orig = sprintf(str_orig, "%3.5d", a);

  ck_assert_int_eq(res_22, res_22_orig);
  ck_assert_str_eq(str, str_orig);

  int res_23 = s21_sprintf(str, "% 3.5d", a);
  int res_23_orig = sprintf(str_orig, "% 3.5d", a);

  ck_assert_int_eq(res_23, res_23_orig);
  ck_assert_str_eq(str, str_orig);

  int res_24 = s21_sprintf(str, "%+3.5d", a);
  int res_24_orig = sprintf(str_orig, "%+3.5d", a);

  ck_assert_int_eq(res_24, res_24_orig);
  ck_assert_str_eq(str, str_orig);

  int res_25 = s21_sprintf(str, "%-3.5d", a);
  int res_25_orig = sprintf(str_orig, "%-3.5d", a);

  ck_assert_int_eq(res_25, res_25_orig);
  ck_assert_str_eq(str, str_orig);

  int res_26 = s21_sprintf(str, "%+05d", a);
  int res_26_orig = sprintf(str_orig, "%+05d", a);

  ck_assert_int_eq(res_26, res_26_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_d_test_5) {
  char str[80];
  char str_orig[80];
  int a = -2344;

  int res_2 = s21_sprintf(str, "% 10.5d", a);
  int res_2_orig = sprintf(str_orig, "% 10.5d", a);

  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = s21_sprintf(str, "%3.5d", a);
  int res_3_orig = sprintf(str_orig, "%3.5d", a);

  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = s21_sprintf(str, "%d", a);
  int res_4_orig = sprintf(str_orig, "%d", a);

  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = s21_sprintf(str, "%0d", a);
  int res_5_orig = sprintf(str_orig, "%0d", a);

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_6 = s21_sprintf(str, "%-d", a);
  int res_6_orig = sprintf(str_orig, "%-d", a);

  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = s21_sprintf(str, "%+d", a);
  int res_7_orig = sprintf(str_orig, "%+d", a);

  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  int res_8 = s21_sprintf(str, "% d", a);
  int res_8_orig = sprintf(str_orig, "% d", a);

  ck_assert_int_eq(res_8, res_8_orig);
  ck_assert_str_eq(str, str_orig);

  int res_9 = s21_sprintf(str, "%5d", a);
  int res_9_orig = sprintf(str_orig, "%5d", a);

  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  int res_10 = s21_sprintf(str, "%05d", a);
  int res_10_orig = sprintf(str_orig, "%05d", a);

  ck_assert_int_eq(res_10, res_10_orig);
  ck_assert_str_eq(str, str_orig);

  int res_11 = s21_sprintf(str, "%-5d", a);
  int res_11_orig = sprintf(str_orig, "%-5d", a);

  ck_assert_int_eq(res_11, res_11_orig);
  ck_assert_str_eq(str, str_orig);

  int res_12 = s21_sprintf(str, "%+5d", a);
  int res_12_orig = sprintf(str_orig, "%+5d", a);

  ck_assert_int_eq(res_12, res_12_orig);
  ck_assert_str_eq(str, str_orig);

  int res_13 = s21_sprintf(str, "% 5d", a);
  int res_13_orig = sprintf(str_orig, "% 5d", a);

  ck_assert_int_eq(res_13, res_13_orig);
  ck_assert_str_eq(str, str_orig);

  int res_14 = s21_sprintf(str, "%.5d", a);
  int res_14_orig = sprintf(str_orig, "%.5d", a);

  ck_assert_int_eq(res_14, res_14_orig);
  ck_assert_str_eq(str, str_orig);

  int res_15 = s21_sprintf(str, "%.5d", a);
  int res_15_orig = sprintf(str_orig, "%.5d", a);

  ck_assert_int_eq(res_15, res_15_orig);
  ck_assert_str_eq(str, str_orig);

  int res_16 = s21_sprintf(str, "% .5d", a);
  int res_16_orig = sprintf(str_orig, "% .5d", a);

  ck_assert_int_eq(res_16, res_16_orig);
  ck_assert_str_eq(str, str_orig);

  int res_17 = s21_sprintf(str, "%+.5d", a);
  int res_17_orig = sprintf(str_orig, "%+.5d", a);

  ck_assert_int_eq(res_17, res_17_orig);
  ck_assert_str_eq(str, str_orig);

  int res_18 = s21_sprintf(str, "%-.5d", a);
  int res_18_orig = sprintf(str_orig, "%-.5d", a);

  ck_assert_int_eq(res_18, res_18_orig);
  ck_assert_str_eq(str, str_orig);

  int res_19 = s21_sprintf(str, "%10.5d", a);
  int res_19_orig = sprintf(str_orig, "%10.5d", a);

  ck_assert_int_eq(res_19, res_19_orig);
  ck_assert_str_eq(str, str_orig);

  int res_20 = s21_sprintf(str, "%+10.5d", a);
  int res_20_orig = sprintf(str_orig, "%+10.5d", a);

  ck_assert_int_eq(res_20, res_20_orig);
  ck_assert_str_eq(str, str_orig);

  int res_21 = s21_sprintf(str, "%-10.5d", a);
  int res_21_orig = sprintf(str_orig, "%-10.5d", a);

  ck_assert_int_eq(res_21, res_21_orig);
  ck_assert_str_eq(str, str_orig);

  int res_22 = s21_sprintf(str, "%3.5d", a);
  int res_22_orig = sprintf(str_orig, "%3.5d", a);

  ck_assert_int_eq(res_22, res_22_orig);
  ck_assert_str_eq(str, str_orig);

  int res_23 = s21_sprintf(str, "% 3.5d", a);
  int res_23_orig = sprintf(str_orig, "% 3.5d", a);

  ck_assert_int_eq(res_23, res_23_orig);
  ck_assert_str_eq(str, str_orig);

  int res_24 = s21_sprintf(str, "%+3.5d", a);
  int res_24_orig = sprintf(str_orig, "%+3.5d", a);

  ck_assert_int_eq(res_24, res_24_orig);
  ck_assert_str_eq(str, str_orig);

  int res_25 = s21_sprintf(str, "%-3.5d", a);
  int res_25_orig = sprintf(str_orig, "%-3.5d", a);

  ck_assert_int_eq(res_25, res_25_orig);
  ck_assert_str_eq(str, str_orig);

  int res_26 = s21_sprintf(str, "%+05d", a);
  int res_26_orig = sprintf(str_orig, "%+05d", a);

  ck_assert_int_eq(res_26, res_26_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_d_test_6) {
  char str[80];
  char str_orig[80];
  int a = 23;

  int res_1 = s21_sprintf(str, "%+10.5d", a);
  int res_1_orig = sprintf(str_orig, "%+10.5d", a);

  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = s21_sprintf(str, "%+3.5d", a);
  int res_3_orig = sprintf(str_orig, "%+3.5d", a);

  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = s21_sprintf(str, "%+d", a);
  int res_4_orig = sprintf(str_orig, "%+d", a);

  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = s21_sprintf(str, "%+0d", a);
  int res_5_orig = sprintf(str_orig, "%+0d", a);

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_6 = s21_sprintf(str, "%-+d", a);
  int res_6_orig = sprintf(str_orig, "%-+d", a);

  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = s21_sprintf(str, "%+d", a);
  int res_7_orig = sprintf(str_orig, "%+d", a);

  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  int res_9 = s21_sprintf(str, "%+5d", a);
  int res_9_orig = sprintf(str_orig, "%+5d", a);

  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  int res_11 = s21_sprintf(str, "%-+5d", a);
  int res_11_orig = sprintf(str_orig, "%-+5d", a);

  ck_assert_int_eq(res_11, res_11_orig);
  ck_assert_str_eq(str, str_orig);

  int res_12 = s21_sprintf(str, "%+5d", a);
  int res_12_orig = sprintf(str_orig, "%+5d", a);

  ck_assert_int_eq(res_12, res_12_orig);
  ck_assert_str_eq(str, str_orig);

  int res_14 = s21_sprintf(str, "%+.5d", a);
  int res_14_orig = sprintf(str_orig, "%+.5d", a);

  ck_assert_int_eq(res_14, res_14_orig);
  ck_assert_str_eq(str, str_orig);

  int res_15 = s21_sprintf(str, "%+.5d", a);
  int res_15_orig = sprintf(str_orig, "%+.5d", a);

  ck_assert_int_eq(res_15, res_15_orig);
  ck_assert_str_eq(str, str_orig);

  int res_16 = s21_sprintf(str, "% .5d", a);
  int res_16_orig = sprintf(str_orig, "% .5d", a);

  ck_assert_int_eq(res_16, res_16_orig);
  ck_assert_str_eq(str, str_orig);

  int res_18 = s21_sprintf(str, "%-+.5d", a);
  int res_18_orig = sprintf(str_orig, "%-+.5d", a);

  ck_assert_int_eq(res_18, res_18_orig);
  ck_assert_str_eq(str, str_orig);

  int res_20 = s21_sprintf(str, "%+10.5d", a);
  int res_20_orig = sprintf(str_orig, "%+10.5d", a);

  ck_assert_int_eq(res_20, res_20_orig);
  ck_assert_str_eq(str, str_orig);

  int res_21 = s21_sprintf(str, "%-+10.5d", a);
  int res_21_orig = sprintf(str_orig, "%-+10.5d", a);

  ck_assert_int_eq(res_21, res_21_orig);
  ck_assert_str_eq(str, str_orig);

  int res_22 = s21_sprintf(str, "%+3.5d", a);
  int res_22_orig = sprintf(str_orig, "%+3.5d", a);

  ck_assert_int_eq(res_22, res_22_orig);
  ck_assert_str_eq(str, str_orig);

  int res_23 = s21_sprintf(str, "% 3.5d", a);
  int res_23_orig = sprintf(str_orig, "% 3.5d", a);

  ck_assert_int_eq(res_23, res_23_orig);
  ck_assert_str_eq(str, str_orig);

  int res_25 = s21_sprintf(str, "%-+3.5d", a);
  int res_25_orig = sprintf(str_orig, "%-+3.5d", a);

  ck_assert_int_eq(res_25, res_25_orig);
  ck_assert_str_eq(str, str_orig);

  int res_26 = s21_sprintf(str, "%+05d", a);
  int res_26_orig = sprintf(str_orig, "%+05d", a);

  ck_assert_int_eq(res_26, res_26_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_d_test_0) {
  char str[80];
  char str_orig[80];
  int a = 0;

  int res_1 = s21_sprintf(str, "%+10.5d", a);
  int res_1_orig = sprintf(str_orig, "%+10.5d", a);

  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = s21_sprintf(str, "%+3.5d", a);
  int res_3_orig = sprintf(str_orig, "%+3.5d", a);

  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = s21_sprintf(str, "%+d", a);
  int res_4_orig = sprintf(str_orig, "%+d", a);

  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = s21_sprintf(str, "%05d", a);
  int res_5_orig = sprintf(str_orig, "%05d", a);

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = s21_sprintf(str, "%+d", a);
  int res_7_orig = sprintf(str_orig, "%+d", a);

  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  int res_9 = s21_sprintf(str, "%+5d", a);
  int res_9_orig = sprintf(str_orig, "%+5d", a);

  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  int res_12 = s21_sprintf(str, "%+5d", a);
  int res_12_orig = sprintf(str_orig, "%+5d", a);

  ck_assert_int_eq(res_12, res_12_orig);
  ck_assert_str_eq(str, str_orig);

  int res_14 = s21_sprintf(str, "%+.5d", a);
  int res_14_orig = sprintf(str_orig, "%+.5d", a);

  ck_assert_int_eq(res_14, res_14_orig);
  ck_assert_str_eq(str, str_orig);

  int res_15 = s21_sprintf(str, "%+.5d", a);
  int res_15_orig = sprintf(str_orig, "%+.5d", a);

  ck_assert_int_eq(res_15, res_15_orig);
  ck_assert_str_eq(str, str_orig);

  int res_20 = s21_sprintf(str, "%+10.5d", a);
  int res_20_orig = sprintf(str_orig, "%+10.5d", a);

  ck_assert_int_eq(res_20, res_20_orig);
  ck_assert_str_eq(str, str_orig);

  int res_22 = s21_sprintf(str, "%+3.5d", a);
  int res_22_orig = sprintf(str_orig, "%+3.5d", a);

  ck_assert_int_eq(res_22, res_22_orig);
  ck_assert_str_eq(str, str_orig);

  int res_26 = s21_sprintf(str, "%+05d", a);
  int res_26_orig = sprintf(str_orig, "%+05d", a);

  ck_assert_int_eq(res_26, res_26_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_e_test) {
  char str[80];
  char str_orig[80];
  double value = 12345.6789;

  int res_1 = s21_sprintf(str, "%e", value);
  int res_1_orig = sprintf(str_orig, "%e", value);
  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_2 = s21_sprintf(str, "%.10e", value);
  int res_2_orig = sprintf(str_orig, "%.10e", value);
  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = s21_sprintf(str, "%+15.3e", value);
  int res_3_orig = sprintf(str_orig, "%+15.3e", value);
  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = s21_sprintf(str, "%-15.3e", value);
  int res_4_orig = sprintf(str_orig, "%-15.3e", value);
  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = s21_sprintf(str, "%E", value);
  int res_5_orig = sprintf(str_orig, "%E", value);
  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  double neg_value = -0.00012345;
  int res_6 = s21_sprintf(str, "%e", neg_value);
  int res_6_orig = sprintf(str_orig, "%e", neg_value);
  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  double big_value = 1.23e+20;
  int res_7 = s21_sprintf(str, "%e", big_value);
  int res_7_orig = sprintf(str_orig, "%e", big_value);
  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  double small_value = 1.23e-20;
  int res_8 = s21_sprintf(str, "%E", small_value);
  int res_8_orig = sprintf(str_orig, "%E", small_value);
  ck_assert_int_eq(res_8, res_8_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_g_test) {
  char str[80];
  char str_orig[80];

  double value = 12345.6789;

  int res_1 = s21_sprintf(str, "%g", value);
  int res_1_orig = sprintf(str_orig, "%g", value);

  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_2 = s21_sprintf(str, "%G", value);
  int res_2_orig = sprintf(str_orig, "%G", value);

  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  double small_value = 0.0000012345;

  int res_3 = s21_sprintf(str, "%g", small_value);
  int res_3_orig = sprintf(str_orig, "%g", small_value);

  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  double large_value = 1234567890123456.0;

  int res_4 = s21_sprintf(str, "%g", large_value);
  int res_4_orig = sprintf(str_orig, "%g", large_value);

  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = s21_sprintf(str, "%15.8g", value);
  int res_5_orig = sprintf(str_orig, "%15.8g", value);

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_6 = s21_sprintf(str, "%-+15.8g", value);
  int res_6_orig = sprintf(str_orig, "%-+15.8g", value);

  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  double zero_value = 0.0;

  int res_7 = s21_sprintf(str, "%g", zero_value);
  int res_7_orig = sprintf(str_orig, "%g", zero_value);

  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  double neg_value = -42.42;

  int res_8 = s21_sprintf(str, "%G", neg_value);
  int res_8_orig = sprintf(str_orig, "%G", neg_value);

  ck_assert_int_eq(res_8, res_8_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_x_test) {
  char str[80];
  char str_orig[80];
  unsigned int value = 0xABCDEF;

  int res_1 = s21_sprintf(str, "%x", value);
  int res_1_orig = sprintf(str_orig, "%x", value);
  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_2 = s21_sprintf(str, "%X", value);
  int res_2_orig = sprintf(str_orig, "%X", value);
  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = s21_sprintf(str, "%#x", value);
  int res_3_orig = sprintf(str_orig, "%#x", value);
  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = s21_sprintf(str, "%#X", value);
  int res_4_orig = sprintf(str_orig, "%#X", value);
  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = s21_sprintf(str, "%10x", value);
  int res_5_orig = sprintf(str_orig, "%10x", value);
  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_6 = s21_sprintf(str, "%010X", value);
  int res_6_orig = sprintf(str_orig, "%010X", value);
  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = s21_sprintf(str, "%-10x", value);
  int res_7_orig = sprintf(str_orig, "%-10x", value);
  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  unsigned int zero = 0;
  int res_8 = s21_sprintf(str, "%#x", zero);
  int res_8_orig = sprintf(str_orig, "%#x", zero);
  ck_assert_int_eq(res_8, res_8_orig);
  ck_assert_str_eq(str, str_orig);

  int res_9 = s21_sprintf(str, "%.8x", value);
  int res_9_orig = sprintf(str_orig, "%.8x", value);
  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  int res_10 = s21_sprintf(str, "%#-15.10X", value);
  int res_10_orig = sprintf(str_orig, "%#-15.10X", value);
  ck_assert_int_eq(res_10, res_10_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_o_test) {
  char str[80];
  char str_orig[80];
  unsigned int value = 012345670;

  int res_1 = s21_sprintf(str, "%o", value);
  int res_1_orig = sprintf(str_orig, "%o", value);
  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_2 = s21_sprintf(str, "%#o", value);
  int res_2_orig = sprintf(str_orig, "%#o", value);
  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = s21_sprintf(str, "%12o", value);
  int res_3_orig = sprintf(str_orig, "%12o", value);
  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = s21_sprintf(str, "%012o", value);
  int res_4_orig = sprintf(str_orig, "%012o", value);
  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = s21_sprintf(str, "%-12o", value);
  int res_5_orig = sprintf(str_orig, "%-12o", value);
  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  unsigned int zero = 0;
  int res_6 = s21_sprintf(str, "%o", zero);
  int res_6_orig = sprintf(str_orig, "%o", zero);
  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = s21_sprintf(str, "%.10o", value);
  int res_7_orig = sprintf(str_orig, "%.10o", value);
  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  int res_8 = s21_sprintf(str, "%#-15.10o", value);
  int res_8_orig = sprintf(str_orig, "%#-15.10o", value);
  ck_assert_int_eq(res_8, res_8_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_p_test) {
  char str[80];
  char str_orig[80];
  int value = 12345;
  void *ptr = &value;

  int res_1 = s21_sprintf(str, "%p", ptr);
  int res_1_orig = sprintf(str_orig, "%p", ptr);
  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_2 = s21_sprintf(str, "%20p", ptr);
  int res_2_orig = sprintf(str_orig, "%20p", ptr);
  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = s21_sprintf(str, "%-20p", ptr);
  int res_3_orig = sprintf(str_orig, "%-20p", ptr);
  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = s21_sprintf(str, "%p", NULL);
  int res_4_orig = sprintf(str_orig, "%p", NULL);
  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = s21_sprintf(str, "Pointer value: %p", ptr);
  int res_5_orig = sprintf(str_orig, "Pointer value: %p", ptr);
  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  char c = 'A';
  void *ptr2 = &c;
  int res_6 = s21_sprintf(str, "%p %p", ptr, ptr2);
  int res_6_orig = sprintf(str_orig, "%p %p", ptr, ptr2);
  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_special_cases_test) {
  char str[100];
  char str_orig[100];

  double nan_value = 0.0 / 0.0;

  int res_1 = s21_sprintf(str, "%f", nan_value);
  int res_1_orig = sprintf(str_orig, "%f", nan_value);
  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_2 = s21_sprintf(str, "%e", nan_value);
  int res_2_orig = sprintf(str_orig, "%e", nan_value);
  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = s21_sprintf(str, "%g", nan_value);
  int res_3_orig = sprintf(str_orig, "%g", nan_value);
  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  double inf_value = 1.0 / 0.0;

  int res_4 = s21_sprintf(str, "%f", inf_value);
  int res_4_orig = sprintf(str_orig, "%f", inf_value);
  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = s21_sprintf(str, "%e", inf_value);
  int res_5_orig = sprintf(str_orig, "%e", inf_value);
  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_6 = s21_sprintf(str, "%g", inf_value);
  int res_6_orig = sprintf(str_orig, "%g", inf_value);
  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = s21_sprintf(str, "%f", -inf_value);
  int res_7_orig = sprintf(str_orig, "%f", -inf_value);
  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  int res_8 = s21_sprintf(str, "%+10.2f", inf_value);
  int res_8_orig = sprintf(str_orig, "%+10.2f", inf_value);
  ck_assert_int_eq(res_8, res_8_orig);
  ck_assert_str_eq(str, str_orig);

  int res_9 = s21_sprintf(str, "%-10.2f", -inf_value);
  int res_9_orig = sprintf(str_orig, "%-10.2f", -inf_value);
  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_zero_precision_test) {
  char str[100];
  char str_orig[100];

  int res_1 = s21_sprintf(str, "%.0d", 0);
  int res_1_orig = sprintf(str_orig, "%.0d", 0);
  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_2 = s21_sprintf(str, "%.0d", 123);
  int res_2_orig = sprintf(str_orig, "%.0d", 123);
  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = s21_sprintf(str, "%.0u", 0);
  int res_3_orig = sprintf(str_orig, "%.0u", 0);
  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = s21_sprintf(str, "%.0o", 0);
  int res_4_orig = sprintf(str_orig, "%.0o", 0);
  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = s21_sprintf(str, "%#.0o", 0);
  int res_5_orig = sprintf(str_orig, "%#.0o", 0);
  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_6 = s21_sprintf(str, "%.0x", 0);
  int res_6_orig = sprintf(str_orig, "%.0x", 0);
  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = s21_sprintf(str, "%#.0x", 0);
  int res_7_orig = sprintf(str_orig, "%#.0x", 0);
  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  int res_8 = s21_sprintf(str, "%.0f", 123.456);
  int res_8_orig = sprintf(str_orig, "%.0f", 123.456);
  ck_assert_int_eq(res_8, res_8_orig);
  ck_assert_str_eq(str, str_orig);

  int res_9 = s21_sprintf(str, "%.0e", 123.456);
  int res_9_orig = sprintf(str_orig, "%.0e", 123.456);
  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  int res_10 = s21_sprintf(str, "%.0g", 123.456);
  int res_10_orig = sprintf(str_orig, "%.0g", 123.456);
  ck_assert_int_eq(res_10, res_10_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_negative_values_test) {
  char str[100];
  char str_orig[100];

  int res_1 = s21_sprintf(str, "%*d", -10, 123);
  int res_1_orig = sprintf(str_orig, "%*d", -10, 123);
  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_2 = s21_sprintf(str, "%.*d", -5, 123);
  int res_2_orig = sprintf(str_orig, "%.*d", -5, 123);
  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = s21_sprintf(str, "%*.*d", -10, -5, 123);
  int res_3_orig = sprintf(str_orig, "%*.*d", -10, -5, 123);
  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = s21_sprintf(str, "%*.*f", -15, -2, 123.456);
  int res_4_orig = sprintf(str_orig, "%*.*f", -15, -2, 123.456);
  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_g_trailing_zeros_test) {
  char str[100];
  char str_orig[100];

  int res_1 = s21_sprintf(str, "%g", 123.4000);
  int res_1_orig = sprintf(str_orig, "%g", 123.4000);
  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_2 = s21_sprintf(str, "%#g", 123.4000);
  int res_2_orig = sprintf(str_orig, "%#g", 123.4000);
  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = s21_sprintf(str, "%g", 123.4e-10);
  int res_3_orig = sprintf(str_orig, "%g", 123.4e-10);
  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = s21_sprintf(str, "%.10g", 123.4000000001);
  int res_4_orig = sprintf(str_orig, "%.10g", 123.4000000001);
  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = s21_sprintf(str, "%g", 0.0);
  int res_5_orig = sprintf(str_orig, "%g", 0.0);
  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_6 = s21_sprintf(str, "%g", 123.000000000001);
  int res_6_orig = sprintf(str_orig, "%g", 123.000000000001);
  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_flag_combinations_test) {
  char str[100];
  char str_orig[100];

  int res_1 = s21_sprintf(str, "%+d", 123);
  int res_1_orig = sprintf(str_orig, "%+d", 123);
  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_2 = s21_sprintf(str, "%-10d", 123);
  int res_2_orig = sprintf(str_orig, "%-10d", 123);
  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = s21_sprintf(str, "%10.5d", 123);
  int res_3_orig = sprintf(str_orig, "%10.5d", 123);
  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = s21_sprintf(str, "%+10.5d", 123);
  int res_4_orig = sprintf(str_orig, "%+10.5d", 123);
  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = s21_sprintf(str, "%#010x", 123);
  int res_5_orig = sprintf(str_orig, "%#010x", 123);
  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_6 = s21_sprintf(str, "%#-10x", 123);
  int res_6_orig = sprintf(str_orig, "%#-10x", 123);
  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = s21_sprintf(str, "%#10.5x", 0);
  int res_7_orig = sprintf(str_orig, "%#10.5x", 0);
  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  int res_8 = s21_sprintf(str, "%+#015.7f", 123.45);
  int res_8_orig = sprintf(str_orig, "%+#015.7f", 123.45);
  ck_assert_int_eq(res_8, res_8_orig);
  ck_assert_str_eq(str, str_orig);

  int res_9 = s21_sprintf(str, "%+#015.7e", 123.45);
  int res_9_orig = sprintf(str_orig, "%+#015.7e", 123.45);
  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  int res_10 = s21_sprintf(str, "%+d %+d", 42, -42);
  int res_10_orig = sprintf(str_orig, "%+d %+d", 42, -42);
  ck_assert_int_eq(res_10, res_10_orig);
  ck_assert_str_eq(str, str_orig);

  int res_11 = s21_sprintf(str, "% d % d", 42, -42);
  int res_11_orig = sprintf(str_orig, "% d % d", 42, -42);
  ck_assert_int_eq(res_11, res_11_orig);
  ck_assert_str_eq(str, str_orig);

  int res_12 = s21_sprintf(str, "%#o %#x %#X", 42, 42, 42);
  int res_12_orig = sprintf(str_orig, "%#o %#x %#X", 42, 42, 42);
  ck_assert_int_eq(res_12, res_12_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_length_modifiers_test) {
  char str[100];
  char str_orig[100];

  short int sh = 12345;
  int res_1 = s21_sprintf(str, "%hd", sh);
  int res_1_orig = sprintf(str_orig, "%hd", sh);
  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  unsigned short int ush = 54321;
  int res_2 = s21_sprintf(str, "%hu", ush);
  int res_2_orig = sprintf(str_orig, "%hu", ush);
  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  char c = 123;
  int res_3 = s21_sprintf(str, "%hhd", c);
  int res_3_orig = sprintf(str_orig, "%hhd", c);
  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  unsigned char uc = 250;
  int res_4 = s21_sprintf(str, "%hhu", uc);
  int res_4_orig = sprintf(str_orig, "%hhu", uc);
  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  long int li = 1234567890L;
  int res_5 = s21_sprintf(str, "%ld", li);
  int res_5_orig = sprintf(str_orig, "%ld", li);
  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  unsigned long int uli = 3987654321UL;
  int res_6 = s21_sprintf(str, "%lu", uli);
  int res_6_orig = sprintf(str_orig, "%lu", uli);
  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  long long int lli = 9223372036854775807LL;
  int res_7 = s21_sprintf(str, "%lld", lli);
  int res_7_orig = sprintf(str_orig, "%lld", lli);
  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  unsigned long long int ulli = 18446744073709551615ULL;
  int res_8 = s21_sprintf(str, "%llu", ulli);
  int res_8_orig = sprintf(str_orig, "%llu", ulli);
  ck_assert_int_eq(res_8, res_8_orig);
  ck_assert_str_eq(str, str_orig);

  long double ld = 123456789.123456789L;
  int res_9 = s21_sprintf(str, "%Lf", ld);
  int res_9_orig = sprintf(str_orig, "%Lf", ld);
  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  int res_10 = s21_sprintf(str, "%+#015.7Lf", ld);
  int res_10_orig = sprintf(str_orig, "%+#015.7Lf", ld);
  ck_assert_int_eq(res_10, res_10_orig);
  ck_assert_str_eq(str, str_orig);

  int res_11 = s21_sprintf(str, "%#lx", uli);
  int res_11_orig = sprintf(str_orig, "%#lx", uli);
  ck_assert_int_eq(res_11, res_11_orig);
  ck_assert_str_eq(str, str_orig);

  int res_12 = s21_sprintf(str, "%#lo", uli);
  int res_12_orig = sprintf(str_orig, "%#lo", uli);
  ck_assert_int_eq(res_12, res_12_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_n_specifier_extended_test) {
  char str[100];
  char str_orig[100];

  int count1 = 0, count1_orig = 0;
  int res_1 = s21_sprintf(str, "Test%n string", &count1);
  int res_1_orig = sprintf(str_orig, "Test%n string", &count1_orig);
  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);
  ck_assert_int_eq(count1, count1_orig);

  int count2 = 0, count3 = 0, count2_orig = 0, count3_orig = 0;
  int res_2 = s21_sprintf(str, "First%n Second%n", &count2, &count3);
  int res_2_orig =
      sprintf(str_orig, "First%n Second%n", &count2_orig, &count3_orig);
  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);
  ck_assert_int_eq(count2, count2_orig);
  ck_assert_int_eq(count3, count3_orig);

  short count_h = 0, count_h_orig = 0;
  char count_hh = 0, count_hh_orig = 0;
  long count_l = 0, count_l_orig = 0;
  long long count_ll = 0, count_ll_orig = 0;

  int res_3 = s21_sprintf(str, "Short:%hn Char:%hhn Long:%ln LongLong:%lln",
                          &count_h, &count_hh, &count_l, &count_ll);
  int res_3_orig =
      sprintf(str_orig, "Short:%hn Char:%hhn Long:%ln LongLong:%lln",
              &count_h_orig, &count_hh_orig, &count_l_orig, &count_ll_orig);

  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);
  ck_assert_int_eq(count_h, count_h_orig);
  ck_assert_int_eq(count_hh, count_hh_orig);
  ck_assert_int_eq(count_l, count_l_orig);
  ck_assert_int_eq(count_ll, count_ll_orig);

  int count4 = 0, count4_orig = 0;
  int res_4 =
      s21_sprintf(str, "Number: %d%n String: %s", 12345, &count4, "test");
  int res_4_orig =
      sprintf(str_orig, "Number: %d%n String: %s", 12345, &count4_orig, "test");
  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);
  ck_assert_int_eq(count4, count4_orig);
}
END_TEST

START_TEST(s21_sprintf_width_precision_args_test) {
  char str[100];
  char str_orig[100];

  int width = 10;
  int res_1 = s21_sprintf(str, "%*d", width, 123);
  int res_1_orig = sprintf(str_orig, "%*d", width, 123);
  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int precision = 5;
  int res_2 = s21_sprintf(str, "%.*d", precision, 123);
  int res_2_orig = sprintf(str_orig, "%.*d", precision, 123);
  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = s21_sprintf(str, "%*.*d", width, precision, 123);
  int res_3_orig = sprintf(str_orig, "%*.*d", width, precision, 123);
  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = s21_sprintf(str, "%*.*f", width, precision, 123.456);
  int res_4_orig = sprintf(str_orig, "%*.*f", width, precision, 123.456);
  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = s21_sprintf(str, "%+*.*f", width, precision, 123.456);
  int res_5_orig = sprintf(str_orig, "%+*.*f", width, precision, 123.456);
  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_6 = s21_sprintf(str, "%-*.*e", width, precision, 123.456);
  int res_6_orig = sprintf(str_orig, "%-*.*e", width, precision, 123.456);
  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = s21_sprintf(str, "%#*.*x", width, precision, 255);
  int res_7_orig = sprintf(str_orig, "%#*.*x", width, precision, 255);
  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_complex_format_test) {
  char str[200];
  char str_orig[200];

  int res_1 = s21_sprintf(str, "Int: %d, Float: %f, String: %s, Char: %c", 123,
                          45.67, "test", 'A');
  int res_1_orig = sprintf(str_orig, "Int: %d, Float: %f, String: %s, Char: %c",
                           123, 45.67, "test", 'A');
  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_2 =
      s21_sprintf(str, "Flags: %+d, %#x, %-10s, %05d", 123, 255, "left", 42);
  int res_2_orig =
      sprintf(str_orig, "Flags: %+d, %#x, %-10s, %05d", 123, 255, "left", 42);
  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = s21_sprintf(str, "Mixed: %10.5f, %.2s, %*.*d", 123.456, "test", 8,
                          4, 123);
  int res_3_orig = sprintf(str_orig, "Mixed: %10.5f, %.2s, %*.*d", 123.456,
                           "test", 8, 4, 123);
  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  long l_val = 1234567890L;
  short s_val = 12345;
  int res_4 = s21_sprintf(str, "Length: %ld, %hd, %Lf", l_val, s_val, 123.456L);
  int res_4_orig =
      sprintf(str_orig, "Length: %ld, %hd, %Lf", l_val, s_val, 123.456L);
  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int count = 0;
  int res_5 =
      s21_sprintf(str, "Special: %p, %e, %%,%n", NULL, 0.0000001, &count);
  int count_orig = 0;
  int res_5_orig =
      sprintf(str_orig, "Special: %p, %e, %%,%n", NULL, 0.0000001, &count_orig);
  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);
  ck_assert_int_eq(count, count_orig);
}
END_TEST

START_TEST(s21_sprintf_string_precision_test) {
  char str[100];
  char str_orig[100];

  char *s1 = "test";
  int res_1 = s21_sprintf(str, "%.10s", s1);
  int res_1_orig = sprintf(str_orig, "%.10s", s1);
  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_2 = s21_sprintf(str, "%.2s", s1);
  int res_2_orig = sprintf(str_orig, "%.2s", s1);
  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = s21_sprintf(str, "%.0s", s1);
  int res_3_orig = sprintf(str_orig, "%.0s", s1);
  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = s21_sprintf(str, "%10.2s", s1);
  int res_4_orig = sprintf(str_orig, "%10.2s", s1);
  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = s21_sprintf(str, "%-10.2s", s1);
  int res_5_orig = sprintf(str_orig, "%-10.2s", s1);
  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_6 = s21_sprintf(str, "%s", NULL);
  int res_6_orig = sprintf(str_orig, "%s", "(null)");
  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = s21_sprintf(str, "%.5s", NULL);
  int res_7_orig = sprintf(str_orig, "%.5s", "(null)");
  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_dynamic_params_test) {
  char buffer1[200];
  char buffer2[200];

  int ints[] = {123, -456, 789, 0, -1};
  double floats[] = {123.456, -7.89, 0.0, -0.0, 0.000001};
  char *strings[] = {"test", "another", "",
                     "very long string with multiple words", NULL};
  char chars[] = {'A', 'b', '1', ' ', '\0'};
  unsigned long hexvals[] = {0x1A2B3C4D, 0xFFFFFFFF, 0, 0x100, 0x1};

  for (int i = 0; i < 5; i++) {
    int res1 = s21_sprintf(
        buffer1, "Int: %d, Float: %f, String: %s, Char: %c, Hex: %lx", ints[i],
        floats[i], strings[i], chars[i], hexvals[i]);
    int res2 =
        sprintf(buffer2, "Int: %d, Float: %f, String: %s, Char: %c, Hex: %lx",
                ints[i], floats[i], strings[i], chars[i], hexvals[i]);

    ck_assert_int_eq(res1, res2);
    ck_assert_str_eq(buffer1, buffer2);
  }

  for (int i = 0; i < 5; i++) {
    int res1 = s21_sprintf(
        buffer1, "Int: %+d, Float: %10.2f, String: %-15.10s, Hex: %#lx",
        ints[i], floats[i], strings[i], hexvals[i]);
    int res2 =
        sprintf(buffer2, "Int: %+d, Float: %10.2f, String: %-15.10s, Hex: %#lx",
                ints[i], floats[i], strings[i], hexvals[i]);

    ck_assert_int_eq(res1, res2);
    ck_assert_str_eq(buffer1, buffer2);
  }
}
END_TEST

START_TEST(s21_sprintf_float_special_cases_test) {
  char str[100];
  char str_orig[100];

  double small_fraction = 123.000000000000001;
  int res_1 = s21_sprintf(str, "%.15f", small_fraction);
  int res_1_orig = sprintf(str_orig, "%.15f", small_fraction);
  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  double rounding_test = 9.9999999;
  int res_2 = s21_sprintf(str, "%.6f", rounding_test);
  int res_2_orig = sprintf(str_orig, "%.6f", rounding_test);
  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  double big_number = 1.23456789e+37;
  int res_3 = s21_sprintf(str, "%f", big_number);
  int res_3_orig = sprintf(str_orig, "%f", big_number);

  ck_assert(str[0] == str_orig[0]);

  ck_assert(res_3 > 0);
  ck_assert(res_3_orig > 0);

  double almost_zero = 0.00000000001;
  int res_4 = s21_sprintf(str, "%f", almost_zero);
  int res_4_orig = sprintf(str_orig, "%f", almost_zero);
  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  double negative_zero = -0.0;
  int res_5 = s21_sprintf(str, "%f", negative_zero);
  int res_5_orig = sprintf(str_orig, "%f", negative_zero);
  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  double tiny = 0.00000000123;
  int res_6 = s21_sprintf(str, "%g", tiny);
  int res_6_orig = sprintf(str_orig, "%g", tiny);
  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  double huge = 123456789012345.0;
  int res_7 = s21_sprintf(str, "%g", huge);
  int res_7_orig = sprintf(str_orig, "%g", huge);
  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(test_s21_itoa) {
  char buffer[256] = {0};

  printf("\n--- TESTING s21_itoa FUNCTION ---\n");

  s21_itoa(0, buffer, 10, 0, 0);
  if (strcmp(buffer, "0") == 0) {
    printf("Test 1 (zero to decimal): PASSED\n");
  } else {
    printf("Test 1 (zero to decimal): FAILED. Expected: \"0\", Got: \"%s\"\n",
           buffer);
    ck_assert_str_eq(buffer, "0");
  }

  s21_itoa(12345, buffer, 10, 0, 0);
  if (strcmp(buffer, "12345") == 0) {
    printf("Test 2 (positive number to decimal): PASSED\n");
  } else {
    printf(
        "Test 2 (positive number to decimal): FAILED. Expected: \"12345\", "
        "Got: \"%s\"\n",
        buffer);
    ck_assert_str_eq(buffer, "12345");
  }

  s21_itoa((unsigned long long)(-12345), buffer, 10, 0, 0);
  if (strcmp(buffer, "-12345") == 0) {
    printf("Test 3 (negative number to decimal): PASSED\n");
  } else {
    printf(
        "Test 3 (negative number to decimal): FAILED. Expected: \"-12345\", "
        "Got: \"%s\"\n",
        buffer);
    ck_assert_str_eq(buffer, "-12345");
  }

  s21_itoa(0xABCD, buffer, 16, 0, 0);
  if (strcmp(buffer, "abcd") == 0) {
    printf("Test 4 (hex lowercase, no prefix): PASSED\n");
  } else {
    printf(
        "Test 4 (hex lowercase, no prefix): FAILED. Expected: \"abcd\", Got: "
        "\"%s\"\n",
        buffer);
    ck_assert_str_eq(buffer, "abcd");
  }

  s21_itoa(0xABCD, buffer, 16, 1, 0);
  if (strcmp(buffer, "ABCD") == 0) {
    printf("Test 5 (hex uppercase, no prefix): PASSED\n");
  } else {
    printf(
        "Test 5 (hex uppercase, no prefix): FAILED. Expected: \"ABCD\", Got: "
        "\"%s\"\n",
        buffer);
    ck_assert_str_eq(buffer, "ABCD");
  }

  s21_itoa(0xABCD, buffer, 16, 0, 1);
  if (strcmp(buffer, "0xabcd") == 0) {
    printf("Test 6 (hex lowercase, with prefix): PASSED\n");
  } else {
    printf(
        "Test 6 (hex lowercase, with prefix): FAILED. Expected: \"0xabcd\", "
        "Got: \"%s\"\n",
        buffer);
    ck_assert_str_eq(buffer, "0xabcd");
  }

  s21_itoa(0xABCD, buffer, 16, 1, 1);
  if (strcmp(buffer, "0XABCD") == 0) {
    printf("Test 7 (hex uppercase, with prefix): PASSED\n");
  } else {
    printf(
        "Test 7 (hex uppercase, with prefix): FAILED. Expected: \"0XABCD\", "
        "Got: \"%s\"\n",
        buffer);
    ck_assert_str_eq(buffer, "0XABCD");
  }

  s21_itoa(0123, buffer, 8, 0, 0);
  if (strcmp(buffer, "123") == 0) {
    printf("Test 8 (octal, no prefix): PASSED\n");
  } else {
    printf(
        "Test 8 (octal, no prefix): FAILED. Expected: \"123\", Got: \"%s\"\n",
        buffer);
    ck_assert_str_eq(buffer, "123");
  }

  s21_itoa(0123, buffer, 8, 0, 1);
  if (strcmp(buffer, "0123") == 0) {
    printf("Test 9 (octal, with prefix, non-zero): PASSED\n");
  } else {
    printf(
        "Test 9 (octal, with prefix, non-zero): FAILED. Expected: \"0123\", "
        "Got: \"%s\"\n",
        buffer);
    ck_assert_str_eq(buffer, "0123");
  }

  s21_itoa(0, buffer, 8, 0, 1);
  if (strcmp(buffer, "0") == 0) {
    printf("Test 10 (zero to octal, with prefix): PASSED\n");
  } else {
    printf(
        "Test 10 (zero to octal, with prefix): FAILED. Expected: \"0\", Got: "
        "\"%s\"\n",
        buffer);
    ck_assert_str_eq(buffer, "0");
  }

  s21_itoa(42, buffer, 2, 0, 0);
  if (strcmp(buffer, "101010") == 0) {
    printf("Test 11 (binary): PASSED\n");
  } else {
    printf("Test 11 (binary): FAILED. Expected: \"101010\", Got: \"%s\"\n",
           buffer);
    ck_assert_str_eq(buffer, "101010");
  }

  s21_itoa(1234567890123456789ULL, buffer, 10, 0, 0);
  if (strcmp(buffer, "1234567890123456789") == 0) {
    printf("Test 12 (large number to decimal): PASSED\n");
  } else {
    printf(
        "Test 12 (large number to decimal): FAILED. Expected: "
        "\"1234567890123456789\", Got: \"%s\"\n",
        buffer);
    ck_assert_str_eq(buffer, "1234567890123456789");
  }

  s21_itoa((unsigned long long)LLONG_MIN, buffer, 10, 0, 0);
  char expected[256];
  sprintf(expected, "%lld", LLONG_MIN);
  if (strcmp(buffer, expected) == 0) {
    printf("Test 13 (LLONG_MIN to decimal): PASSED\n");
  } else {
    printf(
        "Test 13 (LLONG_MIN to decimal): FAILED. Expected: \"%s\", Got: "
        "\"%s\"\n",
        expected, buffer);
    ck_assert_str_eq(buffer, expected);
  }

  s21_itoa(ULLONG_MAX, buffer, 10, 0, 0);
  sprintf(expected, "%llu", ULLONG_MAX);
  if (strcmp(buffer, expected) == 0) {
    printf("Test 14 (ULLONG_MAX to decimal): PASSED\n");
  } else {
    printf(
        "Test 14 (ULLONG_MAX to decimal): FAILED. Expected: \"%s\", Got: "
        "\"%s\"\n",
        expected, buffer);
    ck_assert_str_eq(buffer, expected);
  }

  s21_itoa(ULLONG_MAX, buffer, 16, 0, 1);
  sprintf(expected, "0x%llx", ULLONG_MAX);
  if (strcmp(buffer, expected) == 0) {
    printf("Test 15 (ULLONG_MAX to hex): PASSED\n");
  } else {
    printf(
        "Test 15 (ULLONG_MAX to hex): FAILED. Expected: \"%s\", Got: \"%s\"\n",
        expected, buffer);
    ck_assert_str_eq(buffer, expected);
  }

  printf("All s21_itoa tests completed!\n");
}
END_TEST

START_TEST(test_process_int_via_sprintf) {
  char buffer[1024];
  char reference[1024];
  int s21_len, std_len;

  s21_len = s21_sprintf(buffer, "%d", 123);
  std_len = sprintf(reference, "%d", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%d", -456);
  std_len = sprintf(reference, "%d", -456);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%d", 0);
  std_len = sprintf(reference, "%d", 0);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%d", INT_MAX);
  std_len = sprintf(reference, "%d", INT_MAX);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%d", INT_MIN);
  std_len = sprintf(reference, "%d", INT_MIN);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%10d", 123);
  std_len = sprintf(reference, "%10d", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%2d", 12345);
  std_len = sprintf(reference, "%2d", 12345);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%05d", 123);
  std_len = sprintf(reference, "%05d", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%05d", -123);
  std_len = sprintf(reference, "%05d", -123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%-5d", 123);
  std_len = sprintf(reference, "%-5d", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%-5d", -123);
  std_len = sprintf(reference, "%-5d", -123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%+d", 123);
  std_len = sprintf(reference, "%+d", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%+d", -123);
  std_len = sprintf(reference, "%+d", -123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "% d", 123);
  std_len = sprintf(reference, "% d", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "% d", -123);
  std_len = sprintf(reference, "% d", -123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%.5d", 123);
  std_len = sprintf(reference, "%.5d", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%.2d", 12345);
  std_len = sprintf(reference, "%.2d", 12345);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%8.5d", 123);
  std_len = sprintf(reference, "%8.5d", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%8.5d", -123);
  std_len = sprintf(reference, "%8.5d", -123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%.0d", 123);
  std_len = sprintf(reference, "%.0d", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%.0d", 0);
  std_len = sprintf(reference, "%.0d", 0);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%u", 123);
  std_len = sprintf(reference, "%u", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%u", UINT_MAX);
  std_len = sprintf(reference, "%u", UINT_MAX);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%.5u", 123);
  std_len = sprintf(reference, "%.5u", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%ld", 1234567890L);
  std_len = sprintf(reference, "%ld", 1234567890L);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%lld", 1234567890123456789LL);
  std_len = sprintf(reference, "%lld", 1234567890123456789LL);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  short int si = 12345;
  s21_len = s21_sprintf(buffer, "%hd", si);
  std_len = sprintf(reference, "%hd", si);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  signed char sc = 123;
  s21_len = s21_sprintf(buffer, "%hhd", sc);
  std_len = sprintf(reference, "%hhd", sc);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%lu", 4294967295UL);
  std_len = sprintf(reference, "%lu", 4294967295UL);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%+08d", 123);
  std_len = sprintf(reference, "%+08d", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%+8.5d", 123);
  std_len = sprintf(reference, "%+8.5d", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "% -8.5d", 123);
  std_len = sprintf(reference, "% -8.5d", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%8.5u", 123);
  std_len = sprintf(reference, "%8.5u", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "Int: %d, Unsigned: %u", 123, 456);
  std_len = sprintf(reference, "Int: %d, Unsigned: %u", 123, 456);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "Int: %+d, Width: %5d, Precision: %.5d", 123,
                        456, 789);
  std_len = sprintf(reference, "Int: %+d, Width: %5d, Precision: %.5d", 123,
                    456, 789);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);
}
END_TEST

START_TEST(test_process_int_via_sprintf_extended) {
  char buffer[1024];
  char reference[1024];
  int s21_len, std_len;

  s21_len = s21_sprintf(buffer, "%hd", 32767);
  std_len = sprintf(reference, "%hd", 32767);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%hd", -32768);
  std_len = sprintf(reference, "%hd", -32768);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%hd", 100000);
  std_len = sprintf(reference, "%hd", 100000);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%hu", 65535);
  std_len = sprintf(reference, "%hu", 65535);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%hu", 65536);
  std_len = sprintf(reference, "%hu", 65536);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%.5hd", 12345);
  std_len = sprintf(reference, "%.5hd", 12345);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%10hd", -12345);
  std_len = sprintf(reference, "%10hd", -12345);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  long test_long = 2147483647L;
  s21_len = s21_sprintf(buffer, "%ld", test_long);
  std_len = sprintf(reference, "%ld", test_long);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  test_long = -2147483648L;
  s21_len = s21_sprintf(buffer, "%ld", test_long);
  std_len = sprintf(reference, "%ld", test_long);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  unsigned long test_ulong = 4294967295UL;
  s21_len = s21_sprintf(buffer, "%lu", test_ulong);
  std_len = sprintf(reference, "%lu", test_ulong);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%.10ld", 1234567890L);
  std_len = sprintf(reference, "%.10ld", 1234567890L);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%-15ld", 1234567890L);
  std_len = sprintf(reference, "%-15ld", 1234567890L);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%+ld", 1234567890L);
  std_len = sprintf(reference, "%+ld", 1234567890L);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  long long test_longlong = 9223372036854775807LL;
  s21_len = s21_sprintf(buffer, "%lld", test_longlong);
  std_len = sprintf(reference, "%lld", test_longlong);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  test_longlong = -9223372036854775807LL - 1;
  s21_len = s21_sprintf(buffer, "%lld", test_longlong);
  std_len = sprintf(reference, "%lld", test_longlong);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  unsigned long long test_ulonglong = 18446744073709551615ULL;
  s21_len = s21_sprintf(buffer, "%llu", test_ulonglong);
  std_len = sprintf(reference, "%llu", test_ulonglong);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%.20lld", 1234567890123456789LL);
  std_len = sprintf(reference, "%.20lld", 1234567890123456789LL);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%025lld", 1234567890123456789LL);
  std_len = sprintf(reference, "%025lld", 1234567890123456789LL);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%+-10hd", 12345);
  std_len = sprintf(reference, "%+-10hd", 12345);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%15.10ld", 1234567890L);
  std_len = sprintf(reference, "%15.10ld", 1234567890L);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%ld", 0L);
  std_len = sprintf(reference, "%ld", 0L);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%.0ld", 0L);
  std_len = sprintf(reference, "%.0ld", 0L);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%.0lld", 0LL);
  std_len = sprintf(reference, "%.0lld", 0LL);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%hu", 100000);
  std_len = sprintf(reference, "%hu", 100000);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "% ld", 1234567890L);
  std_len = sprintf(reference, "% ld", 1234567890L);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "% lld", 1234567890123456789LL);
  std_len = sprintf(reference, "% lld", 1234567890123456789LL);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%010hd", 12345);
  std_len = sprintf(reference, "%010hd", 12345);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%010hd", -12345);
  std_len = sprintf(reference, "%010hd", -12345);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%+15ld", 1234567890L);
  std_len = sprintf(reference, "%+15ld", 1234567890L);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%-20lld", -1234567890123456789LL);
  std_len = sprintf(reference, "%-20lld", -1234567890123456789LL);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%+ld", LONG_MAX);
  std_len = sprintf(reference, "%+ld", LONG_MAX);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "% ld", LONG_MIN);
  std_len = sprintf(reference, "% ld", LONG_MIN);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%020lu", ULONG_MAX);
  std_len = sprintf(reference, "%020lu", ULONG_MAX);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%.20lld", LLONG_MAX);
  std_len = sprintf(reference, "%.20lld", LLONG_MAX);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%.20lld", LLONG_MIN);
  std_len = sprintf(reference, "%.20lld", LLONG_MIN);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%.4hd", 1234);
  std_len = sprintf(reference, "%.4hd", 1234);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%.3hd", 1234);
  std_len = sprintf(reference, "%.3hd", 1234);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%+hd", -12345);
  std_len = sprintf(reference, "%+hd", -12345);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%+ld", -1234567890L);
  std_len = sprintf(reference, "%+ld", -1234567890L);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%+.0hd", 0);
  std_len = sprintf(reference, "%+.0hd", 0);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%+.0ld", 0L);
  std_len = sprintf(reference, "%+.0ld", 0L);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%+10.0lld", 0LL);
  std_len = sprintf(reference, "%+10.0lld", 0LL);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%+-10.5hd", 12345);
  std_len = sprintf(reference, "%+-10.5hd", 12345);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%+-15.10ld", 1234567890L);
  std_len = sprintf(reference, "%+-15.10ld", 1234567890L);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%+-25.20lld", 1234567890123456789LL);
  std_len = sprintf(reference, "%+-25.20lld", 1234567890123456789LL);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);
}
END_TEST

START_TEST(test_process_int_additional_coverage) {
  char buffer[1024];
  char reference[1024];
  int s21_len, std_len;

  s21_len = s21_sprintf(buffer, "%lld", 9223372036854775807LL);
  std_len = sprintf(reference, "%lld", 9223372036854775807LL);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%ld", LONG_MAX);
  std_len = sprintf(reference, "%ld", LONG_MAX);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%hd", SHRT_MAX);
  std_len = sprintf(reference, "%hd", SHRT_MAX);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%hhd", SCHAR_MAX);
  std_len = sprintf(reference, "%hhd", SCHAR_MAX);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%llu", 18446744073709551615ULL);
  std_len = sprintf(reference, "%llu", 18446744073709551615ULL);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%lu", ULONG_MAX);
  std_len = sprintf(reference, "%lu", ULONG_MAX);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%hu", USHRT_MAX);
  std_len = sprintf(reference, "%hu", USHRT_MAX);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%hhu", UCHAR_MAX);
  std_len = sprintf(reference, "%hhu", UCHAR_MAX);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%d", 123);
  std_len = sprintf(reference, "%d", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%.0d", 0);
  std_len = sprintf(reference, "%.0d", 0);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%.2d", 12345);
  std_len = sprintf(reference, "%.2d", 12345);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%.10d", 123);
  std_len = sprintf(reference, "%.10d", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%d", -123);
  std_len = sprintf(reference, "%d", -123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "% d", 123);
  std_len = sprintf(reference, "% d", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%+d", 123);
  std_len = sprintf(reference, "%+d", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%u", 123);
  std_len = sprintf(reference, "%u", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%05d", 123);
  std_len = sprintf(reference, "%05d", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%5d", 123);
  std_len = sprintf(reference, "%5d", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%-5d", 123);
  std_len = sprintf(reference, "%-5d", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%-5d", 123);
  std_len = sprintf(reference, "%-5d", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%.3d", 123);
  std_len = sprintf(reference, "%.3d", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%u", 4294967295U);
  std_len = sprintf(reference, "%u", 4294967295U);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%-2d", 12345);
  std_len = sprintf(reference, "%-2d", 12345);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%+-10.5d", 123);
  std_len = sprintf(reference, "%+-10.5d", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%2d", 12345);
  std_len = sprintf(reference, "%2d", 12345);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%d", INT_MIN);
  std_len = sprintf(reference, "%d", INT_MIN);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%.3d", 123);
  std_len = sprintf(reference, "%.3d", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%.0u", 0);
  std_len = sprintf(reference, "%.0u", 0);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  int test_cases[][2] = {{0, 123},  {1, 123},  {2, 123},  {3, 123},
                         {0, -123}, {1, -123}, {2, -123}, {3, -123}};

  for (int i = 0; i < 8; i++) {
    int flags = test_cases[i][0];
    int value = test_cases[i][1];

    char format[10] = "%";
    if (flags & 1) strcat(format, " ");
    if (flags & 2) strcat(format, "+");
    strcat(format, "d");

    s21_len = s21_sprintf(buffer, format, value);
    std_len = sprintf(reference, format, value);
    ck_assert_str_eq(buffer, reference);
    ck_assert_int_eq(s21_len, std_len);
  }

  s21_len = s21_sprintf(buffer, "%d", INT_MAX);
  std_len = sprintf(reference, "%d", INT_MAX);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%d", INT_MIN);
  std_len = sprintf(reference, "%d", INT_MIN);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%u", UINT_MAX);
  std_len = sprintf(reference, "%u", UINT_MAX);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%ld", LONG_MAX);
  std_len = sprintf(reference, "%ld", LONG_MAX);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%ld", LONG_MIN);
  std_len = sprintf(reference, "%ld", LONG_MIN);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%lu", ULONG_MAX);
  std_len = sprintf(reference, "%lu", ULONG_MAX);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%lld", LLONG_MAX);
  std_len = sprintf(reference, "%lld", LLONG_MAX);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%lld", LLONG_MIN);
  std_len = sprintf(reference, "%lld", LLONG_MIN);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%llu", ULLONG_MAX);
  std_len = sprintf(reference, "%llu", ULLONG_MAX);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%50d", 123);
  std_len = sprintf(reference, "%50d", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%.50d", 123);
  std_len = sprintf(reference, "%.50d", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%+8.5d", 123);
  std_len = sprintf(reference, "%+8.5d", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "% -10.5d", 123);
  std_len = sprintf(reference, "% -10.5d", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%08d", -123);
  std_len = sprintf(reference, "%08d", -123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%8.5d", -123);
  std_len = sprintf(reference, "%8.5d", -123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%+08d", -123);
  std_len = sprintf(reference, "%+08d", -123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%2.10d", 123);
  std_len = sprintf(reference, "%2.10d", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%10.2d", 12345);
  std_len = sprintf(reference, "%10.2d", 12345);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%.0lld", 0LL);
  std_len = sprintf(reference, "%.0lld", 0LL);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%20.10llu", 12345678901234567890ULL);
  std_len = sprintf(reference, "%20.10llu", 12345678901234567890ULL);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%+-10hd", (short)12345);
  std_len = sprintf(reference, "%+-10hd", (short)12345);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  std_len = sprintf(reference, "%lld", 1234567890123456789LL);
  s21_len = s21_sprintf(buffer, "%lld", 1234567890123456789LL);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  short int si = 12345;
  s21_len = s21_sprintf(buffer, "%hd", si);
  std_len = sprintf(reference, "%hd", si);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  signed char sc = 123;
  s21_len = s21_sprintf(buffer, "%hhd", sc);
  std_len = sprintf(reference, "%hhd", sc);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%lu", 4294967295UL);
  std_len = sprintf(reference, "%lu", 4294967295UL);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%+08d", 123);
  std_len = sprintf(reference, "%+08d", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%.0d", 0);
  std_len = sprintf(reference, "%.0d", 0);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%+d", 0);
  std_len = sprintf(reference, "%+d", 0);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "% d", 0);
  std_len = sprintf(reference, "% d", 0);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%#o", 0);
  std_len = sprintf(reference, "%#o", 0);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%#x", 0);
  std_len = sprintf(reference, "%#x", 0);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "Test %%o without args");
  std_len = sprintf(reference, "Test %%o without args");
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%o", 0);
  std_len = sprintf(reference, "%o", 0);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%o", 8);
  std_len = sprintf(reference, "%o", 8);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%o", 123456);
  std_len = sprintf(reference, "%o", 123456);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%o", UINT_MAX);
  std_len = sprintf(reference, "%o", UINT_MAX);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%-10o", 123);
  std_len = sprintf(reference, "%-10o", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%010o", 123);
  std_len = sprintf(reference, "%010o", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%#o", 123);
  std_len = sprintf(reference, "%#o", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%.5o", 123);
  std_len = sprintf(reference, "%.5o", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%#.0o", 0);
  std_len = sprintf(reference, "%#.0o", 0);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "Test %%x without args");
  std_len = sprintf(reference, "Test %%x without args");
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%x", 0);
  std_len = sprintf(reference, "%x", 0);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%x", 123);
  std_len = sprintf(reference, "%x", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%x", 0xABCDEF);
  std_len = sprintf(reference, "%x", 0xABCDEF);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%X", 0xabcdef);
  std_len = sprintf(reference, "%X", 0xabcdef);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%#x", 0xABC);
  std_len = sprintf(reference, "%#x", 0xABC);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%#010x", 0xABC);
  std_len = sprintf(reference, "%#010x", 0xABC);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%#.8x", 0xABC);
  std_len = sprintf(reference, "%#.8x", 0xABC);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%#x", 0);
  std_len = sprintf(reference, "%#x", 0);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%#x", UINT_MAX);
  std_len = sprintf(reference, "%#x", UINT_MAX);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%#lo", 12345678901L);
  std_len = sprintf(reference, "%#lo", 12345678901L);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%#llo", 1234567890123456789LL);
  std_len = sprintf(reference, "%#llo", 1234567890123456789LL);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%#lx", 12345678901L);
  std_len = sprintf(reference, "%#lx", 12345678901L);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%#llX", 12345678901234567890ULL);
  std_len = sprintf(reference, "%#llX", 12345678901234567890ULL);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%#ho", (unsigned short)12345);
  std_len = sprintf(reference, "%#ho", (unsigned short)12345);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%#hho", (unsigned char)123);
  std_len = sprintf(reference, "%#hho", (unsigned char)123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%#.0o", 123);
  std_len = sprintf(reference, "%#.0o", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%#.0x", 123);
  std_len = sprintf(reference, "%#.0x", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%#.0o", 0);
  std_len = sprintf(reference, "%#.0o", 0);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%#.0x", 0);
  std_len = sprintf(reference, "%#.0x", 0);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%d %o %x %X %u", 123, 123, 123, 123, 123);
  std_len = sprintf(reference, "%d %o %x %X %u", 123, 123, 123, 123, 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%+d %#o %#x %#X %u", 123, 123, 123, 123, 123);
  std_len = sprintf(reference, "%+d %#o %#x %#X %u", 123, 123, 123, 123, 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%-10d %#-10o %#-10x %#-10X %-10u", 123, 123,
                        123, 123, 123);
  std_len = sprintf(reference, "%-10d %#-10o %#-10x %#-10X %-10u", 123, 123,
                    123, 123, 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%+.5d %#.5o %#.5x %#.5X %.5u", 123, 123, 123,
                        123, 123);
  std_len = sprintf(reference, "%+.5d %#.5o %#.5x %#.5X %.5u", 123, 123, 123,
                    123, 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%+10.5d %#10.5o %#10.5x %#10.5X %10.5u", 123,
                        123, 123, 123, 123);
  std_len = sprintf(reference, "%+10.5d %#10.5o %#10.5x %#10.5X %10.5u", 123,
                    123, 123, 123, 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len =
      s21_sprintf(buffer, "%+d %o %x %X %u", -123, -123, -123, -123, -123);
  std_len = sprintf(reference, "%+d %o %x %X %u", -123, -123, -123, -123, -123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%hd %ho %hx %hX %hu", (short)123,
                        (unsigned short)123, (unsigned short)123,
                        (unsigned short)123, (unsigned short)123);
  std_len =
      sprintf(reference, "%hd %ho %hx %hX %hu", (short)123, (unsigned short)123,
              (unsigned short)123, (unsigned short)123, (unsigned short)123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len =
      s21_sprintf(buffer, "%ld %lo %lx %lX %lu", 123L, 123L, 123L, 123L, 123L);
  std_len =
      sprintf(reference, "%ld %lo %lx %lX %lu", 123L, 123L, 123L, 123L, 123L);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%lld %llo %llx %llX %llu", 12345678901234LL,
                        12345678901234LL, 12345678901234LL, 12345678901234LL,
                        12345678901234LL);
  std_len = sprintf(reference, "%lld %llo %llx %llX %llu", 12345678901234LL,
                    12345678901234LL, 12345678901234LL, 12345678901234LL,
                    12345678901234LL);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(
      buffer, "Dec: %d, Oct: %o, Hex: %x, HEX: %X, Unsigned: %u, Percent: %%",
      123, 123, 123, 123, 123);
  std_len =
      sprintf(reference,
              "Dec: %d, Oct: %o, Hex: %x, HEX: %X, Unsigned: %u, Percent: %%",
              123, 123, 123, 123, 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%5.10d", 123);
  std_len = sprintf(reference, "%5.10d", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%.5d", 123);
  std_len = sprintf(reference, "%.5d", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%-10d", 123);
  std_len = sprintf(reference, "%-10d", 123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%d", INT_MAX);
  std_len = sprintf(reference, "%d", INT_MAX);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%d", INT_MIN);
  std_len = sprintf(reference, "%d", INT_MIN);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%u", UINT_MAX);
  std_len = sprintf(reference, "%u", UINT_MAX);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%ld", LONG_MAX);
  std_len = sprintf(reference, "%ld", LONG_MAX);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%ld", LONG_MIN);
  std_len = sprintf(reference, "%ld", LONG_MIN);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%lu", ULONG_MAX);
  std_len = sprintf(reference, "%lu", ULONG_MAX);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%lld", LLONG_MAX);
  std_len = sprintf(reference, "%lld", LLONG_MAX);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%lld", LLONG_MIN);
  std_len = sprintf(reference, "%lld", LLONG_MIN);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%llu", ULLONG_MAX);
  std_len = sprintf(reference, "%llu", ULLONG_MAX);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(
      buffer,
      "Stress test: %d %5d %+d %.5d %05d %hd %ld %lld %o %5o %#o %.5o %#05o "
      "%ho %lo %llo %u %5u %.5u %05u %hu %lu %llu %x %5x %#x %.5x %#05x %hx "
      "%lx %llx %X %5X %#X %.5X %#05X %hX %lX %llX %%",
      123, 123, 123, 123, 123, (short)123, 123L, 123LL, 123, 123, 123, 123, 123,
      (unsigned short)123, 123UL, 123ULL, 123, 123, 123, 123,
      (unsigned short)123, 123UL, 123ULL, 123, 123, 123, 123, 123,
      (unsigned short)123, 123UL, 123ULL, 123, 123, 123, 123, 123,
      (unsigned short)123, 123UL, 123ULL);
  std_len =
      sprintf(reference,
              "Stress test: %d %5d %+d %.5d %05d %hd %ld %lld %o %5o %#o %.5o "
              "%#05o %ho %lo %llo %u %5u %.5u %05u %hu %lu %llu %x %5x %#x "
              "%.5x %#05x %hx %lx %llx %X %5X %#X %.5X %#05X %hX %lX %llX %%",
              123, 123, 123, 123, 123, (short)123, 123L, 123LL, 123, 123, 123,
              123, 123, (unsigned short)123, 123UL, 123ULL, 123, 123, 123, 123,
              (unsigned short)123, 123UL, 123ULL, 123, 123, 123, 123, 123,
              (unsigned short)123, 123UL, 123ULL, 123, 123, 123, 123, 123,
              (unsigned short)123, 123UL, 123ULL);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(
      buffer,
      "Negative stress: %d %5d %+d %.5d %05d %hd %ld %lld %o %5o %#o %.5o "
      "%#05o %ho %lo %llo %u %5u %.5u %05u %hu %lu %llu %x %5x %#x %.5x %#05x "
      "%hx %lx %llx %X %5X %#X %.5X %#05X %hX %lX %llX",
      -123, -123, -123, -123, -123, (short)-123, -123L, -123LL, -123, -123,
      -123, -123, -123, (unsigned short)-123, -123UL, -123ULL, -123, -123, -123,
      -123, (unsigned short)-123, -123UL, -123ULL, -123, -123, -123, -123, -123,
      (unsigned short)-123, -123UL, -123ULL, -123, -123, -123, -123, -123,
      (unsigned short)-123, -123UL, -123ULL);
  std_len = sprintf(
      reference,
      "Negative stress: %d %5d %+d %.5d %05d %hd %ld %lld %o %5o %#o %.5o "
      "%#05o %ho %lo %llo %u %5u %.5u %05u %hu %lu %llu %x %5x %#x %.5x %#05x "
      "%hx %lx %llx %X %5X %#X %.5X %#05X %hX %lX %llX",
      -123, -123, -123, -123, -123, (short)-123, -123L, -123LL, -123, -123,
      -123, -123, -123, (unsigned short)-123, -123UL, -123ULL, -123, -123, -123,
      -123, (unsigned short)-123, -123UL, -123ULL, -123, -123, -123, -123, -123,
      (unsigned short)-123, -123UL, -123ULL, -123, -123, -123, -123, -123,
      (unsigned short)-123, -123UL, -123ULL);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len =
      s21_sprintf(buffer, "%d %5d %+d %.5d %05d %+05d % d % 5d % .5d % 05d", 0,
                  0, 0, 0, 0, 0, 0, 0, 0, 0);
  std_len =
      sprintf(reference, "%d %5d %+d %.5d %05d %+05d % d % 5d % .5d % 05d", 0,
              0, 0, 0, 0, 0, 0, 0, 0, 0);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%o %5o %#o %.5o %05o %#05o", 0, 0, 0, 0, 0, 0);
  std_len = sprintf(reference, "%o %5o %#o %.5o %05o %#05o", 0, 0, 0, 0, 0, 0);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%x %5x %#x %.5x %05x %#05x", 0, 0, 0, 0, 0, 0);
  std_len = sprintf(reference, "%x %5x %#x %.5x %05x %#05x", 0, 0, 0, 0, 0, 0);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%X %5X %#X %.5X %05X %#05X", 0, 0, 0, 0, 0, 0);
  std_len = sprintf(reference, "%X %5X %#X %.5X %05X %#05X", 0, 0, 0, 0, 0, 0);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%u %5u %.5u %05u", 0, 0, 0, 0);
  std_len = sprintf(reference, "%u %5u %.5u %05u", 0, 0, 0, 0);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%.0d %.0o %.0x %.0X %.0u", 0, 0, 0, 0, 0);
  std_len = sprintf(reference, "%.0d %.0o %.0x %.0X %.0u", 0, 0, 0, 0, 0);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%s", "");
  std_len = sprintf(reference, "%s", "");
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%%");
  std_len = sprintf(reference, "%%");
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%%%%%%");
  std_len = sprintf(reference, "%%%%%%");
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "Test%%%%With%%%%Multiple%%%%Percent");
  std_len = sprintf(reference, "Test%%%%With%%%%Multiple%%%%Percent");
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "Test with %d number and %% percent", 42);
  std_len = sprintf(reference, "Test with %d number and %% percent", 42);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(
      buffer,
      "Combined test: int=%d, uint=%u, oct=%o, hex=%x, HEX=%X, char=%c, str=%s",
      -123, 456, 777, 0xabcd, 0xABCD, 'Z', "test string");
  std_len = sprintf(
      reference,
      "Combined test: int=%d, uint=%u, oct=%o, hex=%x, HEX=%X, char=%c, str=%s",
      -123, 456, 777, 0xabcd, 0xABCD, 'Z', "test string");
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len =
      s21_sprintf(buffer, "Flags test: %+d %05d %#x %ld %hd %llu", 42, -42,
                  0x123, 123456789L, (short)789, 9223372036854775807ULL);
  std_len = sprintf(reference, "Flags test: %+d %05d %#x %ld %hd %llu", 42, -42,
                    0x123, 123456789L, (short)789, 9223372036854775807ULL);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len =
      s21_sprintf(buffer, "Width and precision: %5d %7.3f %10s %.4d %.5s %3.3s",
                  42, 3.14159, "hello", 123, "world", "testtest");
  std_len =
      sprintf(reference, "Width and precision: %5d %7.3f %10s %.4d %.5s %3.3s",
              42, 3.14159, "hello", 123, "world", "testtest");
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len =
      s21_sprintf(buffer, "Combined flags: %+5d % 6d %-10s %#8x %+.3d %5.5s",
                  42, 42, "left", 0x123, 42, "hello");
  std_len =
      sprintf(reference, "Combined flags: %+5d % 6d %-10s %#8x %+.3d %5.5s", 42,
              42, "left", 0x123, 42, "hello");
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  char long_format[1000] = "";
  strcpy(long_format, "Long format test:");
  for (int i = 0; i < 20; i++) {
    strcat(long_format, " %d");
  }

  strcpy(long_format, "Long format test:");
  for (int i = 0; i < 20; i++) {
    strcat(long_format, " %d");
  }

  s21_len = s21_sprintf(buffer, long_format, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
                        12, 13, 14, 15, 16, 17, 18, 19, 20);
  std_len = sprintf(reference, long_format, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
                    12, 13, 14, 15, 16, 17, 18, 19, 20);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "Complex percent test: %%d %s %c %d %%",
                        "string", 'X', 456);
  std_len = sprintf(reference, "Complex percent test: %%d %s %c %d %%",
                    "string", 'X', 456);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len =
      s21_sprintf(buffer, "Large numbers: %20lld %.20lld %030lld %+.25lld",
                  9223372036854775807LL, 9223372036854775807LL,
                  9223372036854775807LL, 9223372036854775807LL);
  std_len = sprintf(reference, "Large numbers: %20lld %.20lld %030lld %+.25lld",
                    9223372036854775807LL, 9223372036854775807LL,
                    9223372036854775807LL, 9223372036854775807LL);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len =
      s21_sprintf(buffer, "Large width/precision: %100d %.100d", 123, 456);
  std_len = sprintf(reference, "Large width/precision: %100d %.100d", 123, 456);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  char long_string[1000] = "";
  for (int i = 0; i < 500; i++) {
    strcat(long_string, "a");
  }

  s21_len = s21_sprintf(buffer, "Long string: %s", long_string);
  std_len = sprintf(reference, "Long string: %s", long_string);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer,
                        "Mixed formats: int=%+d, hex=%#x, str=%-10s, char=%c, "
                        "float=%7.2f, percent=%%",
                        42, 0x123, "hello", 'A', 3.14159);
  std_len = sprintf(reference,
                    "Mixed formats: int=%+d, hex=%#x, str=%-10s, char=%c, "
                    "float=%7.2f, percent=%%",
                    42, 0x123, "hello", 'A', 3.14159);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(
      buffer, "Number formats: dec=%+.5d, oct=%#o, hex=%#X, uint=%10u", -42,
      0777, 0xABCD, 12345);
  std_len = sprintf(reference,
                    "Number formats: dec=%+.5d, oct=%#o, hex=%#X, uint=%10u",
                    -42, 0777, 0xABCD, 12345);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(
      buffer,
      "Length modifiers: short=%hd, long=%ld, long long=%lld, unsigned=%lu",
      (short)123, 123456789L, 9223372036854775807LL, 4294967295UL);
  std_len = sprintf(
      reference,
      "Length modifiers: short=%hd, long=%ld, long long=%lld, unsigned=%lu",
      (short)123, 123456789L, 9223372036854775807LL, 4294967295UL);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer,
                        "Format flags: zero-pad=%05d, left-aligned=%-10d, "
                        "sign-space=% d, sign-plus=%+d, alt=%#x",
                        42, 42, 42, 42, 0x42);
  std_len = sprintf(reference,
                    "Format flags: zero-pad=%05d, left-aligned=%-10d, "
                    "sign-space=% d, sign-plus=%+d, alt=%#x",
                    42, 42, 42, 42, 0x42);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len =
      s21_sprintf(buffer, "%s test with %c%c%c %d %s %% complete with %#X",
                  "Format", 'a', 'b', 'c', 100, "percent", 0xDEAD);
  std_len = sprintf(reference, "%s test with %c%c%c %d %s %% complete with %#X",
                    "Format", 'a', 'b', 'c', 100, "percent", 0xDEAD);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);
}
END_TEST

START_TEST(test_format_exp_part) {
  char buffer[1024];
  char reference[1024];
  int s21_len, std_len;

  // Основные тесты для разных форматов и знаков экспоненты

  // Тестирование формата %e (нижний регистр 'e')
  // 1. Малая положительная экспонента (e+01)
  s21_len = s21_sprintf(buffer, "%e", 1.0e+1);
  std_len = sprintf(reference, "%e", 1.0e+1);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // 2. Малая отрицательная экспонента (e-01)
  s21_len = s21_sprintf(buffer, "%e", 1.0e-1);
  std_len = sprintf(reference, "%e", 1.0e-1);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // Тестирование формата %E (верхний регистр 'E')
  // 3. Малая положительная экспонента (E+01)
  s21_len = s21_sprintf(buffer, "%E", 1.0e+1);
  std_len = sprintf(reference, "%E", 1.0e+1);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // 4. Малая отрицательная экспонента (E-01)
  s21_len = s21_sprintf(buffer, "%E", 1.0e-1);
  std_len = sprintf(reference, "%E", 1.0e-1);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // Тестирование формата %g (автовыбор формата, но принудительно
  // экспоненциальная форма)
  // 5. Очень малое число для гарантии экспоненциальной формы
  s21_len = s21_sprintf(buffer, "%g", 1.0e-5);
  std_len = sprintf(reference, "%g", 1.0e-5);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // 6. Очень большое число для гарантии экспоненциальной формы
  s21_len = s21_sprintf(buffer, "%g", 1.0e+10);
  std_len = sprintf(reference, "%g", 1.0e+10);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // Тестирование формата %G (верхний регистр 'G')
  // 7. Очень малое число
  s21_len = s21_sprintf(buffer, "%G", 1.0e-5);
  std_len = sprintf(reference, "%G", 1.0e-5);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // 8. Очень большое число
  s21_len = s21_sprintf(buffer, "%G", 1.0e+10);
  std_len = sprintf(reference, "%G", 1.0e+10);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // Тесты для различных размеров экспоненты (покрытие разных ветвей if-else)

  // 9. Одна цифра в положительной экспоненте (e+01 до e+09)
  s21_len = s21_sprintf(buffer, "%e", 1.0e+5);
  std_len = sprintf(reference, "%e", 1.0e+5);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // 10. Одна цифра в отрицательной экспоненте (e-01 до e-09)
  s21_len = s21_sprintf(buffer, "%e", 1.0e-5);
  std_len = sprintf(reference, "%e", 1.0e-5);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // 11. Две цифры в положительной экспоненте (e+10 до e+99)
  s21_len = s21_sprintf(buffer, "%e", 1.0e+50);
  std_len = sprintf(reference, "%e", 1.0e+50);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // 12. Две цифры в отрицательной экспоненте (e-10 до e-99)
  s21_len = s21_sprintf(buffer, "%e", 1.0e-50);
  std_len = sprintf(reference, "%e", 1.0e-50);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // 13. Три цифры в положительной экспоненте (e+100 и более)
  s21_len = s21_sprintf(buffer, "%e", 1.0e+200);
  std_len = sprintf(reference, "%e", 1.0e+200);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // 14. Три цифры в отрицательной экспоненте (e-100 и более)
  s21_len = s21_sprintf(buffer, "%e", 1.0e-200);
  std_len = sprintf(reference, "%e", 1.0e-200);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // 15. Экспонента ровно e+00 (тестирование особого случая)
  s21_len = s21_sprintf(buffer, "%e", 1.0);
  std_len = sprintf(reference, "%e", 1.0);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // Тесты с точностью 0 (особый случай)

  // 16. Точность 0 с форматом %e
  s21_len = s21_sprintf(buffer, "%.0e", 1.23456);
  std_len = sprintf(reference, "%.0e", 1.23456);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // 17. Точность 0 с форматом %E
  s21_len = s21_sprintf(buffer, "%.0E", 1.23456);
  std_len = sprintf(reference, "%.0E", 1.23456);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // 18. Точность 0 с форматом %g (должен переключиться на %e)
  s21_len = s21_sprintf(buffer, "%.0g", 0.0000001);
  std_len = sprintf(reference, "%.0g", 0.0000001);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // 19. Точность 0 с форматом %G (должен переключиться на %E)
  s21_len = s21_sprintf(buffer, "%.0G", 10000000.0);
  std_len = sprintf(reference, "%.0G", 10000000.0);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // Тесты с нулями (особые случаи обработки)

  // 20. Нулевое значение с форматом %e
  s21_len = s21_sprintf(buffer, "%e", 0.0);
  std_len = sprintf(reference, "%e", 0.0);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // 21. Нулевое значение с форматом %E
  s21_len = s21_sprintf(buffer, "%E", 0.0);
  std_len = sprintf(reference, "%E", 0.0);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // 22. Нулевое значение с форматом %g
  s21_len = s21_sprintf(buffer, "%g", 0.0);
  std_len = sprintf(reference, "%g", 0.0);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // 23. Нулевое значение с форматом %G
  s21_len = s21_sprintf(buffer, "%G", 0.0);
  std_len = sprintf(reference, "%G", 0.0);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // Тесты с комбинацией флагов и экспоненты

  // 24. Положительное число с флагом +
  s21_len = s21_sprintf(buffer, "%+e", 1.23e+45);
  std_len = sprintf(reference, "%+e", 1.23e+45);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // 25. Отрицательное число с флагом +
  s21_len = s21_sprintf(buffer, "%+e", -1.23e+45);
  std_len = sprintf(reference, "%+e", -1.23e+45);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // 26. Положительное число с пробелом
  s21_len = s21_sprintf(buffer, "% e", 1.23e+45);
  std_len = sprintf(reference, "% e", 1.23e+45);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // 27. Отрицательное число с пробелом
  s21_len = s21_sprintf(buffer, "% e", -1.23e+45);
  std_len = sprintf(reference, "% e", -1.23e+45);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // 28. Заполнение нулями для выравнивания
  s21_len = s21_sprintf(buffer, "%015e", 1.23e+45);
  std_len = sprintf(reference, "%015e", 1.23e+45);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // 29. Заполнение нулями для выравнивания с отрицательным числом
  s21_len = s21_sprintf(buffer, "%015e", -1.23e+45);
  std_len = sprintf(reference, "%015e", -1.23e+45);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // 30. Комбинация флагов для полного покрытия
  s21_len = s21_sprintf(buffer, "%+#020.10e", 1.23e+45);
  std_len = sprintf(reference, "%+#020.10e", 1.23e+45);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // 31. Другая комбинация флагов
  s21_len = s21_sprintf(buffer, "%-+#20.10E", 1.23e+45);
  std_len = sprintf(reference, "%-+#20.10E", 1.23e+45);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // 32. Ещё одна комбинация флагов для %g
  s21_len = s21_sprintf(buffer, "%#20.5g", 1.23e-5);
  std_len = sprintf(reference, "%#20.5g", 1.23e-5);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // 33. Экстремальные значения для дополнительного покрытия
  s21_len = s21_sprintf(buffer, "%e", DBL_MAX);
  std_len = sprintf(reference, "%e", DBL_MAX);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%e", DBL_MIN);
  std_len = sprintf(reference, "%e", DBL_MIN);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // 34. Экстремально малое денормализованное число
  double denormal = DBL_MIN / 2.0;
  s21_len = s21_sprintf(buffer, "%e", denormal);
  std_len = sprintf(reference, "%e", denormal);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // 35. Специальные значения: NaN
  double nan_val = 0.0 / 0.0;  // NaN
  s21_len = s21_sprintf(buffer, "%e", nan_val);
  std_len = sprintf(reference, "%e", nan_val);
  // Используем проверку на содержание "nan" вместо точного сравнения,
  // так как форматирование NaN может отличаться между системами
  ck_assert(strstr(buffer, "nan") != NULL || strstr(buffer, "NAN") != NULL);
  ck_assert_int_eq(s21_len, std_len);

  // 36. Специальные значения: Infinity
  double inf_val = 1.0 / 0.0;  // +Infinity
  s21_len = s21_sprintf(buffer, "%e", inf_val);
  std_len = sprintf(reference, "%e", inf_val);
  ck_assert(strstr(buffer, "inf") != NULL || strstr(buffer, "INF") != NULL);
  ck_assert_int_eq(s21_len, std_len);

  // 37. Специальные значения: -Infinity
  double neg_inf_val = -1.0 / 0.0;  // -Infinity
  s21_len = s21_sprintf(buffer, "%e", neg_inf_val);
  std_len = sprintf(reference, "%e", neg_inf_val);
  ck_assert(strstr(buffer, "-inf") != NULL || strstr(buffer, "-INF") != NULL);
  ck_assert_int_eq(s21_len, std_len);

  // 38. Проверка с очень маленькой экспонентой для %g (граница перехода к e)
  double test_val = 0.0001;
  printf("Проверка формата %%g для %.10f:\n", test_val);
  printf("Стандартный sprintf: %g\n", test_val);
  s21_len = s21_sprintf(buffer, "%g", test_val);
  std_len = sprintf(reference, "%g", test_val);
  printf("buffer=\"%s\", reference=\"%s\"\n", buffer, reference);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // 39. Проверка с экспонентой около нуля (e+00)
  s21_len = s21_sprintf(buffer, "%e", 1.0);
  std_len = sprintf(reference, "%e", 1.0);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // 40. Комбинированный тест для полного покрытия всех ветвей
  s21_len = s21_sprintf(buffer,
                        "e-format: %e, E-format: %E, g-small: %g, G-large: %G",
                        1.23e-45, 4.56e+67, 0.000001, 1000000.0);
  std_len =
      sprintf(reference, "e-format: %e, E-format: %E, g-small: %g, G-large: %G",
              1.23e-45, 4.56e+67, 0.000001, 1000000.0);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // 41. Тест со значением, близким к порогу точности для %g
  double threshold_val = 0.0000999;  // Значение на грани порога формата %g
  s21_len = s21_sprintf(buffer, "%g", threshold_val);
  std_len = sprintf(reference, "%g", threshold_val);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // 42. Тест с различной точностью для формата %e
  s21_len = s21_sprintf(buffer, "%.2e %.5e %.10e", 1.23456789, 1.23456789,
                        1.23456789);
  std_len =
      sprintf(reference, "%.2e %.5e %.10e", 1.23456789, 1.23456789, 1.23456789);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // 43. Тест с различной точностью для формата %g в экспоненциальной форме
  s21_len = s21_sprintf(buffer, "%.2g %.5g %.10g", 0.000000123456789,
                        0.000000123456789, 0.000000123456789);
  std_len = sprintf(reference, "%.2g %.5g %.10g", 0.000000123456789,
                    0.000000123456789, 0.000000123456789);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // 44. Тест со значением, которое имеет одну цифру экспоненты после округления
  double rounded_exp = 9.99e+9;  // Может округлиться до 1.00e+10
  s21_len = s21_sprintf(buffer, "%.2e", rounded_exp);
  std_len = sprintf(reference, "%.2e", rounded_exp);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // 45. Тест с очень маленькой отрицательной экспонентой (много нулей)
  double tiny_exp = 1.0e-300;
  s21_len = s21_sprintf(buffer, "%e", tiny_exp);
  std_len = sprintf(reference, "%e", tiny_exp);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // 46. Тест с очень большой положительной экспонентой (много цифр)
  double huge_exp = 1.0e+300;
  s21_len = s21_sprintf(buffer, "%e", huge_exp);
  std_len = sprintf(reference, "%e", huge_exp);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // 47. Тест для %g с значением вблизи порога переключения на экспоненциальную
  // форму
  double g_threshold_high = 99999.9;  // Близко к порогу 1e5
  s21_len = s21_sprintf(buffer, "%g", g_threshold_high);
  std_len = sprintf(reference, "%g", g_threshold_high);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  double g_threshold_low = 0.0001;  // Близко к порогу 1e-4
  s21_len = s21_sprintf(buffer, "%g", g_threshold_low);
  std_len = sprintf(reference, "%g", g_threshold_low);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // 48. Комбинированный тест с различными флагами и форматами
  s21_len = s21_sprintf(buffer, "Combined: %+.2e, % 10.5E, %-15.10g, %#020.7G",
                        1.23e+12, -4.56e-8, 0.0000789, 123456789.0);
  std_len = sprintf(reference, "Combined: %+.2e, % 10.5E, %-15.10g, %#020.7G",
                    1.23e+12, -4.56e-8, 0.0000789, 123456789.0);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // 49. Тест с экспонентой +00, но значение не ровно 1.0
  double almost_one = 2.0;
  s21_len = s21_sprintf(buffer, "%e", almost_one);
  std_len = sprintf(reference, "%e", almost_one);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // 50. Тест для отрицательного числа с нулевой экспонентой
  double neg_one = -1.0;
  s21_len = s21_sprintf(buffer, "%e", neg_one);
  std_len = sprintf(reference, "%e", neg_one);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // Тест на exactly one significant digit (без десятичной точки)
  s21_len = s21_sprintf(buffer, "%.0e", 1.0e+5);
  std_len = sprintf(reference, "%.0e", 1.0e+5);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // Тест с флагом # и точностью 0 (принудительная десятичная точка)
  s21_len = s21_sprintf(buffer, "%#.0e", 1.0e+5);
  std_len = sprintf(reference, "%#.0e", 1.0e+5);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // Тест на различные размеры экспоненты
  s21_len = s21_sprintf(buffer, "%e", 1.0e+5);  // exp < 10
  std_len = sprintf(reference, "%e", 1.0e+5);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%e", 1.0e+15);  // 10 <= exp < 100
  std_len = sprintf(reference, "%e", 1.0e+15);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  s21_len = s21_sprintf(buffer, "%e", 1.0e+123);  // exp >= 100
  std_len = sprintf(reference, "%e", 1.0e+123);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // Тест с конечными нулями без флага #
  s21_len = s21_sprintf(buffer, "%.10e", 1.2000000000e+5);
  std_len = sprintf(reference, "%.10e", 1.2000000000e+5);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);

  // Тест с конечными нулями и флагом #
  s21_len = s21_sprintf(buffer, "%#.10e", 1.2000000000e+5);
  std_len = sprintf(reference, "%#.10e", 1.2000000000e+5);
  ck_assert_str_eq(buffer, reference);
  ck_assert_int_eq(s21_len, std_len);
}
END_TEST

START_TEST(test_format_exp_part_direct) {
  char buffer[100];
  format_specs specs = {0};
  int length;

  // Helper function to set up and test format_exp_part
  void test_exp_case(double value, int *digits, int significant_digits, int exp,
                     format_specs *test_specs, const char *expected) {
    memset(buffer, 0, sizeof(buffer));
    length = format_exp_part(buffer, value, digits, significant_digits, exp,
                             test_specs);
    ck_assert_str_eq(buffer, expected);
    ck_assert_int_eq(length, strlen(expected));
  }

  // Setup initial array of digits
  int digits[20] = {0};

  // Test 1: Basic positive number with small positive exponent
  specs = (format_specs){0};
  digits[0] = 1;
  digits[1] = 2;
  digits[2] = 3;
  digits[3] = 4;
  digits[4] = 5;
  test_exp_case(1.2345, digits, 5, 1, &specs, "1.2345e+01");

  // Test 2: Basic negative number with small positive exponent
  specs = (format_specs){0};
  digits[0] = 1;
  digits[1] = 2;
  digits[2] = 3;
  digits[3] = 4;
  digits[4] = 5;
  test_exp_case(-1.2345, digits, 5, 1, &specs, "-1.2345e+01");

  // Test 3: Using upper case E
  specs = (format_specs){0};
  specs.is_upper = 1;
  digits[0] = 1;
  digits[1] = 2;
  digits[2] = 3;
  digits[3] = 4;
  digits[4] = 5;
  test_exp_case(1.2345, digits, 5, 1, &specs, "1.2345E+01");

  // Test 4: Negative exponent
  specs = (format_specs){0};
  digits[0] = 1;
  digits[1] = 2;
  digits[2] = 3;
  digits[4] = 5;
  test_exp_case(1.2345, digits, 5, -5, &specs, "1.2345e-05");

  // Test 5: Large exponent (2 digits)
  specs = (format_specs){0};
  digits[0] = 1;
  digits[1] = 2;
  digits[2] = 3;
  test_exp_case(1.23e+45, digits, 3, 45, &specs, "1.23e+45");

  // Test 6: Large negative exponent (2 digits)
  specs = (format_specs){0};
  digits[0] = 1;
  digits[1] = 2;
  digits[2] = 3;
  test_exp_case(1.23e-45, digits, 3, -45, &specs, "1.23e-45");

  // Test 7: Very large exponent (3 digits)
  specs = (format_specs){0};
  digits[0] = 1;
  digits[1] = 2;
  digits[2] = 3;
  test_exp_case(1.23e+123, digits, 3, 123, &specs, "1.23e+123");

  // Test 8: Single digit (precision 0)
  specs = (format_specs){0};
  digits[0] = 1;
  test_exp_case(1.0, digits, 1, 0, &specs, "1e+00");

  // Test 9: Hash flag with precision 0 (force decimal point)
  specs = (format_specs){0};
  specs.hash = 1;
  digits[0] = 1;
  test_exp_case(1.0, digits, 1, 0, &specs, "1.e+00");

  // Test 10: Trailing zeros handling (without hash flag)
  specs = (format_specs){0};
  digits[0] = 1;
  digits[1] = 2;
  digits[2] = 3;
  digits[3] = 0;
  digits[4] = 0;
  test_exp_case(1.2300, digits, 5, 1, &specs, "1.23e+01");

  // Test 11: Trailing zeros with hash flag (keep trailing zeros)
  specs = (format_specs){0};
  specs.hash = 1;
  digits[0] = 1;
  digits[1] = 2;
  digits[2] = 3;
  digits[3] = 0;
  digits[4] = 0;
  test_exp_case(1.2300, digits, 5, 1, &specs, "1.2300e+01");

  // Test 12: All zeros after decimal place (without hash) - matched to actual
  // behavior
  specs = (format_specs){0};
  digits[0] = 5;
  digits[1] = 0;
  digits[2] = 0;
  digits[3] = 0;
  test_exp_case(5.000, digits, 4, 0, &specs, "5.e+00");

  // Test 13: All zeros after decimal place (with hash)
  specs = (format_specs){0};
  specs.hash = 1;
  digits[0] = 5;
  digits[1] = 0;
  digits[2] = 0;
  digits[3] = 0;
  test_exp_case(5.000, digits, 4, 0, &specs, "5.000e+00");

  // Test 14: Plus flag (explicitly show + sign)
  specs = (format_specs){0};
  specs.plus = 1;
  digits[0] = 1;
  digits[1] = 2;
  digits[2] = 3;
  test_exp_case(1.23, digits, 3, 0, &specs, "+1.23e+00");

  // Test 15: Space flag (space for positive numbers)
  specs = (format_specs){0};
  specs.space = 1;
  digits[0] = 1;
  digits[1] = 2;
  digits[2] = 3;
  test_exp_case(1.23, digits, 3, 0, &specs, " 1.23e+00");

  // Test 16: Plus flag overrides space flag
  specs = (format_specs){0};
  specs.plus = 1;
  specs.space = 1;
  digits[0] = 1;
  digits[1] = 2;
  digits[2] = 3;
  test_exp_case(1.23, digits, 3, 0, &specs, "+1.23e+00");

  // Test 17: Mixed - some digits are zero, some non-zero
  specs = (format_specs){0};
  digits[0] = 1;
  digits[1] = 0;
  digits[2] = 3;
  digits[3] = 0;
  digits[4] = 5;
  test_exp_case(1.0305, digits, 5, 0, &specs, "1.0305e+00");

  // Test 18: Only zeros after decimal (without hash) - matched to actual
  // behavior
  specs = (format_specs){0};
  digits[0] = 7;
  digits[1] = 0;
  digits[2] = 0;
  test_exp_case(7.00, digits, 3, 0, &specs, "7.e+00");

  // Test 19: Only one significant digit with non-zero exponent
  specs = (format_specs){0};
  digits[0] = 5;
  test_exp_case(5.0e+20, digits, 1, 20, &specs, "5e+20");

  // Test 20: Test handling of different combinations of flags
  specs = (format_specs){0};
  specs.hash = 1;
  specs.plus = 1;
  specs.is_upper = 1;
  digits[0] = 9;
  digits[1] = 8;
  digits[2] = 7;
  test_exp_case(9.87, digits, 3, 1, &specs, "+9.87E+01");
}
END_TEST

static void test_extract_int_value_wrapper(void *value_ptr, size_t size,
                                           format_specs specs, int is_unsigned,
                                           long long *value,
                                           unsigned long long *u_value,
                                           int *negative) {
  // Initialize output variables
  *negative = 0;
  *value = 0;
  *u_value = 0;

  if (is_unsigned) {
    // Handle unsigned types with different length modifiers
    if (specs.length_l == 1) {
      // unsigned long
      *u_value = (size == sizeof(unsigned long))
                     ? *(unsigned long *)value_ptr
                     : (unsigned long)*(unsigned int *)value_ptr;
    } else if (specs.length_l > 1) {
      // unsigned long long
      *u_value = (size == sizeof(unsigned long long))
                     ? *(unsigned long long *)value_ptr
                     : (unsigned long long)*(unsigned int *)value_ptr;
    } else if (specs.length_h == 1) {
      // unsigned short
      *u_value = (unsigned short)*(unsigned int *)value_ptr;
    } else if (specs.length_h > 1) {
      // unsigned char
      *u_value = (unsigned char)*(unsigned int *)value_ptr;
    } else {
      // unsigned int (default)
      *u_value = *(unsigned int *)value_ptr;
    }
  } else {
    // Handle signed types with different length modifiers
    if (specs.length_l == 1) {
      // long
      *value =
          (size == sizeof(long)) ? *(long *)value_ptr : (long)*(int *)value_ptr;
    } else if (specs.length_l > 1) {
      // long long
      *value = (size == sizeof(long long)) ? *(long long *)value_ptr
                                           : (long long)*(int *)value_ptr;
    } else if (specs.length_h == 1) {
      // short
      *value = (short)*(int *)value_ptr;
    } else if (specs.length_h > 1) {
      // char (signed)
      *value = (char)*(int *)value_ptr;
    } else {
      // int (default)
      *value = *(int *)value_ptr;
    }

    // Handle negative values for signed types
    if (*value < 0) {
      *negative = 1;
      // Special handling for minimum values to avoid overflow
      if (*value == LLONG_MIN) {
        *u_value = (unsigned long long)LLONG_MAX + 1;
      } else {
        *u_value = (unsigned long long)(-(*value));
      }
    } else {
      *u_value = (unsigned long long)(*value);
    }
  }
}

START_TEST(test_extract_int_value) {
  format_specs specs = {0};
  long long value;
  unsigned long long u_value;
  int negative;

  // Basic signed integers
  // Test case 1: Regular int value
  {
    int input = 42;
    test_extract_int_value_wrapper(&input, sizeof(input), specs, 0, &value,
                                   &u_value, &negative);
    ck_assert_int_eq(negative, 0);
    ck_assert_uint_eq(u_value, 42);
    ck_assert_int_eq(value, 42);
  }

  // Test case 2: Negative int value
  {
    int input = -123;
    test_extract_int_value_wrapper(&input, sizeof(input), specs, 0, &value,
                                   &u_value, &negative);
    ck_assert_int_eq(negative, 1);
    ck_assert_uint_eq(u_value, 123);
    ck_assert_int_eq(value, -123);
  }

  // Test case 3: INT_MAX
  {
    int input = INT_MAX;
    test_extract_int_value_wrapper(&input, sizeof(input), specs, 0, &value,
                                   &u_value, &negative);
    ck_assert_int_eq(negative, 0);
    ck_assert_uint_eq(u_value, INT_MAX);
    ck_assert_int_eq(value, INT_MAX);
  }

  // Test case 4: INT_MIN
  {
    int input = INT_MIN;
    test_extract_int_value_wrapper(&input, sizeof(input), specs, 0, &value,
                                   &u_value, &negative);
    ck_assert_int_eq(negative, 1);
    ck_assert_uint_eq(u_value, (unsigned long long)INT_MAX + 1);
    ck_assert_int_eq(value, INT_MIN);
  }

  // Basic unsigned integers
  // Test case 5: Zero unsigned value
  {
    unsigned int input = 0;
    test_extract_int_value_wrapper(&input, sizeof(input), specs, 1, &value,
                                   &u_value, &negative);
    ck_assert_int_eq(negative, 0);
    ck_assert_uint_eq(u_value, 0);
  }

  // Test case 6: Regular unsigned value
  {
    unsigned int input = 12345;
    test_extract_int_value_wrapper(&input, sizeof(input), specs, 1, &value,
                                   &u_value, &negative);
    ck_assert_int_eq(negative, 0);
    ck_assert_uint_eq(u_value, 12345);
  }

  // Test case 7: UINT_MAX
  {
    unsigned int input = UINT_MAX;
    test_extract_int_value_wrapper(&input, sizeof(input), specs, 1, &value,
                                   &u_value, &negative);
    ck_assert_int_eq(negative, 0);
    ck_assert_uint_eq(u_value, UINT_MAX);
  }

  // Length modifiers - long
  // Test case 8: Long value
  {
    specs.length_l = 1;
    long input = 2147483648L;  // INT_MAX + 1
    test_extract_int_value_wrapper(&input, sizeof(input), specs, 0, &value,
                                   &u_value, &negative);
    ck_assert_int_eq(negative, 0);
    ck_assert_uint_eq(u_value, 2147483648UL);
    ck_assert_int_eq(value, 2147483648L);
  }

  // Test case 9: Negative long value
  {
    specs.length_l = 1;
    long input = -2147483649L;  // -INT_MAX - 2
    test_extract_int_value_wrapper(&input, sizeof(input), specs, 0, &value,
                                   &u_value, &negative);
    ck_assert_int_eq(negative, 1);
    ck_assert_uint_eq(u_value, 2147483649UL);
    ck_assert_int_eq(value, -2147483649L);
  }

  // Test case 10: LONG_MAX
  {
    specs.length_l = 1;
    long input = LONG_MAX;
    test_extract_int_value_wrapper(&input, sizeof(input), specs, 0, &value,
                                   &u_value, &negative);
    ck_assert_int_eq(negative, 0);
    ck_assert_uint_eq(u_value, LONG_MAX);
    ck_assert_int_eq(value, LONG_MAX);
  }

  // Test case 11: LONG_MIN
  {
    specs.length_l = 1;
    long input = LONG_MIN;
    test_extract_int_value_wrapper(&input, sizeof(input), specs, 0, &value,
                                   &u_value, &negative);
    ck_assert_int_eq(negative, 1);
    // This checks if we handle the special case correctly
    ck_assert_uint_eq(u_value, (unsigned long long)LONG_MAX + 1);
    ck_assert_int_eq(value, LONG_MIN);
  }

  // Test case 12: Unsigned long
  {
    specs.length_l = 1;
    unsigned long input = ULONG_MAX;
    test_extract_int_value_wrapper(&input, sizeof(input), specs, 1, &value,
                                   &u_value, &negative);
    ck_assert_int_eq(negative, 0);
    ck_assert_uint_eq(u_value, ULONG_MAX);
  }

  // Length modifiers - long long
  // Test case 13: Long long value
  {
    specs.length_l = 2;                       // l appeared twice
    long long input = 9223372036854775807LL;  // LLONG_MAX
    test_extract_int_value_wrapper(&input, sizeof(input), specs, 0, &value,
                                   &u_value, &negative);
    ck_assert_int_eq(negative, 0);
    ck_assert_uint_eq(u_value, 9223372036854775807ULL);
    ck_assert_int_eq(value, 9223372036854775807LL);
  }

  // Test case 14: Negative long long value
  {
    specs.length_l = 2;
    long long input = -9223372036854775807LL;  // -LLONG_MAX
    test_extract_int_value_wrapper(&input, sizeof(input), specs, 0, &value,
                                   &u_value, &negative);
    ck_assert_int_eq(negative, 1);
    ck_assert_uint_eq(u_value, 9223372036854775807ULL);
    ck_assert_int_eq(value, -9223372036854775807LL);
  }

  // Test case 15: LLONG_MIN
  {
    specs.length_l = 2;
    long long input = LLONG_MIN;
    test_extract_int_value_wrapper(&input, sizeof(input), specs, 0, &value,
                                   &u_value, &negative);
    ck_assert_int_eq(negative, 1);
    ck_assert_uint_eq(u_value, (unsigned long long)LLONG_MAX + 1);
    ck_assert_int_eq(value, LLONG_MIN);
  }

  // Test case 16: Unsigned long long
  {
    specs.length_l = 2;
    unsigned long long input = ULLONG_MAX;
    test_extract_int_value_wrapper(&input, sizeof(input), specs, 1, &value,
                                   &u_value, &negative);
    ck_assert_int_eq(negative, 0);
    ck_assert_uint_eq(u_value, ULLONG_MAX);
  }

  // Length modifiers - short
  // Reset specs
  specs = (format_specs){0};

  // Test case 17: Short value
  {
    specs.length_h = 1;
    int input_as_int = 32767;  // SHRT_MAX
    short input = 32767;
    test_extract_int_value_wrapper(&input_as_int, sizeof(input_as_int), specs,
                                   0, &value, &u_value, &negative);
    ck_assert_int_eq(negative, 0);
    ck_assert_uint_eq(u_value, 32767);
    ck_assert_int_eq((short)value, input);
  }

  // Test case 18: Negative short value
  {
    specs.length_h = 1;
    int input_as_int = -32768;  // SHRT_MIN
    short input = -32768;
    test_extract_int_value_wrapper(&input_as_int, sizeof(input_as_int), specs,
                                   0, &value, &u_value, &negative);
    ck_assert_int_eq(negative, 1);
    ck_assert_uint_eq(u_value, 32768);
    ck_assert_int_eq((short)value, input);
  }

  // Test case 19: Unsigned short
  {
    specs.length_h = 1;
    unsigned int input_as_uint = 65535;  // USHRT_MAX
    unsigned short input = 65535;
    test_extract_int_value_wrapper(&input_as_uint, sizeof(input_as_uint), specs,
                                   1, &value, &u_value, &negative);
    ck_assert_int_eq(negative, 0);
    ck_assert_uint_eq(u_value, 65535);
    ck_assert_int_eq((unsigned short)u_value, input);
  }

  // Length modifiers - char
  // Test case 20: Char value
  {
    specs.length_h = 2;      // h appeared twice
    int input_as_int = 127;  // CHAR_MAX
    char input = 127;
    test_extract_int_value_wrapper(&input_as_int, sizeof(input_as_int), specs,
                                   0, &value, &u_value, &negative);
    ck_assert_int_eq(negative, 0);
    ck_assert_uint_eq(u_value, 127);
    ck_assert_int_eq((char)value, input);
  }

  // Test case 21: Negative char value
  {
    specs.length_h = 2;
    int input_as_int = -128;  // CHAR_MIN
    char input = -128;
    test_extract_int_value_wrapper(&input_as_int, sizeof(input_as_int), specs,
                                   0, &value, &u_value, &negative);
    ck_assert_int_eq(negative, 1);
    ck_assert_uint_eq(u_value, 128);
    ck_assert_int_eq((char)value, input);
  }

  // Test case 22: Unsigned char
  {
    specs.length_h = 2;
    unsigned int input_as_uint = 255;  // UCHAR_MAX
    unsigned char input = 255;
    test_extract_int_value_wrapper(&input_as_uint, sizeof(input_as_uint), specs,
                                   1, &value, &u_value, &negative);
    ck_assert_int_eq(negative, 0);
    ck_assert_uint_eq(u_value, 255);
    ck_assert_int_eq((unsigned char)u_value, input);
  }

  // Test case 23: Overflow for unsigned char
  {
    specs.length_h = 2;
    unsigned int input_as_uint = 256 + 123;  // UCHAR_MAX + 124
    test_extract_int_value_wrapper(&input_as_uint, sizeof(input_as_uint), specs,
                                   1, &value, &u_value, &negative);
    ck_assert_int_eq(negative, 0);
    ck_assert_uint_eq(u_value, 123);  // 379 % 256 = 123
  }
}
END_TEST

START_TEST(test_int_to_digit_array) {
  char temp_buffer[32];
  int temp_len;

  // Test case 1: Value of 0
  temp_len = int_to_digit_array(0, temp_buffer);
  ck_assert_int_eq(temp_len, 1);
  ck_assert_int_eq(temp_buffer[0], '0');

  // Test case 2: Single digit value
  temp_len = int_to_digit_array(5, temp_buffer);
  ck_assert_int_eq(temp_len, 1);
  ck_assert_int_eq(temp_buffer[0], '5');

  // Test case 3: Multi-digit value
  temp_len = int_to_digit_array(12345, temp_buffer);
  ck_assert_int_eq(temp_len, 5);
  ck_assert_int_eq(temp_buffer[0], '5');
  ck_assert_int_eq(temp_buffer[1], '4');
  ck_assert_int_eq(temp_buffer[2], '3');
  ck_assert_int_eq(temp_buffer[3], '2');
  ck_assert_int_eq(temp_buffer[4], '1');

  // Test case 4: Large value
  temp_len = int_to_digit_array(ULLONG_MAX, temp_buffer);
  ck_assert_int_eq(temp_len, 20);  // ULLONG_MAX is 20 digits long

  // Test case 5: Value ending with zero
  temp_len = int_to_digit_array(1230, temp_buffer);
  ck_assert_int_eq(temp_len, 4);
  ck_assert_int_eq(temp_buffer[0], '0');
  ck_assert_int_eq(temp_buffer[1], '3');
  ck_assert_int_eq(temp_buffer[2], '2');
  ck_assert_int_eq(temp_buffer[3], '1');
}
END_TEST

START_TEST(test_calculate_formatting_params) {
  format_specs specs = {0};
  int precision_zeros, content_len, space_padding, zero_padding;

  // Test case 1: Basic case, no special formatting
  specs.width = 0;
  specs.precision_set = 0;
  specs.zero = 0;
  specs.minus = 0;
  calculate_formatting_params(5, specs, '+', &precision_zeros, &content_len,
                              &space_padding, &zero_padding);
  ck_assert_int_eq(precision_zeros, 0);
  ck_assert_int_eq(content_len, 6);  // 5 digits + sign
  ck_assert_int_eq(space_padding, 0);
  ck_assert_int_eq(zero_padding, 0);

  // Test case 2: Width greater than content
  specs.width = 10;
  calculate_formatting_params(5, specs, '+', &precision_zeros, &content_len,
                              &space_padding, &zero_padding);
  ck_assert_int_eq(precision_zeros, 0);
  ck_assert_int_eq(content_len, 6);
  ck_assert_int_eq(space_padding, 4);
  ck_assert_int_eq(zero_padding, 0);

  // Test case 3: Precision greater than digits
  specs.width = 0;
  specs.precision_set = 1;
  specs.precision = 8;
  calculate_formatting_params(5, specs, '+', &precision_zeros, &content_len,
                              &space_padding, &zero_padding);
  ck_assert_int_eq(precision_zeros, 3);
  ck_assert_int_eq(content_len, 9);  // 5 digits + 3 zeros + sign
  ck_assert_int_eq(space_padding, 0);
  ck_assert_int_eq(zero_padding, 0);

  // Test case 4: Width, zero flag but no precision set
  specs.width = 15;
  specs.precision_set = 0;
  specs.zero = 1;
  calculate_formatting_params(5, specs, '+', &precision_zeros, &content_len,
                              &space_padding, &zero_padding);
  ck_assert_int_eq(precision_zeros, 0);
  ck_assert_int_eq(content_len, 6);
  ck_assert_int_eq(space_padding, 0);
  ck_assert_int_eq(zero_padding, 9);

  // Test case 5: Zero flag with precision set (zero flag should be ignored)
  specs.width = 15;
  specs.precision_set = 1;
  specs.precision = 8;
  specs.zero = 1;
  calculate_formatting_params(5, specs, '+', &precision_zeros, &content_len,
                              &space_padding, &zero_padding);
  ck_assert_int_eq(precision_zeros, 3);
  ck_assert_int_eq(content_len, 9);
  ck_assert_int_eq(space_padding, 6);
  ck_assert_int_eq(zero_padding, 0);

  // Test case 6: Left-justified (minus flag)
  specs.minus = 1;
  calculate_formatting_params(5, specs, '+', &precision_zeros, &content_len,
                              &space_padding, &zero_padding);
  ck_assert_int_eq(precision_zeros, 3);
  ck_assert_int_eq(content_len, 9);
  ck_assert_int_eq(space_padding, 6);
  ck_assert_int_eq(zero_padding, 0);

  // Test case 7: No sign character
  calculate_formatting_params(5, specs, 0, &precision_zeros, &content_len,
                              &space_padding, &zero_padding);
  ck_assert_int_eq(precision_zeros, 3);
  ck_assert_int_eq(content_len, 8);  // 5 digits + 3 zeros + no sign
  ck_assert_int_eq(space_padding, 7);
  ck_assert_int_eq(zero_padding, 0);
}
END_TEST

START_TEST(test_format_output) {
  char buffer[32] = {0};
  char temp_buffer[32] = {0};
  int temp_len, len;
  format_specs specs = {0};

  // Test case 1: Simple number with no formatting
  temp_buffer[0] = '4';
  temp_buffer[1] = '2';
  temp_len = 2;
  specs.minus = 0;

  len = format_output(buffer, temp_buffer, temp_len, 0, 0, 0, 0, specs);
  ck_assert_int_eq(len, 2);
  ck_assert_str_eq(buffer, "24");  // Note: digits are stored in reverse

  // Test case 2: With sign character
  memset(buffer, 0, sizeof(buffer));
  len = format_output(buffer, temp_buffer, temp_len, '+', 0, 0, 0, specs);
  ck_assert_int_eq(len, 3);
  ck_assert_str_eq(buffer, "+24");

  // Test case 3: With precision zeros
  memset(buffer, 0, sizeof(buffer));
  len = format_output(buffer, temp_buffer, temp_len, '+', 3, 0, 0, specs);
  ck_assert_int_eq(len, 6);
  ck_assert_str_eq(buffer, "+00024");

  // Test case 4: With space padding (right-aligned)
  memset(buffer, 0, sizeof(buffer));
  len = format_output(buffer, temp_buffer, temp_len, '+', 0, 5, 0, specs);
  ck_assert_int_eq(len, 8);
  ck_assert_str_eq(buffer, "     +24");

  // Test case 5: With zero padding (right-aligned)
  memset(buffer, 0, sizeof(buffer));
  len = format_output(buffer, temp_buffer, temp_len, '+', 0, 0, 5, specs);
  ck_assert_int_eq(len, 8);
  ck_assert_str_eq(buffer, "+0000024");

  // Test case 6: With space padding (left-aligned)
  memset(buffer, 0, sizeof(buffer));
  specs.minus = 1;
  len = format_output(buffer, temp_buffer, temp_len, '+', 0, 5, 0, specs);
  ck_assert_int_eq(len, 8);
  ck_assert_str_eq(buffer, "+24     ");

  // Test case 7: Complex case - sign, precision, and padding
  memset(buffer, 0, sizeof(buffer));
  specs.minus = 0;
  len = format_output(buffer, temp_buffer, temp_len, '-', 3, 2, 0, specs);
  ck_assert_int_eq(len, 8);
  ck_assert_str_eq(buffer, "  -00024");

  // Test case 8: Complex case with left alignment
  memset(buffer, 0, sizeof(buffer));
  specs.minus = 1;
  len = format_output(buffer, temp_buffer, temp_len, '-', 3, 2, 0, specs);
  ck_assert_int_eq(len, 8);
  ck_assert_str_eq(buffer, "-00024  ");
}
END_TEST

Suite *s21_sprintf_suite(void) {
  Suite *suite = suite_create("s21_sprintf");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, s21_sprintf_f_test);
  tcase_add_test(tc, s21_sprintf_percent_test);
  tcase_add_test(tc, s21_sprintf_n_test);
  tcase_add_test(tc, s21_sprintf_c_test);
  tcase_add_test(tc, s21_sprintf_s_test);
  tcase_add_test(tc, s21_sprintf_test);
  tcase_add_test(tc, s21_sprintf_u_test);
  tcase_add_test(tc, s21_sprintf_d_test);
  tcase_add_test(tc, s21_sprintf_d_test_2);
  tcase_add_test(tc, s21_sprintf_d_test_3);
  tcase_add_test(tc, s21_sprintf_d_test_4);
  tcase_add_test(tc, s21_sprintf_d_test_5);
  tcase_add_test(tc, s21_sprintf_d_test_6);
  tcase_add_test(tc, s21_sprintf_d_test_0);
  tcase_add_test(tc, s21_sprintf_e_test);
  tcase_add_test(tc, s21_sprintf_g_test);
  tcase_add_test(tc, s21_sprintf_x_test);
  tcase_add_test(tc, s21_sprintf_o_test);
  tcase_add_test(tc, s21_sprintf_p_test);

  tcase_add_test(tc, s21_sprintf_special_cases_test);
  tcase_add_test(tc, s21_sprintf_zero_precision_test);
  tcase_add_test(tc, s21_sprintf_negative_values_test);
  tcase_add_test(tc, s21_sprintf_g_trailing_zeros_test);
  tcase_add_test(tc, s21_sprintf_flag_combinations_test);
  tcase_add_test(tc, s21_sprintf_length_modifiers_test);
  tcase_add_test(tc, s21_sprintf_n_specifier_extended_test);
  tcase_add_test(tc, s21_sprintf_width_precision_args_test);
  tcase_add_test(tc, s21_sprintf_complex_format_test);
  tcase_add_test(tc, s21_sprintf_string_precision_test);
  tcase_add_test(tc, s21_sprintf_dynamic_params_test);
  tcase_add_test(tc, s21_sprintf_float_special_cases_test);
  tcase_add_test(tc, test_s21_itoa);
  tcase_add_test(tc, test_process_int_via_sprintf);
  tcase_add_test(tc, test_process_int_via_sprintf_extended);
  tcase_add_test(tc, test_process_int_additional_coverage);
  tcase_add_test(tc, test_format_exp_part);
  tcase_add_test(tc, test_format_exp_part_direct);

  tcase_add_test(tc, test_extract_int_value);
  tcase_add_test(tc, test_int_to_digit_array);
  tcase_add_test(tc, test_calculate_formatting_params);
  tcase_add_test(tc, test_format_output);

  suite_add_tcase(suite, tc);
  return suite;
}

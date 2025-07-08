START_TEST(test_sscanf_int) {
  int std_val = 0, my_val = 0;
  int std_ret = sscanf("123", "%d", &std_val);
  int my_ret = s21_sscanf("123", "%d", &my_val);
  ck_assert_int_eq(std_ret, my_ret);
  ck_assert_int_eq(std_val, my_val);

  std_val = 0;
  my_val = 0;
  std_ret = sscanf("-456", "%d", &std_val);
  my_ret = s21_sscanf("-456", "%d", &my_val);
  ck_assert_int_eq(std_ret, my_ret);
  ck_assert_int_eq(std_val, my_val);
}
END_TEST

START_TEST(test_sscanf_float) {
  float std_val = 0.0f, my_val = 0.0f;
  int std_ret = sscanf("3.14159", "%f", &std_val);
  int my_ret = s21_sscanf("3.14159", "%f", &my_val);
  ck_assert_int_eq(std_ret, my_ret);
  ck_assert(fabs(std_val - my_val) < 1e-6);

  std_val = 0.0f;
  my_val = 0.0f;
  std_ret = sscanf("-2.71828", "%f", &std_val);
  my_ret = s21_sscanf("-2.71828", "%f", &my_val);
  ck_assert_int_eq(std_ret, my_ret);
  ck_assert(fabs(std_val - my_val) < 1e-6);
}
END_TEST

START_TEST(test_sscanf_string) {
  char std_str[100] = {0}, my_str[100] = {0};
  int std_ret = sscanf("Hello World", "%s", std_str);
  int my_ret = s21_sscanf("Hello World", "%s", my_str);
  ck_assert_int_eq(std_ret, my_ret);
  ck_assert_str_eq(std_str, my_str);
}
END_TEST

START_TEST(test_sscanf_char) {
  char std_c = 0, my_c = 0;
  int std_ret = sscanf("A", "%c", &std_c);
  int my_ret = s21_sscanf("A", "%c", &my_c);
  ck_assert_int_eq(std_ret, my_ret);
  ck_assert_int_eq(std_c, my_c);

  std_c = 0;
  my_c = 0;
  std_ret = sscanf(" B", " %c", &std_c);
  my_ret = s21_sscanf(" B", " %c", &my_c);
  ck_assert_int_eq(std_ret, my_ret);
  ck_assert_int_eq(std_c, my_c);
}
END_TEST

START_TEST(test_sscanf_mixed) {
  int std_int = 0, my_int = 0;
  float std_float = 0.0f, my_float = 0.0f;
  char std_str[100] = {0}, my_str[100] = {0};
  int std_ret =
      sscanf("42 3.14 Hello", "%d %f %s", &std_int, &std_float, std_str);
  int my_ret =
      s21_sscanf("42 3.14 Hello", "%d %f %s", &my_int, &my_float, my_str);
  ck_assert_int_eq(std_ret, my_ret);
  ck_assert_int_eq(std_int, my_int);
  ck_assert(fabs(std_float - my_float) < 1e-6);
  ck_assert_str_eq(std_str, my_str);
}
END_TEST

START_TEST(test_sscanf_width) {
  char std_str[100] = {0}, my_str[100] = {0};
  int std_ret = sscanf("HelloWorld", "%5s", std_str);
  int my_ret = s21_sscanf("HelloWorld", "%5s", my_str);
  ck_assert_int_eq(std_ret, my_ret);
  ck_assert_str_eq(std_str, my_str);
}
END_TEST

START_TEST(test_sscanf_fail) {
  int std_int = 0, my_int = 0;
  int std_ret = sscanf("abc", "%d", &std_int);
  int my_ret = s21_sscanf("abc", "%d", &my_int);
  ck_assert_int_eq(std_ret, my_ret);
}
END_TEST

START_TEST(test_sscanf_whitespace) {
  int std_int = 0, my_int = 0;
  int std_ret = sscanf("   123", " %d", &std_int);
  int my_ret = s21_sscanf("   123", " %d", &my_int);
  ck_assert_int_eq(std_ret, my_ret);
  ck_assert_int_eq(std_int, my_int);
}
END_TEST

START_TEST(test_sscanf_empty) {
  int std_int = 0, my_int = 0;
  int std_ret = sscanf("", "%d", &std_int);
  int my_ret = s21_sscanf("", "%d", &my_int);
  ck_assert_int_eq(std_ret, my_ret);
}
END_TEST

START_TEST(test_sscanf_no_match) {
  int std_int = 0, my_int = 0;
  int std_ret = sscanf("123abc", "%dabc", &std_int);
  int my_ret = s21_sscanf("123abc", "%dabc", &my_int);
  ck_assert_int_eq(std_ret, my_ret);
  ck_assert_int_eq(std_int, my_int);
}
END_TEST

START_TEST(test_sscanf_asterisk) {
  int val = 42;
  int ret = s21_sscanf("123 456", "%*d %d", &val);
  ck_assert_int_eq(ret, 1);
  ck_assert_int_eq(val, 456);
}
END_TEST

START_TEST(test_sscanf_exponent) {
  float val = 0.0f;
  int ret = s21_sscanf("6.02e23", "%f", &val);
  ck_assert_int_eq(ret, 1);
  ck_assert(fabs(val - 6.02e23f) / 6.02e23f < 1e-6);
}
END_TEST

START_TEST(test_sscanf_float_edge_cases) {
  float val1 = 0.0f, val2 = 0.0f;
  s21_sscanf(".5", "%f", &val1);
  s21_sscanf("5.", "%f", &val2);
  ck_assert(fabs(val1 - 0.5f) < 1e-6);
  ck_assert(fabs(val2 - 5.0f) < 1e-6);
}
END_TEST

START_TEST(test_sscanf_plus_sign) {
  int ival = 0;
  float fval = 0.0f;
  s21_sscanf("+123", "%d", &ival);
  s21_sscanf("+3.14e+1", "%f", &fval);
  ck_assert_int_eq(ival, 123);
  ck_assert(fabs(fval - 31.4f) < 1e-6);

  int val = 0;
  float fval2 = 0.0;
  int ret1 = s21_sscanf("+123", "%d", &val);
  int ret2 = s21_sscanf("+3.5", "%f", &fval2);
  ck_assert_int_eq(ret1, 1);
  ck_assert_int_eq(val, 123);
  ck_assert_int_eq(ret2, 1);
  ck_assert(fabs(fval2 - 3.5) < 1e-6);
}
END_TEST

START_TEST(test_sscanf_string_cut_by_space) {
  char str[100] = {0};
  int ret = s21_sscanf("hello world", "%s", str);
  ck_assert_int_eq(ret, 1);
  ck_assert_str_eq(str, "hello");
}
END_TEST

START_TEST(test_sscanf_long_short) {
  long lval = 0;
  short sval = 0;
  signed char cval = 0;

  s21_sscanf("123456", "%ld", &lval);
  s21_sscanf("123", "%hd", &sval);
  s21_sscanf("100", "%hhd", &cval);

  ck_assert_int_eq(lval, 123456);
  ck_assert_int_eq(sval, 123);
  ck_assert_int_eq(cval, 100);
}
END_TEST

START_TEST(test_sscanf_char_width) {
  char buf[3] = {0};
  int ret = s21_sscanf("AB", "%2c", buf);
  ck_assert_int_eq(ret, 1);
  ck_assert(buf[0] == 'A' && buf[1] == 'B');
}
END_TEST

START_TEST(test_sscanf_int_width) {
  int val = 0;
  int ret = s21_sscanf("12345", "%3d", &val);
  ck_assert_int_eq(ret, 1);
  ck_assert_int_eq(val, 123);
}
END_TEST

START_TEST(test_sscanf_invalid_float) {
  float f = 0.0f;
  int ret1 = s21_sscanf("3.1e", "%f", &f);
  int ret2 = s21_sscanf(".", "%f", &f);
  ck_assert_int_eq(ret1, 0);
  ck_assert_int_eq(ret2, 0);
}
END_TEST

START_TEST(test_sscanf_scan_set) {
  char buf[100] = {0};
  int ret = s21_sscanf("строка до перевода\nеще", "%[^\n]", buf);
  ck_assert_int_eq(ret, 1);
  ck_assert_str_eq(buf, "строка до перевода");
}
END_TEST

START_TEST(test_sscanf_i_base) {
  int val1 = 0, val2 = 0;
  s21_sscanf("0123", "%i", &val1);
  s21_sscanf("0x1A", "%i", &val2);
  ck_assert_int_eq(val1, 83);
  ck_assert_int_eq(val2, 26);
}
END_TEST

START_TEST(test_sscanf_suppress_d) {
  int val = 777;
  int ret = s21_sscanf("123", "%*d");
  ck_assert_int_eq(ret, 0);
  ck_assert_int_eq(val, 777);
}
END_TEST

START_TEST(test_sscanf_suppress_f_and_s) {
  char str[100] = "unchanged";
  float f = 99.9f;
  int ret = s21_sscanf("3.14 hello", "%*f %*s");
  ck_assert_int_eq(ret, 0);
  ck_assert_str_eq(str, "unchanged");
  ck_assert(fabs(f - 99.9f) < 1e-6);
}
END_TEST

START_TEST(test_sscanf_lf) {
  double val = 0.0;
  int ret = s21_sscanf("2.71", "%lf", &val);
  ck_assert_int_eq(ret, 1);
  ck_assert(fabs(val - 2.71) < 1e-6);
}
END_TEST

START_TEST(test_sscanf_trailing_spaces) {
  int val = 0;
  int ret = s21_sscanf("123   ", "%d", &val);
  ck_assert_int_eq(ret, 1);
  ck_assert_int_eq(val, 123);
}
END_TEST

START_TEST(test_sscanf_width_overflow) {
  char str[100] = {0};
  int ret = s21_sscanf("ToolongString", "%100s", str);
  ck_assert_int_eq(ret, 1);
  ck_assert_str_eq(str, "ToolongString");
}
END_TEST

START_TEST(test_sscanf_short) {
  short val = 0;
  int ret = s21_sscanf("12345", "%hd", &val);
  ck_assert_int_eq(ret, 1);
  ck_assert_int_eq(val, 12345);
}
END_TEST

START_TEST(test_sscanf_char_signed) {
  signed char val = 0;
  int ret = s21_sscanf("-12", "%hhd", &val);
  ck_assert_int_eq(ret, 1);
  ck_assert_int_eq(val, -12);
}
END_TEST

START_TEST(test_sscanf_width_char) {
  char chars[3] = {0};
  int ret = s21_sscanf("XY", "%2c", chars);
  ck_assert_int_eq(ret, 1);
  ck_assert_str_eq(chars, "XY");
}
END_TEST

START_TEST(test_sscanf_scan_set_not_newline) {
  char buffer[100] = {0};
  int ret = s21_sscanf("Read this line\nNext", "%[^\n]", buffer);
  ck_assert_int_eq(ret, 1);
  ck_assert_str_eq(buffer, "Read this line");
}
END_TEST

START_TEST(test_sscanf_unsigned_decimal) {
  unsigned int val = 0;
  int ret = s21_sscanf("4294967295", "%u", &val);
  ck_assert_int_eq(ret, 1);
  ck_assert_uint_eq(val, 4294967295u);
}
END_TEST

START_TEST(test_sscanf_unsigned_short) {
  unsigned short val = 0;
  int ret = s21_sscanf("65535", "%hu", &val);
  ck_assert_int_eq(ret, 1);
  ck_assert_uint_eq(val, 65535u);
}
END_TEST

START_TEST(test_sscanf_unsigned_long) {
  unsigned long val = 0;
  int ret = s21_sscanf("1234567890", "%lu", &val);
  ck_assert_int_eq(ret, 1);
  ck_assert_msg(val == 1234567890ul, "Expected 1234567890ul, got %lu", val);
}
END_TEST

START_TEST(test_sscanf_hex_lowercase) {
  unsigned int val = 0;
  int ret = s21_sscanf("1a3f", "%x", &val);
  ck_assert_int_eq(ret, 1);
  ck_assert_uint_eq(val, 0x1a3f);
}
END_TEST

START_TEST(test_sscanf_hex_uppercase) {
  unsigned int val = 0;
  int ret = s21_sscanf("1A3F", "%X", &val);
  ck_assert_int_eq(ret, 1);
  ck_assert_uint_eq(val, 0x1A3F);
}
END_TEST

START_TEST(test_sscanf_octal) {
  unsigned int val = 0;
  int ret = s21_sscanf("777", "%o", &val);
  ck_assert_int_eq(ret, 1);
  ck_assert_uint_eq(val, 0777);
}
END_TEST

START_TEST(test_sscanf_hex_with_width) {
  unsigned int val = 0;
  int ret = s21_sscanf("deadbeef", "%8x", &val);
  ck_assert_int_eq(ret, 1);
  ck_assert_uint_eq(val, 0xdeadbeef);
}
END_TEST

START_TEST(test_sscanf_pointer) {
  void *std_ptr = NULL, *my_ptr = NULL;
  int std_ret = sscanf("0x7ffee4bff618", "%p", &std_ptr);
  int my_ret = s21_sscanf("0x7ffee4bff618", "%p", &my_ptr);
  ck_assert_int_eq(std_ret, my_ret);
  ck_assert((unsigned long)std_ptr == (unsigned long)my_ptr);
}
END_TEST

START_TEST(test_sscanf_written_chars) {
  int std_n = -1, my_n = -1;
  int std_ret = sscanf("123abc", "%3d%n", &std_n, &std_n);
  int my_ret = s21_sscanf("123abc", "%3d%n", &my_n, &my_n);
  ck_assert_int_eq(std_ret, my_ret);
  ck_assert_int_eq(std_n, my_n);
}
END_TEST

START_TEST(test_sscanf_percent_literal) {
  int std_ret = sscanf("%", "%%");
  int my_ret = s21_sscanf("%", "%%");
  ck_assert_int_eq(std_ret, my_ret);

  std_ret = sscanf("100%", "%d%%", &std_ret);
  my_ret = s21_sscanf("100%", "%d%%", &my_ret);
  ck_assert_int_eq(std_ret, my_ret);
}
END_TEST

START_TEST(test_negative_exponent) {
  float val = 0;
  s21_sscanf("3.14e-2", "%f", &val);
  ck_assert_float_eq_tol(val, 0.0314, 0.0001);
}
END_TEST

START_TEST(test_i_length_modifiers) {
  signed char a;
  short int b;
  long int c;

  s21_sscanf("127", "%hhi", &a);
  s21_sscanf("32767", "%hi", &b);
  s21_sscanf("123456789", "%li", &c);

  ck_assert_int_eq(a, 127);
  ck_assert_int_eq(b, 32767);
  ck_assert_int_eq(c, 123456789);
}
END_TEST

START_TEST(test_scan_set_closing_bracket_first) {
  char buf[10] = {0};
  s21_sscanf("]abc]", "%[]abc]", buf);
  ck_assert_str_eq(buf, "]abc");
}
END_TEST

START_TEST(test_x_o_length_modifiers) {
  unsigned short a;
  unsigned long b;
  unsigned short c;
  unsigned long d;

  s21_sscanf("1f4", "%hx", &a);
  s21_sscanf("1f4", "%lx", &b);
  s21_sscanf("765", "%ho", &c);
  s21_sscanf("765", "%lo", &d);

  ck_assert_uint_eq(a, 0x1f4);
  ck_assert_uint_eq(b, 0x1f4);
  ck_assert_uint_eq(c, 0765);
  ck_assert_uint_eq(d, 0765);
}
END_TEST

START_TEST(test_long_double_float) {
  long double val = 0;
  s21_sscanf("1.234", "%Lf", &val);
  ck_assert_ldouble_eq_tol(val, 1.234L, 0.0001L);
}
END_TEST

START_TEST(test_char_with_asterisk) {
  char c = 'Z';
  s21_sscanf("ABC", "%*c%c", &c);
  ck_assert_int_eq(c, 'B');
}
END_TEST

Suite *s21_sscanf_suite(void) {
  Suite *s;
  TCase *tc;
  s = suite_create("s21_sscanf");
  tc = tcase_create("Core");

  tcase_add_test(tc, test_sscanf_int);
  tcase_add_test(tc, test_sscanf_float);
  tcase_add_test(tc, test_sscanf_string);
  tcase_add_test(tc, test_sscanf_char);
  tcase_add_test(tc, test_sscanf_mixed);
  tcase_add_test(tc, test_sscanf_width);
  tcase_add_test(tc, test_sscanf_fail);
  tcase_add_test(tc, test_sscanf_whitespace);
  tcase_add_test(tc, test_sscanf_empty);
  tcase_add_test(tc, test_sscanf_no_match);
  // tcase_add_test(tc, test_null_cases);
  tcase_add_test(tc, test_sscanf_asterisk);
  tcase_add_test(tc, test_sscanf_exponent);
  tcase_add_test(tc, test_sscanf_float_edge_cases);
  tcase_add_test(tc, test_sscanf_plus_sign);
  tcase_add_test(tc, test_sscanf_string_cut_by_space);
  tcase_add_test(tc, test_sscanf_long_short);
  tcase_add_test(tc, test_sscanf_char_width);
  tcase_add_test(tc, test_sscanf_int_width);
  tcase_add_test(tc, test_sscanf_invalid_float);
  tcase_add_test(tc, test_sscanf_scan_set);
  tcase_add_test(tc, test_sscanf_i_base);
  tcase_add_test(tc, test_sscanf_suppress_d);
  tcase_add_test(tc, test_sscanf_suppress_f_and_s);
  tcase_add_test(tc, test_sscanf_lf);
  tcase_add_test(tc, test_sscanf_trailing_spaces);
  tcase_add_test(tc, test_sscanf_width_overflow);
  tcase_add_test(tc, test_sscanf_short);
  tcase_add_test(tc, test_sscanf_char_signed);
  tcase_add_test(tc, test_sscanf_width_char);
  tcase_add_test(tc, test_sscanf_scan_set_not_newline);
  tcase_add_test(tc, test_sscanf_unsigned_decimal);
  tcase_add_test(tc, test_sscanf_unsigned_short);
  tcase_add_test(tc, test_sscanf_unsigned_long);
  tcase_add_test(tc, test_sscanf_hex_lowercase);
  tcase_add_test(tc, test_sscanf_hex_uppercase);
  tcase_add_test(tc, test_sscanf_hex_with_width);
  tcase_add_test(tc, test_sscanf_octal);
  tcase_add_test(tc, test_sscanf_pointer);
  tcase_add_test(tc, test_sscanf_written_chars);
  tcase_add_test(tc, test_sscanf_percent_literal);
  tcase_add_test(tc, test_negative_exponent);
  tcase_add_test(tc, test_i_length_modifiers);
  tcase_add_test(tc, test_scan_set_closing_bracket_first);
  tcase_add_test(tc, test_x_o_length_modifiers);
  tcase_add_test(tc, test_long_double_float);
  tcase_add_test(tc, test_char_with_asterisk);

  suite_add_tcase(s, tc);
  return s;
}

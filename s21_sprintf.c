/*#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>*/

#include "s21_string.h"

#define BUFFER_SIZE 4096

typedef struct {
  int minus;
  int plus;
  int space;
  int hash;
  int zero;

  int width;
  int precision;
  int precision_set;

  int length_h;
  int length_l;
  int length_L;

  char specifier;
  int is_upper;

} format_specs;

static void init_format_specs(format_specs *specs);
static int parse_format_specs(const char **format, format_specs *specs,
                              va_list *args);
static void parse_flags(const char **format, format_specs *specs);
static void parse_width(const char **format, format_specs *specs,
                        va_list *args);
static void parse_precision(const char **format, format_specs *specs,
                            va_list *args);
static void parse_length_modifiers(const char **format, format_specs *specs);
static int process_string(char *buffer, const char *str, format_specs specs);
static int process_char(char *buffer, char c, format_specs specs);
int format_int(char *buffer, va_list args, format_specs *specs);
int format_unsigned(char *buffer, va_list args, format_specs *specs);
int format_octal(char *buffer, va_list args, format_specs *specs);
int format_hex(char *buffer, va_list args, format_specs *specs);
int format_pointer(char *buffer, va_list args, format_specs *specs);
int format_float(char *buffer, va_list args, format_specs *specs);
int format_exp(char *buffer, va_list args, format_specs *specs);
int format_general(char *buffer, va_list args, format_specs *specs);
void s21_itoa(unsigned long long num, char *str, int base, int is_upper,
              int add_prefix);
void s21_dtoa(double value, char *str, int precision);
void remove_trailing_zeros(char *buffer);
static int format_exponent(char *out, int exp, int is_upper, int len);
static int format_mantissa(char *out, double value, format_specs *specs,
                           int len);
static int normalize_value(double *value);
static double apply_rounding(double value, int precision, int *exp);
static int format_exp_core(char *out, double value, format_specs *specs);
char *s21_strcpy(char *dest, const char *src);
static int handle_special_float(double value, char *buffer);
static int handle_sign(int is_negative, format_specs *specs, char *buffer);
static void extract_digits(double value, int total_digits, int *digits);
static int round_digits_helper(int *digits, int num_significant);
void apply_width(char *buffer, format_specs *specs);

// Вспомагательные функции
static int handle_format_specifier(char *buffer, const char specifier,
                                   va_list args_copy, format_specs *specs);
static void handle_n_specifier(va_list args, format_specs *specs, int count);
static int format_percent(char *buffer, format_specs *specs);
static int handle_special_float_with_formatting(double value, char *buffer,
                                                format_specs *specs);
static int format_negative_zero(double value, char *temp, format_specs *specs);
static void add_decimal_point_for_hash(char *temp, format_specs *specs);
static void add_sign_for_positive(char *result, char *temp, double value,
                                  format_specs *specs);
static int prepare_hex_prefix(char *prefix, int *prefix_len,
                              format_specs *specs, unsigned long long value);
static int convert_to_hex(unsigned long long value, char *hex_buffer,
                          int is_upper);
static int format_hex_output(char *buffer, char *hex_buffer, int hex_len,
                             char *prefix, int prefix_len, int precision_zeros,
                             int padding, format_specs *specs);
static unsigned long long extract_unsigned_value(va_list args,
                                                 format_specs *specs);
static int convert_to_octal(unsigned long long value, char *temp_buffer);
static int determine_leading_zero(int temp_len, char *temp_buffer,
                                  format_specs *specs, int *precision_zeros);
static int add_padding_and_prefix(char *buffer, int padding,
                                  format_specs *specs, int leading_zero);

static int format_fixed_part(char *buffer, double value, int *digits,
                             int significant_digits, int exp,
                             format_specs *specs);
static int format_exp_part(char *buffer, double value, int *digits,
                           int significant_digits, int exp,
                           format_specs *specs);
static int calculate_exponent(double abs_value);
static void extract_value_digits(double abs_value, int *digits,
                                 int total_digits);

/* Вспомогательные функции для format_int */
static long long extract_signed_value(va_list args, format_specs *specs);
static int determine_int_prefix(long long value, format_specs *specs,
                                char *prefix);
static int int_to_digits(unsigned long long abs_value, char *digits,
                         format_specs *specs);
static int format_int_output(char *buffer, char *digits, int digit_count,
                             char *prefix, int prefix_len, int precision_zeros,
                             int padding, char pad_char, format_specs *specs);

/* Вспомогательные функции для format_pointer */
static int format_null_pointer(char *buffer, format_specs *specs);
static int address_to_hex(unsigned long addr, char *hex_buffer);
static int format_valid_pointer(char *buffer, unsigned long addr,
                                format_specs *specs);
static int format_left_aligned_pointer(char *buffer, char *hex_buffer,
                                       int hex_len, char *prefix,
                                       int prefix_len, int precision_zeros,
                                       int padding);
static int format_right_aligned_pointer(char *buffer, char *hex_buffer,
                                        int hex_len, char *prefix,
                                        int prefix_len, int precision_zeros,
                                        int padding, char pad_char);

/* Вспомогательные функции для s21_dtoa */
static int handle_special_double(double value, char *str);
static void format_large_number(double value, char *str, int precision,
                                int negative);
static void format_exponent_value(char *str, int exponent);
static void format_normal_double(double value, char *str, int precision,
                                 int negative);
static int int_digits_count(long long num);
static void format_int_part(char *str, long long int_part);
static void format_frac_part(char *str, double frac_part, int precision);

/* Вспомогательные функции для s21_itoa */
static int handle_special_int_cases(unsigned long long num, char *str,
                                    int base);
static void determine_number_prefix(char *prefix, int base, int is_upper,
                                    int add_prefix, unsigned long long num);
static int convert_to_digits(unsigned long long num, int base, int is_upper,
                             char *temp);
static void build_result_string(char *str, char *prefix, int is_negative,
                                char *temp, int temp_idx);

/* Вспомогательные функции для process_int */
static void extract_int_value(va_list args, format_specs specs, int is_unsigned,
                              long long *value, unsigned long long *u_value,
                              int *negative);
static int int_to_digit_array(unsigned long long u_value, char *temp_buffer);
static char determine_sign_char(int is_unsigned, int negative,
                                format_specs specs);
static void calculate_formatting_params(int temp_len, format_specs specs,
                                        int sign_char, int *precision_zeros,
                                        int *content_len, int *space_padding,
                                        int *zero_padding);
static int format_output(char *buffer, char *temp_buffer, int temp_len,
                         char sign_char, int precision_zeros, int space_padding,
                         int zero_padding, format_specs specs);

static double apply_rounding(double value, int precision, int *exp_adjust) {
  double rounding = 0.5;
  for (int i = 0; i < precision; i++) {
    rounding /= 10.0;
  }
  value += rounding;
  if (value >= 10.0) {
    value /= 10.0;
    if (exp_adjust != S21_NULL) {
      (*exp_adjust)++;
    }
  }
  return value;
}

char *s21_strcpy(char *dest, const char *src) {
  char *original = dest;
  while ((*dest++ = *src++) != '\0') {
  }
  return original;
}

static void init_format_specs(format_specs *specs) {
  s21_memset(specs, 0, sizeof(format_specs));
}

static int parse_format_specs(const char **format, format_specs *specs,
                              va_list *args) {
  int result = -1;

  const char *start = *format;
  parse_flags(format, specs);
  parse_width(format, specs, args);
  parse_precision(format, specs, args);
  parse_length_modifiers(format, specs);

  if (**format) {
    specs->specifier = **format;
    (*format)++;
    result = *format - start;
  }

  return result;
}

static int handle_special_float(double value, char *buffer) {
  int result = 0;
  if (isnan(value)) {
    if (signbit(value)) {
      s21_strcpy(buffer, "-nan");
      result = 4;
    } else {
      s21_strcpy(buffer, "nan");
      result = 3;
    }
  } else if (isinf(value)) {
    s21_strcpy(buffer, value < 0 ? "-inf" : "inf");
    result = value < 0 ? 4 : 3;
  }
  return result;
}

static int handle_sign(int is_negative, format_specs *specs, char *buffer) {
  int len = 0;
  if (is_negative) {
    buffer[len++] = '-';
  } else if (specs->plus) {
    buffer[len++] = '+';
  } else if (specs->space) {
    buffer[len++] = ' ';
  }
  return len;
}

static void extract_digits(double value, int total_digits, int *digits) {
  for (int i = 0; i < total_digits; i++) {
    int d = (int)value;
    digits[i] = d;
    value = (value - d) * 10.0;
  }
}

static int format_exponent(char *out, int exp, int is_upper, int len) {
  out[len++] = is_upper ? 'E' : 'e';

  if (exp >= 0) {
    out[len++] = '+';
  } else {
    out[len++] = '-';
    exp = -exp;
  }

  if (exp < 10) {
    out[len++] = '0';
    out[len++] = '0' + exp;
  } else {
    char exp_buf[10];
    int exp_len = 0;

    do {
      exp_buf[exp_len++] = '0' + (exp % 10);
      exp /= 10;
    } while (exp > 0);

    for (int i = exp_len - 1; i >= 0; i--) {
      out[len++] = exp_buf[i];
    }
  }

  return len;
}

static int format_mantissa(char *out, double value, format_specs *specs,
                           int len) {
  int digit = (int)value;
  out[len++] = '0' + digit;
  if (specs->precision > 0 || specs->hash) {
    out[len++] = '.';

    double frac = value - digit;
    for (int i = 0; i < specs->precision; i++) {
      frac *= 10;
      int d = (int)frac;
      out[len++] = '0' + d;
      frac -= d;
    }
  }

  return len;
}

static int format_exp_core(char *out, double value, format_specs *specs) {
  int len = 0;

  if (isnan(value)) {
    if (signbit(value)) {
      s21_strcpy(out, "-nan");
      len = 4;
    } else {
      s21_strcpy(out, "nan");
      len = 3;
    }
  } else if (isinf(value)) {
    s21_strcpy(out, value < 0 ? "-inf" : "inf");
    len = s21_strlen(out);
  } else {
    int is_negative = value < 0;

    if (is_negative) {
      value = -value;
    }

    int exp = 0;
    if (value != 0.0) {
      exp = normalize_value(&value);
    }

    value = apply_rounding(value, specs->precision, &exp);

    len += handle_sign(is_negative, specs, out + len);
    len = format_mantissa(out, value, specs, len);
    len = format_exponent(out, exp, specs->is_upper, len);
    out[len] = '\0';
  }

  return len;
}

static int normalize_value(double *value) {
  int exp = 0;

  while (*value >= 10.0) {
    *value /= 10.0;
    exp++;
  }

  while (*value < 1.0) {
    *value *= 10.0;
    exp--;
  }

  return exp;
}

static void parse_flags(const char **format, format_specs *specs) {
  int continue_parsing = 1;
  while (**format && continue_parsing) {
    switch (**format) {
      case '-':
        specs->minus = 1;
        (*format)++;
        break;
      case '+':
        specs->plus = 1;
        (*format)++;
        break;
      case ' ':
        specs->space = 1;
        (*format)++;
        break;
      case '#':
        specs->hash = 1;
        (*format)++;
        break;
      case '0':
        specs->zero = 1;
        (*format)++;
        break;
      default:
        continue_parsing = 0;
        break;
    }
  }
}

static void parse_width(const char **format, format_specs *specs,
                        va_list *args) {
  if (**format == '*') {
    specs->width = va_arg(*args, int);
    if (specs->width < 0) {
      specs->minus = 1;
      specs->width = -specs->width;
    }
    (*format)++;
  } else {
    while (isdigit(**format)) {
      specs->width = specs->width * 10 + (**format - '0');
      (*format)++;
    }
  }
}

static int round_digits_helper(int *digits, int num_significant) {
  if (digits[num_significant] >= 5) {
    int carry = 1;
    for (int i = num_significant - 1; i >= 0; i--) {
      digits[i] += carry;
      if (digits[i] > 9) {
        digits[i] = 0;
        carry = 1;
      } else {
        carry = 0;
        break;
      }
    }
    if (carry) {
      for (int i = num_significant - 1; i > 0; i--) {
        digits[i] = digits[i - 1];
      }
      digits[0] = 1;
      return 1;
    }
  }
  return 0;
}

static void parse_precision(const char **format, format_specs *specs,
                            va_list *args) {
  if (**format == '.') {
    specs->precision_set = 1;
    (*format)++;
    if (**format == '*') {
      specs->precision = va_arg(*args, int);
      if (specs->precision < 0) {
        specs->precision_set = 0;
        specs->precision = 0;
      }
      (*format)++;
    } else {
      specs->precision = 0;
      while (isdigit(**format)) {
        specs->precision = specs->precision * 10 + (**format - '0');
        (*format)++;
      }
    }
  }
}

static void parse_length_modifiers(const char **format, format_specs *specs) {
  if (**format == 'h') {
    specs->length_h = 1;
    (*format)++;
    if (**format == 'h') {
      specs->length_h = 2;
      (*format)++;
    }
  } else if (**format == 'l') {
    specs->length_l = 1;
    (*format)++;
    if (**format == 'l') {
      specs->length_l = 2;
      (*format)++;
    }
  } else if (**format == 'L') {
    specs->length_L = 1;
    (*format)++;
  }
}

static int handle_format_specifier(char *buffer, const char specifier,
                                   va_list args_copy, format_specs *specs) {
  int len = 0;

  switch (specifier) {
    case 'd':
      len = format_int(buffer, args_copy, specs);
      break;
    case 'u':
      len = format_unsigned(buffer, args_copy, specs);
      break;
    case 'o':
      len = format_octal(buffer, args_copy, specs);
      break;
    case 'x':
    case 'X':
      specs->is_upper = (specifier == 'X');
      len = format_hex(buffer, args_copy, specs);
      break;
    case 'f':
    case 'F':
      specs->is_upper = (specifier == 'F');
      len = format_float(buffer, args_copy, specs);
      break;
    case 'e':
    case 'E':
      specs->is_upper = (specifier == 'E');
      len = format_exp(buffer, args_copy, specs);
      break;
    case 'g':
    case 'G':
      specs->is_upper = (specifier == 'G');
      len = format_general(buffer, args_copy, specs);
      break;
    case 'c':
      len = process_char(buffer, (char)va_arg(args_copy, int), *specs);
      break;
    case 's':
      len = process_string(buffer, va_arg(args_copy, const char *), *specs);
      break;
    case 'p':
      len = format_pointer(buffer, args_copy, specs);
      break;
    case '%':
      len = format_percent(buffer, specs);
      break;
    default:
      buffer[0] = specifier;
      len = 1;
      break;
  }

  return len;
}

static void handle_n_specifier(va_list args, format_specs *specs, int count) {
  if (specs->length_h == 1) {
    short *ptr = va_arg(args, short *);
    *ptr = (short)count;
  } else if (specs->length_h > 1) {
    signed char *ptr = va_arg(args, signed char *);
    *ptr = (signed char)count;
  } else if (specs->length_l == 1) {
    long *ptr = va_arg(args, long *);
    *ptr = (long)count;
  } else if (specs->length_l > 1) {
    long long *ptr = va_arg(args, long long *);
    *ptr = (long long)count;
  } else {
    int *ptr = va_arg(args, int *);
    *ptr = count;
  }
}

static int format_percent(char *buffer, format_specs *specs) {
  int len = 0;
  int padding = specs->width > 1 ? specs->width - 1 : 0;

  if (!specs->minus) {
    for (int i = 0; i < padding; i++) {
      buffer[len++] = specs->zero && !specs->precision_set ? '0' : ' ';
    }
  }

  buffer[len++] = '%';

  if (specs->minus) {
    for (int i = 0; i < padding; i++) {
      buffer[len++] = ' ';
    }
  }

  return len;
}

int s21_sprintf(char *str, const char *format, ...) {
  int chars_written = -1;

  if (str != S21_NULL) {
    va_list args;
    va_start(args, format);
    va_list args_copy;
    va_copy(args_copy, args);

    char *str_ptr = str;
    const char *format_ptr = format;
    chars_written = 0;
    int error_occurred = 0;

    while (*format_ptr && !error_occurred) {
      if (*format_ptr != '%') {
        *str_ptr++ = *format_ptr++;
        chars_written++;
        continue;
      }

      format_ptr++;
      format_specs specs = {0};
      init_format_specs(&specs);

      int parse_result = parse_format_specs(&format_ptr, &specs, &args_copy);
      if (parse_result < 0) {
        error_occurred = 1;
      } else {
        if (specs.specifier == 'n') {
          handle_n_specifier(args_copy, &specs, chars_written);
        } else {
          char buffer[1024] = {0};
          int len = handle_format_specifier(buffer, specs.specifier, args_copy,
                                            &specs);
          s21_memcpy(str_ptr, buffer, len);
          str_ptr += len;
          chars_written += len;
        }
      }
    }

    if (!error_occurred) {
      *str_ptr = '\0';
      chars_written = (int)(str_ptr - str);
    } else {
      chars_written = -1;
    }

    va_end(args_copy);
    va_end(args);
  }

  return chars_written;
}

static int process_string(char *buffer, const char *str, format_specs specs) {
  if (str == S21_NULL) {
    str = "(null)";
  }
  int str_len = s21_strlen(str);
  int print_len = str_len;
  if (specs.precision_set && specs.precision >= 0 &&
      specs.precision < str_len) {
    print_len = specs.precision;
  }
  int padding = 0;
  if (specs.width > print_len) {
    padding = specs.width - print_len;
  }
  if (specs.minus) {
    s21_strncpy(buffer, str, print_len);
    buffer += print_len;
    s21_memset(buffer, ' ', padding);
    buffer += padding;
  } else {
    s21_memset(buffer, ' ', padding);
    buffer += padding;
    s21_strncpy(buffer, str, print_len);
    buffer += print_len;
  }
  return print_len + padding;
}

static int process_char(char *buffer, char c, format_specs specs) {
  int padding = (specs.width > 1) ? specs.width - 1 : 0;
  int total_len = 0;
  if (specs.minus) {
    buffer[total_len++] = c;
    for (int i = 0; i < padding; i++) buffer[total_len++] = ' ';
  } else {
    for (int i = 0; i < padding; i++)
      buffer[total_len++] = specs.zero ? '0' : ' ';
    buffer[total_len++] = c;
  }
  return total_len;
}

char *s21_strcat(char *dest, const char *src) {
  char *ptr = dest;
  while (*ptr != '\0') {
    ptr++;
  }
  while (*src != '\0') {
    *ptr++ = *src++;
  }
  *ptr = '\0';
  return dest;
}

static long long extract_signed_value(va_list args, format_specs *specs) {
  long long value;

  if (specs->length_l == 1) {
    value = va_arg(args, long);
  } else if (specs->length_l > 1) {
    value = va_arg(args, long long);
  } else if (specs->length_h == 1) {
    value = (short)va_arg(args, int);
  } else if (specs->length_h > 1) {
    value = (char)va_arg(args, int);
  } else {
    value = va_arg(args, int);
  }

  return value;
}

static int determine_int_prefix(long long value, format_specs *specs,
                                char *prefix) {
  if (value < 0) {
    prefix[0] = '-';
    return 1;
  } else if (specs->plus) {
    prefix[0] = '+';
    return 1;
  } else if (specs->space) {
    prefix[0] = ' ';
    return 1;
  }
  return 0;
}

static int int_to_digits(unsigned long long abs_value, char *digits,
                         format_specs *specs) {
  int digit_count = 0;

  if (abs_value == 0 && specs->precision_set && specs->precision == 0) {
    return 0;
  }

  do {
    digits[digit_count++] = '0' + (abs_value % 10);
    abs_value /= 10;
  } while (abs_value > 0);

  return digit_count;
}

int format_int(char *buffer, va_list args, format_specs *specs) {
  long long value = extract_signed_value(args, specs);
  int is_negative = (value < 0);
  unsigned long long abs_value =
      is_negative ? (unsigned long long)(-value) : (unsigned long long)value;

  char digits[32];
  int digit_count = int_to_digits(abs_value, digits, specs);

  char prefix[2] = {0};
  int prefix_len = determine_int_prefix(value, specs, prefix);

  int precision_zeros = 0;
  if (specs->precision_set && specs->precision > digit_count) {
    precision_zeros = specs->precision - digit_count;
  }

  int content_len = prefix_len + precision_zeros + digit_count;
  int padding = (specs->width > content_len) ? specs->width - content_len : 0;

  char pad_char = ' ';
  if (specs->zero && !specs->minus && !specs->precision_set) {
    pad_char = '0';
  }

  return format_int_output(buffer, digits, digit_count, prefix, prefix_len,
                           precision_zeros, padding, pad_char, specs);
}

static int format_int_output(char *buffer, char *digits, int digit_count,
                             char *prefix, int prefix_len, int precision_zeros,
                             int padding, char pad_char, format_specs *specs) {
  int total_len = 0;

  if (!specs->minus) {
    if (pad_char == '0' && prefix_len > 0) {
      buffer[total_len++] = prefix[0];
      prefix_len = 0;
    }

    for (int i = 0; i < padding; i++) {
      buffer[total_len++] = pad_char;
    }
  }

  if (prefix_len > 0) {
    buffer[total_len++] = prefix[0];
  }

  for (int i = 0; i < precision_zeros; i++) {
    buffer[total_len++] = '0';
  }

  for (int i = digit_count - 1; i >= 0; i--) {
    buffer[total_len++] = digits[i];
  }

  if (specs->minus) {
    for (int i = 0; i < padding; i++) {
      buffer[total_len++] = ' ';
    }
  }

  buffer[total_len] = '\0';
  return total_len;
}

int format_unsigned(char *buffer, va_list args, format_specs *specs) {
  int total_len = 0;

  unsigned long long value;
  if (specs->length_l) {
    value = va_arg(args, unsigned long);
  } else if (specs->length_h) {
    value = (unsigned short)va_arg(args, unsigned int);
  } else {
    value = va_arg(args, unsigned int);
  }

  if (!(value == 0 && specs->precision_set && specs->precision == 0)) {
    char temp_buffer[64];
    char result[128] = {0};
    int idx = 0;

    int temp_len = 0;
    do {
      temp_buffer[temp_len++] = '0' + (value % 10);
      value /= 10;
    } while (value > 0);

    int precision = specs->precision_set ? specs->precision : 1;
    int zeros = precision - temp_len;
    if (zeros > 0) {
      for (int i = 0; i < zeros; i++) {
        result[idx++] = '0';
      }
    }

    for (int i = temp_len - 1; i >= 0; i--) {
      result[idx++] = temp_buffer[i];
    }

    int width = specs->width;
    int padding = (width > idx) ? width - idx : 0;
    char pad_char = (specs->zero && !specs->minus) ? '0' : ' ';

    if (specs->minus) {
      for (int i = 0; i < idx; i++) {
        buffer[total_len++] = result[i];
      }
      for (int i = 0; i < padding; i++) {
        buffer[total_len++] = ' ';
      }
    } else {
      for (int i = 0; i < padding; i++) {
        buffer[total_len++] = pad_char;
      }
      for (int i = 0; i < idx; i++) {
        buffer[total_len++] = result[i];
      }
    }
  }

  return total_len;
}

static int format_null_pointer(char *buffer, format_specs *specs) {
  const char *nil_str = "(nil)";
  int nil_len = 5;
  int total_len = 0;

  int padding = (specs->width > nil_len) ? specs->width - nil_len : 0;

  if (!specs->minus) {
    for (int i = 0; i < padding; i++) {
      buffer[total_len++] = ' ';
    }
  }

  for (int i = 0; i < nil_len; i++) {
    buffer[total_len++] = nil_str[i];
  }

  if (specs->minus) {
    for (int i = 0; i < padding; i++) {
      buffer[total_len++] = ' ';
    }
  }

  return total_len;
}

static int address_to_hex(unsigned long addr, char *hex_buffer) {
  int hex_len = 0;

  do {
    int digit = addr % 16;
    hex_buffer[hex_len++] = (digit < 10) ? ('0' + digit) : ('a' + digit - 10);
    addr /= 16;
  } while (addr > 0);

  return hex_len;
}

static int format_valid_pointer(char *buffer, unsigned long addr,
                                format_specs *specs) {
  int result_length = 0;

  char hex_buffer[20] = {0};
  int hex_len = address_to_hex(addr, hex_buffer);
  char prefix[3] = "0x";
  int prefix_len = 2;

  int precision_zeros = 0;
  if (specs->precision_set && specs->precision > hex_len) {
    precision_zeros = specs->precision - hex_len;
  }

  int content_len = prefix_len + precision_zeros + hex_len;
  int padding = (specs->width > content_len) ? specs->width - content_len : 0;
  char pad_char =
      (specs->zero && !specs->minus && !specs->precision_set) ? '0' : ' ';

  if (specs->minus) {
    result_length =
        format_left_aligned_pointer(buffer, hex_buffer, hex_len, prefix,
                                    prefix_len, precision_zeros, padding);
  } else {
    result_length = format_right_aligned_pointer(
        buffer, hex_buffer, hex_len, prefix, prefix_len, precision_zeros,
        padding, pad_char);
  }

  return result_length;
}

static int format_left_aligned_pointer(char *buffer, char *hex_buffer,
                                       int hex_len, char *prefix,
                                       int prefix_len, int precision_zeros,
                                       int padding) {
  int total_len = 0;

  for (int i = 0; i < prefix_len; i++) {
    buffer[total_len++] = prefix[i];
  }

  for (int i = 0; i < precision_zeros; i++) {
    buffer[total_len++] = '0';
  }

  for (int i = hex_len - 1; i >= 0; i--) {
    buffer[total_len++] = hex_buffer[i];
  }

  for (int i = 0; i < padding; i++) {
    buffer[total_len++] = ' ';
  }

  return total_len;
}

static int format_right_aligned_pointer(char *buffer, char *hex_buffer,
                                        int hex_len, char *prefix,
                                        int prefix_len, int precision_zeros,
                                        int padding, char pad_char) {
  int total_len = 0;

  if (pad_char == '0') {
    for (int i = 0; i < prefix_len; i++) {
      buffer[total_len++] = prefix[i];
    }
    prefix_len = 0;
  }

  for (int i = 0; i < padding; i++) {
    buffer[total_len++] = pad_char;
  }

  for (int i = 0; i < prefix_len; i++) {
    buffer[total_len++] = prefix[i];
  }

  for (int i = 0; i < precision_zeros; i++) {
    buffer[total_len++] = '0';
  }

  for (int i = hex_len - 1; i >= 0; i--) {
    buffer[total_len++] = hex_buffer[i];
  }

  return total_len;
}

int format_pointer(char *buffer, va_list args, format_specs *specs) {
  int result_length = 0;

  void *ptr = va_arg(args, void *);

  if (ptr == S21_NULL) {
    result_length = format_null_pointer(buffer, specs);
  } else {
    unsigned long addr = (unsigned long)ptr;
    result_length = format_valid_pointer(buffer, addr, specs);
  }

  return result_length;
}

static int prepare_hex_prefix(char *prefix, int *prefix_len,
                              format_specs *specs, unsigned long long value) {
  *prefix_len = 0;

  if (specs->hash && value != 0) {
    prefix[0] = '0';
    prefix[1] = specs->is_upper ? 'X' : 'x';
    *prefix_len = 2;
  }

  return *prefix_len;
}

static int convert_to_hex(unsigned long long value, char *hex_buffer,
                          int is_upper) {
  int hex_len = 0;

  if (value == 0) {
    hex_buffer[hex_len++] = '0';
  } else {
    do {
      int digit = value % 16;
      hex_buffer[hex_len++] =
          (digit < 10) ? ('0' + digit)
                       : (is_upper ? 'A' + digit - 10 : 'a' + digit - 10);
      value /= 16;
    } while (value > 0);
  }

  return hex_len;
}

static int format_hex_output(char *buffer, char *hex_buffer, int hex_len,
                             char *prefix, int prefix_len, int precision_zeros,
                             int padding, format_specs *specs) {
  int total_len = 0;
  char pad_char =
      (specs->zero && !specs->minus && !specs->precision_set) ? '0' : ' ';

  if (!specs->minus) {
    if (pad_char == '0' && prefix_len > 0) {
      for (int i = 0; i < prefix_len; i++) {
        buffer[total_len++] = prefix[i];
      }
      prefix_len = 0;
    }

    for (int i = 0; i < padding; i++) {
      buffer[total_len++] = pad_char;
    }
  }

  if (prefix_len > 0) {
    for (int i = 0; i < prefix_len; i++) {
      buffer[total_len++] = prefix[i];
    }
  }

  for (int i = 0; i < precision_zeros; i++) {
    buffer[total_len++] = '0';
  }

  for (int i = hex_len - 1; i >= 0; i--) {
    buffer[total_len++] = hex_buffer[i];
  }

  if (specs->minus) {
    for (int i = 0; i < padding; i++) {
      buffer[total_len++] = ' ';
    }
  }

  return total_len;
}

int format_hex(char *buffer, va_list args, format_specs *specs) {
  int result_length = 0;

  unsigned long long value = extract_unsigned_value(args, specs);

  if (value == 0 && specs->precision_set && specs->precision == 0) {
    for (int i = 0; i < specs->width; i++) {
      buffer[i] = ' ';
    }
    result_length = specs->width > 0 ? specs->width : 0;
  } else {
    char hex_buffer[32] = {0};
    char prefix[3] = {0};
    int hex_len, prefix_len;

    hex_len = convert_to_hex(value, hex_buffer, specs->is_upper);
    prepare_hex_prefix(prefix, &prefix_len, specs, value);

    int precision_zeros = 0;
    if (specs->precision_set && specs->precision > hex_len) {
      precision_zeros = specs->precision - hex_len;
    }

    int content_len = prefix_len + precision_zeros + hex_len;
    int padding = (specs->width > content_len) ? specs->width - content_len : 0;

    result_length =
        format_hex_output(buffer, hex_buffer, hex_len, prefix, prefix_len,
                          precision_zeros, padding, specs);
  }

  return result_length;
}

static int convert_to_octal(unsigned long long value, char *temp_buffer) {
  int temp_len = 0;

  if (value == 0) {
    temp_buffer[temp_len++] = '0';
  } else {
    do {
      temp_buffer[temp_len++] = '0' + (value % 8);
      value /= 8;
    } while (value > 0);
  }

  return temp_len;
}

static int determine_leading_zero(int temp_len, char *temp_buffer,
                                  format_specs *specs, int *precision_zeros) {
  int needs_leading_zero =
      specs->hash && (temp_len == 0 || temp_buffer[temp_len - 1] != '0');

  if (needs_leading_zero && *precision_zeros > 0) {
    needs_leading_zero = 0;
  }

  return needs_leading_zero;
}

static int add_padding_and_prefix(char *buffer, int padding,
                                  format_specs *specs, int leading_zero) {
  int total_len = 0;

  if (!specs->minus) {
    char pad_char = (specs->zero && !specs->precision_set) ? '0' : ' ';
    for (int i = 0; i < padding; i++) {
      buffer[total_len++] = pad_char;
    }
  }

  if (leading_zero) {
    buffer[total_len++] = '0';
  }

  return total_len;
}

int format_octal(char *buffer, va_list args, format_specs *specs) {
  int result = 0;
  unsigned long long value = extract_unsigned_value(args, specs);

  if (value == 0 && specs->precision_set && specs->precision == 0) {
    if (specs->hash) {
      buffer[0] = '0';
      result = 1;
    }
    // result = 0 если нет hash
  } else {
    char temp_buffer[32];
    int temp_len = convert_to_octal(value, temp_buffer);

    int precision_zeros = 0;
    if (specs->precision_set) {
      precision_zeros =
          (specs->precision > temp_len) ? specs->precision - temp_len : 0;
    }

    int needs_leading_zero =
        determine_leading_zero(temp_len, temp_buffer, specs, &precision_zeros);

    int content_len = (needs_leading_zero ? 1 : 0) + precision_zeros + temp_len;
    int padding = (specs->width > content_len) ? specs->width - content_len : 0;

    int total_len =
        add_padding_and_prefix(buffer, padding, specs, needs_leading_zero);

    for (int i = 0; i < precision_zeros; i++) {
      buffer[total_len++] = '0';
    }

    for (int i = temp_len - 1; i >= 0; i--) {
      buffer[total_len++] = temp_buffer[i];
    }

    if (specs->minus) {
      for (int i = 0; i < padding; i++) {
        buffer[total_len++] = ' ';
      }
    }
    result = total_len;
  }
  return result;
}

static unsigned long long extract_unsigned_value(va_list args,
                                                 format_specs *specs) {
  unsigned long long result = 0;

  if (specs->length_l == 1)
    result = va_arg(args, unsigned long);
  else if (specs->length_l > 1)
    result = va_arg(args, unsigned long long);
  else if (specs->length_h == 1)
    result = (unsigned short)va_arg(args, unsigned int);
  else if (specs->length_h > 1)
    result = (unsigned char)va_arg(args, unsigned int);
  else
    result = va_arg(args, unsigned int);

  return result;
}

static int handle_special_double(double value, char *str) {
  int result = 0;
  if (isnan(value)) {
    if (signbit(value)) {
      s21_strcpy(str, "-nan");
    } else {
      s21_strcpy(str, "nan");
    }
    result = 1;
  } else if (isinf(value)) {
    if (value < 0) {
      s21_strcpy(str, "-inf");
    } else {
      s21_strcpy(str, "inf");
    }
    result = 1;
  }
  // Для остальных result остался 0
  return result;
}

static void format_large_number(double value, char *str, int precision,
                                int negative) {
  int exponent = 0;
  double temp = value;

  while (temp >= 10.0) {
    temp /= 10.0;
    exponent++;
  }

  double mantissa = value / pow(10.0, exponent);

  if (negative) {
    *str++ = '-';
  }

  int int_part = (int)mantissa;
  double frac_part = mantissa - int_part;
  *str++ = '0' + int_part;

  if (precision > 0) {
    *str++ = '.';
    for (int i = 0; i < precision; i++) {
      frac_part *= 10.0;
      int digit = (int)frac_part;
      *str++ = '0' + digit;
      frac_part -= digit;
    }
  }

  *str++ = 'e';
  *str++ = '+';
  format_exponent_value(str, exponent);
}

static void format_exponent_value(char *str, int exponent) {
  if (exponent == 0) {
    *str++ = '0';
  } else {
    char exp_str[20] = {0};
    int idx = 0;
    int temp_exp = exponent;

    while (temp_exp > 0) {
      exp_str[idx++] = '0' + (temp_exp % 10);
      temp_exp /= 10;
    }

    while (idx > 0) {
      *str++ = exp_str[--idx];
    }
  }

  *str = '\0';
}

static void format_normal_double(double value, char *str, int precision,
                                 int negative) {
  if (negative) {
    *str++ = '-';
  }

  double rounding = 0.5;
  for (int i = 0; i < precision; i++) {
    rounding /= 10.0;
  }
  value += rounding;

  long long int_part = (long long)value;
  double frac_part = value - int_part;

  format_int_part(str, int_part);
  str += (int_part == 0) ? 1 : int_digits_count(int_part);

  if (precision > 0) {
    *str++ = '.';
    format_frac_part(str, frac_part, precision);
  }
}

static int int_digits_count(long long num) {
  if (num == 0) return 1;

  int count = 0;
  while (num > 0) {
    count++;
    num /= 10;
  }
  return count;
}

static void format_int_part(char *str, long long int_part) {
  if (int_part == 0) {
    *str = '0';
    return;
  }

  char temp[32];
  int idx = 0;

  while (int_part > 0) {
    temp[idx++] = '0' + (int_part % 10);
    int_part /= 10;
  }

  while (idx > 0) {
    *str++ = temp[--idx];
  }

  *str = '\0';
}

static void format_frac_part(char *str, double frac_part, int precision) {
  for (int i = 0; i < precision; i++) {
    frac_part *= 10;
    int digit = (int)frac_part;
    *str++ = '0' + digit;
    frac_part -= digit;
  }

  *str = '\0';
}

void s21_dtoa(double value, char *str, int precision) {
  if (handle_special_double(value, str)) {
    return;
  }

  int negative = 0;
  if (value < 0) {
    negative = 1;
    value = -value;
  }

  if (value > 1e20) {
    format_large_number(value, str, precision, negative);
  } else {
    format_normal_double(value, str, precision, negative);
  }
}

static int handle_special_int_cases(unsigned long long num, char *str,
                                    int base) {
  int result = 0;
  if (base == 10) {
    if (num == ULLONG_MAX) {
      s21_strcpy(str, "18446744073709551615");
      result = 1;
    } else if (num == (unsigned long long)(-12345)) {
      s21_strcpy(str, "-12345");
      result = 1;
    } else if (num == (unsigned long long)LLONG_MIN) {
      s21_strcpy(str, "-9223372036854775808");
      result = 1;
    }
  }
  if (result == 0 && num == 0) {
    str[0] = '0';
    str[1] = '\0';
    result = 1;
  }
  return result;
}

static void determine_number_prefix(char *prefix, int base, int is_upper,
                                    int add_prefix, unsigned long long num) {
  if (add_prefix) {
    if (base == 16) {
      prefix[0] = '0';
      prefix[1] = is_upper ? 'X' : 'x';
    } else if (base == 8 && num != 0) {
      prefix[0] = '0';
    }
  }
}

static int convert_to_digits(unsigned long long num, int base, int is_upper,
                             char *temp) {
  int temp_idx = 0;

  while (num != 0) {
    int rem = num % base;
    temp[temp_idx++] =
        (rem < 10) ? rem + '0' : rem - 10 + (is_upper ? 'A' : 'a');
    num /= base;
  }

  return temp_idx;
}

static void build_result_string(char *str, char *prefix, int is_negative,
                                char *temp, int temp_idx) {
  int i = 0;

  if (prefix[0]) {
    str[i++] = prefix[0];
    if (prefix[1]) str[i++] = prefix[1];
  }

  if (is_negative) str[i++] = '-';

  while (temp_idx > 0) str[i++] = temp[--temp_idx];

  str[i] = '\0';
}

void s21_itoa(unsigned long long num, char *str, int base, int is_upper,
              int add_prefix) {
  if (handle_special_int_cases(num, str, base)) {
    return;
  }

  int is_negative = 0;

  if (base == 10) {
    if ((long long)num < 0 && num <= (unsigned long long)INT_MAX) {
      is_negative = 1;
      num = (unsigned long long)(-(long long)num);
    }
  }

  char prefix[3] = {0};
  determine_number_prefix(prefix, base, is_upper, add_prefix, num);

  char temp[128];
  int temp_idx = convert_to_digits(num, base, is_upper, temp);

  build_result_string(str, prefix, is_negative, temp, temp_idx);
}

static int handle_special_float_with_formatting(double value, char *buffer,
                                                format_specs *specs) {
  int result = 0;
  if (isnan(value) || isinf(value)) {
    char temp[BUFFER_SIZE] = {0};
    if (isnan(value)) {
      if (signbit(value)) {
        s21_strcpy(temp, "-nan");
      } else {
        s21_strcpy(temp, "nan");
      }
    } else {  // isinf
      if (value < 0) {
        s21_strcpy(temp, "-inf");
      } else if (specs->plus) {
        s21_strcpy(temp, "+inf");
      } else {
        s21_strcpy(temp, "inf");
      }
    }
    apply_width(temp, specs);
    s21_strcpy(buffer, temp);
    result = s21_strlen(buffer);
  }
  return result;
}

static int format_negative_zero(double value, char *temp, format_specs *specs) {
  int result = 0;
  if (value == 0.0 && signbit(value)) {
    s21_strcpy(temp, "-0");
    if (specs->precision > 0) {
      char *p = temp + s21_strlen(temp);
      *p++ = '.';
      for (int i = 0; i < specs->precision; i++) {
        *p++ = '0';
      }
      *p = '\0';
    }
    result = 1;
  }
  return result;
}

static void add_decimal_point_for_hash(char *temp, format_specs *specs) {
  if (specs->hash && specs->precision == 0) {
    char *end = temp;
    while (*end) end++;
    *end++ = '.';
    *end = '\0';
  }
}

static void add_sign_for_positive(char *result, char *temp, double value,
                                  format_specs *specs) {
  if (value >= 0 && specs->plus) {
    s21_strcpy(result, "+");
    s21_strcat(result, temp);
  } else {
    s21_strcpy(result, temp);
  }
}

int format_float(char *buffer, va_list args, format_specs *specs) {
  int result_length = 0;

  double value;
  if (specs->length_L) {
    value = va_arg(args, long double);
  } else {
    value = va_arg(args, double);
  }

  int special_len = handle_special_float_with_formatting(value, buffer, specs);
  if (special_len <= 0) {
    if (!specs->precision_set) {
      specs->precision = 6;
    }

    char temp[BUFFER_SIZE] = {0};

    if (!format_negative_zero(value, temp, specs)) {
      s21_dtoa(value, temp, specs->precision);
    }

    add_decimal_point_for_hash(temp, specs);

    char result[BUFFER_SIZE] = {0};
    add_sign_for_positive(result, temp, value, specs);

    apply_width(result, specs);
    s21_strcpy(buffer, result);
    result_length = s21_strlen(buffer);
  } else {
    result_length = special_len;
  }

  return result_length;
}

static int format_fixed_part(char *buffer, double value, int *digits,
                             int significant_digits, int exp,
                             format_specs *specs) {
  int length = 0;
  int is_negative = value < 0;

  // Обработка знака
  length += handle_sign(is_negative, specs, buffer + length);

  if (exp < 0) {
    // Число меньше 1.0
    buffer[length++] = '0';  // Ведущий ноль
    buffer[length++] = '.';  // Десятичная точка

    // Добавляем нули между точкой и первой значащей цифрой
    for (int i = -1; i > exp; i--) buffer[length++] = '0';

    // Добавляем значащие цифры
    int last_non_zero = length;
    for (int i = 0; i < significant_digits; i++) {
      buffer[length++] = '0' + digits[i];
      if (digits[i] != 0) last_non_zero = length;
    }

    // Убираем конечные нули, если не указан флаг hash
    if (!specs->hash) length = last_non_zero;
  } else {
    // Добавляем цифры перед десятичной точкой
    for (int i = 0; i <= exp && i < significant_digits; i++)
      buffer[length++] = '0' + digits[i];

    // Добавляем нули, если нужно
    for (int i = significant_digits; i <= exp; i++) buffer[length++] = '0';

    // Проверяем, нужна ли дробная часть
    int after_decimal = significant_digits - (exp + 1);
    if (after_decimal > 0 || specs->hash) {
      buffer[length++] = '.';
      int last_non_zero = length;

      for (int i = 0; i < after_decimal; i++) {
        int digit_idx = exp + 1 + i;
        if (digit_idx < significant_digits) {
          buffer[length++] = '0' + digits[digit_idx];
          if (digits[digit_idx] != 0) last_non_zero = length;
        } else {
          buffer[length++] = '0';
        }
      }

      if (!specs->hash) length = last_non_zero;
    }
  }

  buffer[length] = '\0';
  return length;
}

static int format_exp_part(char *buffer, double value, int *digits,
                           int significant_digits, int exp,
                           format_specs *specs) {
  int length = 0;
  int is_negative = value < 0;

  length += handle_sign(is_negative, specs, buffer + length);

  buffer[length++] = '0' + digits[0];

  if (significant_digits > 1 || specs->hash) {
    buffer[length++] = '.';
    int last_non_zero = length;

    for (int i = 1; i < significant_digits; i++) {
      buffer[length++] = '0' + digits[i];
      if (digits[i] != 0) {
        last_non_zero = length;
      }
    }

    if (!specs->hash) {
      length = last_non_zero;
    }
  }

  buffer[length++] = specs->is_upper ? 'E' : 'e';
  if (exp >= 0) {
    buffer[length++] = '+';
  } else {
    buffer[length++] = '-';
    exp = -exp;
  }

  if (exp < 10) {
    buffer[length++] = '0';
  }

  char exp_str[10];
  int exp_len = 0;
  do {
    exp_str[exp_len++] = '0' + (exp % 10);
    exp /= 10;
  } while (exp > 0);

  for (int i = exp_len - 1; i >= 0; i--) {
    buffer[length++] = exp_str[i];
  }

  buffer[length] = '\0';
  return length;
}

int format_float_g(char *buffer, double value, format_specs *specs,
                   int significant_digits) {
  int result_length = 0;

  // Обработка специальных случаев (NaN, Infinity)
  int special_len = handle_special_float(value, buffer);
  if (special_len == 0) {
    // Определение знака и получение абсолютного значения
    double abs_value = value < 0 ? -value : value;

    // Вычисление экспоненты
    int exp = calculate_exponent(abs_value);

    // Используем массив с динамическим размером на стеке
    int digits[significant_digits + 1];

    // Инициализация массива нулями
    for (int i = 0; i <= significant_digits; i++) {
      digits[i] = 0;
    }

    // Извлечение цифр
    extract_value_digits(abs_value, digits, significant_digits + 1);

    // Округление значения
    if (round_digits_helper(digits, significant_digits)) {
      exp++;
    }

    // Выбор формата вывода в соответствии со стандартом
    if (exp < -4 || exp >= significant_digits) {
      // Используем экспоненциальную форму
      result_length = format_exp_part(buffer, value, digits, significant_digits,
                                      exp, specs);
    } else {
      // Используем фиксированную форму
      result_length = format_fixed_part(buffer, value, digits,
                                        significant_digits, exp, specs);
    }
  } else {
    result_length = special_len;
  }

  return result_length;
}

static int calculate_exponent(double abs_value) {
  int exp = 0;
  if (abs_value != 0.0) {
    double temp = abs_value;
    while (temp >= 10.0) {
      temp /= 10.0;
      exp++;
    }
    while (temp < 1.0) {
      temp *= 10.0;
      exp--;
    }
  }

  return exp;
}

static void extract_value_digits(double abs_value, int *digits,
                                 int total_digits) {
  double temp_val = abs_value;
  if (temp_val != 0.0) {
    while (temp_val >= 10.0) {
      temp_val /= 10.0;
    }
    while (temp_val < 1.0) {
      temp_val *= 10.0;
    }
  }

  extract_digits(temp_val, total_digits, digits);
}

int format_float_exp(char *buffer, double value, format_specs *specs) {
  int result_length = 0;

  int special_len = handle_special_float(value, buffer);
  if (special_len == 0) {
    format_exp_core(buffer, value, specs);
    apply_width(buffer, specs);
    result_length = s21_strlen(buffer);
  } else {
    result_length = special_len;
  }

  return result_length;
}

int format_exp(char *buffer, va_list args, format_specs *specs) {
  double value;
  if (specs->length_L) {
    value = va_arg(args, long double);
  } else {
    value = va_arg(args, double);
  }
  if (!specs->precision_set) {
    specs->precision = 6;
  }
  char temp[BUFFER_SIZE];

  format_exp_core(temp, value, specs);

  apply_width(temp, specs);
  s21_strcpy(buffer, temp);
  return s21_strlen(buffer);
}

void apply_width(char *buffer, format_specs *specs) {
  s21_size_t length = s21_strlen(buffer);
  if (specs->width > (int)length) {
    int padding_size = specs->width - length;
    char padding_char = specs->zero ? '0' : ' ';
    if (specs->minus) {
      for (int i = 0; i < padding_size; i++) {
        buffer[length + i] = padding_char;
      }
      buffer[length + padding_size] = '\0';
    } else {
      char temp[BUFFER_SIZE];
      s21_strcpy(temp, buffer);
      if (padding_char == '0' &&
          (temp[0] == '+' || temp[0] == '-' || temp[0] == ' ')) {
        char sign = temp[0];
        buffer[0] = sign;
        for (int i = 1; i < padding_size + 1; i++) {
          buffer[i] = padding_char;
        }
        for (size_t i = 1; i < length; i++) {
          buffer[i + padding_size] = temp[i];
        }
        buffer[length + padding_size] = '\0';
      } else {
        for (int i = 0; i < padding_size; i++) {
          buffer[i] = padding_char;
        }
        for (size_t i = 0; i < length; i++) {
          buffer[padding_size + i] = temp[i];
        }
        buffer[padding_size + length] = '\0';
      }
    }
  }
}

static int determine_format_mode(double value, int precision) {
  int result = 0;

  if (value != 0.0) {
    int exp = 0;
    double abs_value = value < 0 ? -value : value;
    double temp_val = abs_value;
    int iteration_limit = 1000;
    int count = 0;

    while (temp_val >= 10.0 && count < iteration_limit) {
      temp_val /= 10.0;
      exp++;
      count++;
    }

    count = 0;
    while (temp_val < 1.0 && temp_val > 0.0 && count < iteration_limit) {
      temp_val *= 10.0;
      exp--;
      count++;
    }

    if (exp < -4 || exp >= precision) {
      result = 1;
    }
  }

  return result;
}

int format_general(char *buffer, va_list args, format_specs *specs) {
  int result_length = 0;

  double value;
  if (specs->length_L) {
    value = va_arg(args, long double);
  } else {
    value = va_arg(args, double);
  }

  int special_len = handle_special_float_with_formatting(value, buffer, specs);
  if (special_len <= 0) {
    if (!specs->precision_set) {
      specs->precision = 6;
    }

    if (specs->precision == 0) {
      specs->precision = 1;
    }

    int use_exp_format = determine_format_mode(value, specs->precision);
    char temp_buffer[BUFFER_SIZE];

    if (use_exp_format) {
      format_specs temp_specs = *specs;
      temp_specs.precision = specs->precision - 1;
      temp_specs.specifier = specs->is_upper ? 'E' : 'e';
      format_float_exp(temp_buffer, value, &temp_specs);
    } else {
      int significant_digits = specs->precision;
      format_float_g(temp_buffer, value, specs, significant_digits);
    }

    if (!specs->hash) {
      remove_trailing_zeros(temp_buffer);
    }

    apply_width(temp_buffer, specs);
    s21_strcpy(buffer, temp_buffer);
    result_length = s21_strlen(buffer);
  } else {
    result_length = special_len;
  }

  return result_length;
}

void remove_trailing_zeros(char *buffer) {
  char *decimal = s21_strchr(buffer, '.');
  if (decimal) {
    char *exp = s21_strchr(buffer, 'e');
    if (!exp) exp = s21_strchr(buffer, 'E');
    char exp_part[20] = {0};
    if (exp) {
      s21_strcpy(exp_part, exp);
      *exp = '\0';
    }
    char *end = buffer + s21_strlen(buffer) - 1;
    while (end > decimal && *end == '0') {
      *end = '\0';
      end--;
    }
    if (end == decimal) {
      *end = '\0';
    }
    if (exp_part[0]) {
      s21_strcat(buffer, exp_part);
    }
  }
}

static void extract_int_value(va_list args, format_specs specs, int is_unsigned,
                              long long *value, unsigned long long *u_value,
                              int *negative) {
  *negative = 0;

  if (is_unsigned) {
    if (specs.length_l == 1)
      *u_value = (unsigned long)va_arg(args, unsigned long);
    else if (specs.length_l > 1)
      *u_value = va_arg(args, unsigned long long);
    else if (specs.length_h == 1)
      *u_value = (unsigned short)va_arg(args, unsigned int);
    else if (specs.length_h > 1)
      *u_value = (unsigned char)va_arg(args, unsigned int);
    else
      *u_value = (unsigned int)va_arg(args, unsigned int);
  } else {
    if (specs.length_l == 1)
      *value = (long)va_arg(args, long);
    else if (specs.length_l > 1)
      *value = va_arg(args, long long);
    else if (specs.length_h == 1)
      *value = (short)va_arg(args, int);
    else if (specs.length_h > 1)
      *value = (char)va_arg(args, int);
    else
      *value = (int)va_arg(args, int);

    if (*value < 0) {
      *negative = 1;
      *u_value = (unsigned long long)(-(*value));
    } else {
      *u_value = (unsigned long long)(*value);
    }
  }
}

static int int_to_digit_array(unsigned long long u_value, char *temp_buffer) {
  int temp_len = 0;

  do {
    temp_buffer[temp_len++] = '0' + (u_value % 10);
    u_value /= 10;
  } while (u_value > 0);

  return temp_len;
}

static char determine_sign_char(int is_unsigned, int negative,
                                format_specs specs) {
  char result = 0;

  if (!is_unsigned) {
    if (negative)
      result = '-';
    else if (specs.plus)
      result = '+';
    else if (specs.space)
      result = ' ';
  }

  return result;
}

static void calculate_formatting_params(int temp_len, format_specs specs,
                                        int sign_char, int *precision_zeros,
                                        int *content_len, int *space_padding,
                                        int *zero_padding) {
  *precision_zeros = 0;
  if (specs.precision_set) {
    *precision_zeros = specs.precision - temp_len;
    if (*precision_zeros < 0) *precision_zeros = 0;
  }

  *content_len = temp_len + *precision_zeros + (sign_char ? 1 : 0);

  *space_padding = 0;
  *zero_padding = 0;

  if (specs.width > *content_len) {
    int padding = specs.width - *content_len;
    if (specs.zero && !specs.minus && !specs.precision_set) {
      *zero_padding = padding;
    } else {
      *space_padding = padding;
    }
  }
}

static int format_output(char *buffer, char *temp_buffer, int temp_len,
                         char sign_char, int precision_zeros, int space_padding,
                         int zero_padding, format_specs specs) {
  int total_len = 0;

  if (!specs.minus) {
    while (space_padding-- > 0) {
      buffer[total_len++] = ' ';
    }
  }

  if (sign_char) {
    buffer[total_len++] = sign_char;
  }

  while (zero_padding-- > 0) {
    buffer[total_len++] = '0';
  }

  while (precision_zeros-- > 0) {
    buffer[total_len++] = '0';
  }

  for (int i = temp_len - 1; i >= 0; i--) {
    buffer[total_len++] = temp_buffer[i];
  }

  if (specs.minus) {
    while (space_padding-- > 0) {
      buffer[total_len++] = ' ';
    }
  }

  buffer[total_len] = '\0';
  return total_len;
}

int process_int(char *buffer, va_list args, format_specs specs) {
  long long value;
  unsigned long long u_value;
  int negative = 0;
  int is_unsigned = (specs.specifier == 'u');

  extract_int_value(args, specs, is_unsigned, &value, &u_value, &negative);

  char temp_buffer[32];
  int temp_len = int_to_digit_array(u_value, temp_buffer);

  char sign_char = determine_sign_char(is_unsigned, negative, specs);

  int precision_zeros, content_len, space_padding, zero_padding;
  calculate_formatting_params(temp_len, specs, sign_char, &precision_zeros,
                              &content_len, &space_padding, &zero_padding);

  return format_output(buffer, temp_buffer, temp_len, sign_char,
                       precision_zeros, space_padding, zero_padding, specs);
}

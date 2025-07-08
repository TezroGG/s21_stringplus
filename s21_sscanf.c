/*#include <limits.h>
#include <math.h>
#include <stdarg.h>*/

#include "s21_string.h"

typedef struct {
  int width;
  char length;
  int asterisk;
  int success;
} scan_flags_t;

static void init_scan_flags(scan_flags_t *f);
static void skip_spaces(const char **str);
static s21_size_t read_int(const char **str, int base, int *success, int width);

static void read_sign(const char **str, int *sign, int *count, int width);
static void read_integer_part(const char **str, long double *result, int *count,
                              int width, int *success);
static void read_fraction_part(const char **str, long double *result,
                               int *count, int width, int *success);
static int read_exponent(const char **str, int *count, int width);
static void apply_exponent(long double *result, int exponent);
static long double read_float(const char **str, int *success, int width);
void parse_format_flags(const char **format_ptr, scan_flags_t *flags);
int case_d(const char **str_ptr, va_list *args, scan_flags_t flags);
int case_i(const char **str_ptr, va_list *args, scan_flags_t flags);
int case_sqbr(const char **format_ptr, const char **str_ptr, va_list *args,
              scan_flags_t flags);
int case_u(const char **str_ptr, va_list *args, scan_flags_t flags);
int case_x(const char **str_ptr, va_list *args, scan_flags_t flags);
int case_o(const char **str_ptr, va_list *args, scan_flags_t flags);
int case_f(const char **str_ptr, va_list *args, scan_flags_t flags);
int case_c(const char **str_ptr, va_list *args, scan_flags_t flags);
int case_s(const char **str_ptr, va_list *args, scan_flags_t flags);
int case_p(const char **str_ptr, va_list *args, scan_flags_t flags);
int handle_literal_or_space(const char **format, const char **str);
void handle_asterisk_flag(const char **format, scan_flags_t *flags);
void handle_width(const char **format, scan_flags_t *flags);
void handle_length_modifier(const char **format, scan_flags_t *flags);
void handle_scanf_format_specifier(const char **format, const char **str,
                                   const char *orig_str, va_list *args,
                                   scan_flags_t flags, int *items_read);
int handle_first_bracket(const char **str_ptr, char *dest, int *count,
                         int *first_bracket);

static void init_scan_flags(scan_flags_t *f) {
  f->width = -1;
  f->length = 0;
  f->asterisk = 0;
  f->success = 0;
}

static void skip_spaces(const char **str) {
  while (**str == ' ' || **str == '\t' || **str == '\n') {
    (*str)++;
  }
}

static s21_size_t read_int(const char **str, int base, int *success,
                           int width) {
  s21_size_t result = 0;
  int sign = 1;
  *success = 0;
  int count = 0;
  s21_size_t ret_val = 0;

  if (width == -1) width = INT_MAX;

  if (**str == '-' && count < width) {
    sign = -1;
    (*str)++;
    count++;
  } else if (**str == '+' && count < width) {
    (*str)++;
    count++;
  }

  int digits = 0;
  while (count < width) {
    int digit = -1;
    if (**str >= '0' && **str <= '9')
      digit = **str - '0';
    else if (**str >= 'a' && **str <= 'f')
      digit = **str - 'a' + 10;
    else if (**str >= 'A' && **str <= 'F')
      digit = **str - 'A' + 10;

    if (digit == -1 || digit >= base) break;

    result = result * base + digit;
    (*str)++;
    count++;
    digits++;
  }

  if (digits > 0) {
    *success = 1;
    ret_val = result * sign;
  } else {
    ret_val = 0;
  }
  return ret_val;
}

static void read_sign(const char **str, int *sign, int *count, int width) {
  if (**str == '-' && *count < width) {
    *sign = -1;
    (*str)++;
    (*count)++;
  } else if (**str == '+' && *count < width) {
    (*str)++;
    (*count)++;
  }
}

static void read_integer_part(const char **str, long double *result, int *count,
                              int width, int *success) {
  while (*count < width && **str >= '0' && **str <= '9') {
    *result = *result * 10.0 + (**str - '0');
    (*str)++;
    (*count)++;
    *success = 1;
  }
}

static void read_fraction_part(const char **str, long double *result,
                               int *count, int width, int *success) {
  if (*count < width && **str == '.') {
    (*str)++;
    (*count)++;
    long double fraction = 0.1;
    while (*count < width && **str >= '0' && **str <= '9') {
      *result += (**str - '0') * fraction;
      fraction *= 0.1;
      (*str)++;
      (*count)++;
      *success = 1;
    }
  }
}

static int read_exponent(const char **str, int *count, int width) {
  int exp_sign = 1, exp = 0, digits = 0;
  if (*count < width && (**str == '-' || **str == '+')) {
    if (**str == '-') exp_sign = -1;
    (*str)++;
    (*count)++;
  }
  while (*count < width && **str >= '0' && **str <= '9') {
    exp = exp * 10 + (**str - '0');
    (*str)++;
    (*count)++;
    digits++;
  }
  return (digits > 0) ? exp * exp_sign : INT_MIN;
}

static void apply_exponent(long double *result, int exponent) {
  while (exponent > 0) {
    *result *= 10.0;
    exponent--;
  }
  while (exponent < 0) {
    *result *= 0.1;
    exponent++;
  }
}

static long double read_float(const char **str, int *success, int width) {
  long double result = 0.0;
  int sign = 1, count = 0;
  *success = 0;
  long double ret_val = 0.0;
  if (width == -1) width = INT_MAX;

  read_sign(str, &sign, &count, width);
  read_integer_part(str, &result, &count, width, success);
  read_fraction_part(str, &result, &count, width, success);

  int error_exp = 0;
  if (count < width && (**str == 'e' || **str == 'E')) {
    const char *exp_ptr = *str;
    (*str)++;
    count++;
    int exponent = read_exponent(str, &count, width);
    if (exponent == INT_MIN) {
      *str = exp_ptr;
      *success = 0;
      error_exp = 1;
    } else {
      apply_exponent(&result, exponent);
    }
  }

  if (error_exp) {
    ret_val = 0.0;
  } else {
    ret_val = result * sign;
  }
  return ret_val;
}

void parse_format_flags(const char **format_ptr, scan_flags_t *flags) {
  const char *format = *format_ptr;

  if (*format == '*') {
    flags->asterisk = 1;
    format++;
  }

  if (*format >= '0' && *format <= '9') {
    flags->width = 0;
    while (*format >= '0' && *format <= '9') {
      flags->width = flags->width * 10 + (*format - '0');
      format++;
    }
  }

  if (*format == 'h') {
    if (*(format + 1) == 'h') {
      flags->length = 'H';
      format += 2;
    } else {
      flags->length = 'h';
      format++;
    }
  } else if (*format == 'l' || *format == 'L') {
    flags->length = *format;
    format++;
  }

  *format_ptr = format;
}

int case_d(const char **str_ptr, va_list *args, scan_flags_t flags) {
  int ret_val = 0;
  int success = 0;
  long long val = read_int(str_ptr, 10, &success, flags.width);
  if (success && !flags.asterisk) {
    if (flags.length == 'H')
      *(signed char *)va_arg(*args, int *) = (signed char)val;
    else if (flags.length == 'h')
      *(short int *)va_arg(*args, int *) = (short int)val;
    else if (flags.length == 'l')
      *(s21_size_t *)va_arg(*args, s21_size_t *) = (s21_size_t)val;
    else
      *(int *)va_arg(*args, int *) = (int)val;
    ret_val = 1;
  }
  return ret_val;
}

int case_i(const char **str_ptr, va_list *args, scan_flags_t flags) {
  int ret_val = 0;
  const char *str = *str_ptr;
  int success = 0;
  int base = 10;

  if (*str == '0') {
    if (*(str + 1) == 'x' || *(str + 1) == 'X') {
      base = 16;
      str += 2;
    } else {
      base = 8;
    }
  }

  long long val = read_int(&str, base, &success, flags.width);
  *str_ptr = str;

  if (success && !flags.asterisk) {
    if (flags.length == 'H')
      *(signed char *)va_arg(*args, int *) = (signed char)val;
    else if (flags.length == 'h')
      *(short int *)va_arg(*args, int *) = (short int)val;
    else if (flags.length == 'l')
      *(s21_size_t *)va_arg(*args, s21_size_t *) = (s21_size_t)val;
    else
      *(int *)va_arg(*args, int *) = (int)val;
    ret_val = 1;
  }

  return ret_val;
}

int handle_first_bracket(const char **str_ptr, char *dest, int *count,
                         int *first_bracket) {
  int ret_val = 0;
  const char *str = *str_ptr;

  if (*first_bracket && *count == 0) {
    if (*str == ']') {
      if (dest) dest[*count] = *str;
      (*count)++;
      (*str_ptr)++;
      *first_bracket = 0;
      ret_val = 1;
    } else {
      *first_bracket = 0;
    }
  }
  return ret_val;
}

int case_sqbr(const char **format_ptr, const char **str_ptr, va_list *args,
              scan_flags_t flags) {
  const char *format = *format_ptr;
  const char *str = *str_ptr;
  int inverted = 0;
  if (*(++format) == '^') {
    inverted = 1;
    format++;
  }
  int first_bracket = 0;
  int allowed[256] = {0};
  if (*format == ']') {
    first_bracket = 1;
    format++;
  }
  while (*format && *format != ']') {
    allowed[(unsigned char)*format] = 1;
    format++;
  }
  if (*format == ']') {
    format++;
  }
  int count = 0;
  char *dest = S21_NULL;
  if (!flags.asterisk) {
    dest = va_arg(*args, char *);
  }
  int max_chars = (flags.width == -1 ? INT_MAX : flags.width);
  while (*str) {
    if (handle_first_bracket(&str, dest, &count, &first_bracket)) continue;
    int in_set = allowed[(unsigned char)*str];
    if (inverted) in_set = !in_set;
    if (!in_set) break;
    if (count >= max_chars) break;
    if (dest) dest[count] = *str;
    count++;
    str++;
  }
  if (dest) dest[count] = '\0';
  *format_ptr = format;
  *str_ptr = str;
  return (count > 0 ? 1 : 0);
}

int case_u(const char **str_ptr, va_list *args, scan_flags_t flags) {
  int ret_val = 0;
  const char *str = *str_ptr;
  int success;
  s21_size_t val = (s21_size_t)read_int(&str, 10, &success, flags.width);

  if (success && !flags.asterisk) {
    if (flags.length == 'h') {
      *(unsigned short *)va_arg(*args, unsigned int *) = (unsigned short)val;
    } else if (flags.length == 'l') {
      *(unsigned long *)va_arg(*args, unsigned long *) = (unsigned long)val;
    } else {
      *(unsigned int *)va_arg(*args, unsigned int *) = (unsigned int)val;
    }
    ret_val = 1;
  }

  *str_ptr = str;
  return ret_val;
}

int case_x(const char **str_ptr, va_list *args, scan_flags_t flags) {
  int ret_val = 0;
  const char *str = *str_ptr;
  int success;
  s21_size_t val = (s21_size_t)read_int(&str, 16, &success, flags.width);

  if (success && !flags.asterisk) {
    if (flags.length == 'h') {
      *(unsigned short *)va_arg(*args, unsigned int *) = (unsigned short)val;
    } else if (flags.length == 'l') {
      *(unsigned long *)va_arg(*args, unsigned long *) = (unsigned long)val;
    } else {
      *(unsigned int *)va_arg(*args, unsigned int *) = (unsigned int)val;
    }
    ret_val = 1;
  }
  *str_ptr = str;
  return ret_val;
}

int case_o(const char **str_ptr, va_list *args, scan_flags_t flags) {
  int ret_val = 0;
  const char *str = *str_ptr;
  int success;
  s21_size_t val = (s21_size_t)read_int(&str, 8, &success, flags.width);

  if (success && !flags.asterisk) {
    if (flags.length == 'h') {
      *(unsigned short *)va_arg(*args, unsigned int *) = (unsigned short)val;
    } else if (flags.length == 'l') {
      *(unsigned long *)va_arg(*args, unsigned long *) = (unsigned long)val;
    } else {
      *(unsigned int *)va_arg(*args, unsigned int *) = (unsigned int)val;
    }
    ret_val = 1;
  }
  *str_ptr = str;
  return ret_val;
}

int case_f(const char **str_ptr, va_list *args, scan_flags_t flags) {
  int ret_val = 0;
  const char *str = *str_ptr;
  int success;
  long double val = read_float(&str, &success, flags.width);

  if (success && !flags.asterisk) {
    if (flags.length == 'L') {
      *(long double *)va_arg(*args, long double *) = val;
    } else if (flags.length == 'l') {
      *(double *)va_arg(*args, double *) = (double)val;
    } else {
      *(float *)va_arg(*args, float *) = (float)val;
    }
    ret_val = 1;
  }
  *str_ptr = str;
  return ret_val;
}

int case_c(const char **str_ptr, va_list *args, scan_flags_t flags) {
  int ret_val = 0;
  const char *str = *str_ptr;
  int n = (flags.width == -1 ? 1 : flags.width);

  if (!flags.asterisk) {
    char *dest = va_arg(*args, char *);
    for (int i = 0; i < n; i++) {
      dest[i] = *str;
      str++;
    }
    *str_ptr = str;
    ret_val = 1;
  } else {
    *str_ptr = str + n;
    ret_val = 0;
  }
  return ret_val;
}

int case_s(const char **str_ptr, va_list *args, scan_flags_t flags) {
  int ret_val = 0;
  const char *str = *str_ptr;
  int max_chars = (flags.width == -1) ? INT_MAX : flags.width;

  if (!flags.asterisk) {
    char *ptr = va_arg(*args, char *);
    int count = 0;
    while (*str && *str != ' ' && *str != '\t' && *str != '\n' &&
           count < max_chars) {
      *ptr++ = *str++;
      count++;
    }
    *ptr = '\0';
    *str_ptr = str;
    if (count > 0)
      ret_val = 1;
    else
      ret_val = 0;
  } else {
    int count = 0;
    while (*str && *str != ' ' && *str != '\t' && *str != '\n' &&
           count < max_chars) {
      str++;
      count++;
    }
    *str_ptr = str;
    ret_val = 0;
  }
  return ret_val;
}

int case_p(const char **str_ptr, va_list *args, scan_flags_t flags) {
  int ret_val = 0;
  const char *str = *str_ptr;
  int success;

  if (*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X')) {
    str += 2;
  }

  s21_size_t val = (s21_size_t)read_int(&str, 16, &success, flags.width);

  if (success && !flags.asterisk) {
    *(void **)va_arg(*args, void **) = (void *)val;
    *str_ptr = str;
    ret_val = 1;
  } else {
    *str_ptr = str;
    ret_val = 0;
  }
  return ret_val;
}

int handle_literal_or_space(const char **format, const char **str) {
  int ret_val = 0;
  if (**format != '%') {
    if (**format == ' ' || **format == '\t' || **format == '\n') {
      skip_spaces(str);
      (*format)++;
      ret_val = 1;
    } else if (*((*format)++) != *((*str)++)) {
      ret_val = 0;
    } else {
      ret_val = 1;
    }
  }
  return ret_val;
}

void handle_asterisk_flag(const char **format, scan_flags_t *flags) {
  if (**format == '*') {
    flags->asterisk = 1;
    (*format)++;
  }
}

void handle_width(const char **format, scan_flags_t *flags) {
  if (**format >= '0' && **format <= '9') {
    flags->width = 0;
    while (**format >= '0' && **format <= '9') {
      flags->width = flags->width * 10 + (**format - '0');
      (*format)++;
    }
  }
}

void handle_length_modifier(const char **format, scan_flags_t *flags) {
  if (**format == 'h') {
    if (*(*format + 1) == 'h') {
      flags->length = 'H';
      (*format) += 2;
    } else {
      flags->length = 'h';
      (*format)++;
    }
  } else if (**format == 'l' || **format == 'L') {
    flags->length = **format;
    (*format)++;
  }
}

void handle_scanf_format_specifier(const char **format, const char **str,
                                   const char *orig_str, va_list *args,
                                   scan_flags_t flags, int *items_read) {
  switch (**format) {
    case 'd':
      *items_read += case_d(str, args, flags);
      break;
    case 'i':
      *items_read += case_i(str, args, flags);
      break;
    case '[':
      *items_read += case_sqbr(format, str, args, flags);
      break;
    case 'u':
      *items_read += case_u(str, args, flags);
      break;
    case 'x':
    case 'X':
      *items_read += case_x(str, args, flags);
      break;
    case 'o':
      *items_read += case_o(str, args, flags);
      break;
    case 'f':
    case 'e':
    case 'E':
    case 'g':
    case 'G':
      *items_read += case_f(str, args, flags);
      break;
    case 'c':
      *items_read += case_c(str, args, flags);
      break;
    case 's':
      *items_read += case_s(str, args, flags);
      break;
    case 'p':
      *items_read += case_p(str, args, flags);
      break;
    case 'n':
      if (!flags.asterisk) {
        *(int *)va_arg(*args, int *) = (int)(*str - orig_str);
      }
      break;
    case '%':
      if (**str == '%') (*str)++;
      break;
  }
}

int s21_sscanf(const char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  int items_read = 0;
  scan_flags_t flags;
  int initial_input_empty = (*str == '\0');
  const char *orig_str = str;
  while (*format && *str) {
    if (handle_literal_or_space(&format, &str)) continue;
    format++;
    init_scan_flags(&flags);
    handle_asterisk_flag(&format, &flags);
    handle_width(&format, &flags);
    handle_length_modifier(&format, &flags);
    skip_spaces(&str);
    handle_scanf_format_specifier(&format, &str, orig_str, &args, flags,
                                  &items_read);
    format++;
  }

  va_end(args);
  if (initial_input_empty && items_read == 0) {
    return -1;
  }
  return items_read;
}

#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  char *ptr = (char *)str;
  void *res = s21_NULL;

  for (s21_size_t i = 0; (i < n) && ptr; i++) {
    if (*ptr == (char)c) {
      res = ptr;
      break;
    }

    ptr++;
  }

  return res;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  char *ptr1 = (char *)str1;
  char *ptr2 = (char *)str2;
  int cmp = 0;

  if (n) {
    while (*(char *)ptr1 == *(char *)ptr2 && --n) {
      ptr1 = (char *)ptr1 + 1;
      ptr2 = (char *)ptr2 + 1;
    }
    cmp = (*((unsigned char *)ptr1) - *((unsigned char *)ptr2));
  }

  return cmp;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *cdest = (char *)dest;
  const char *csrc = (char *)src;

  for (s21_size_t i = 0; i < n; ++i) {
    *cdest++ = *csrc++;
  }

  return dest;
}

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  void *ret = dest;

  if (dest <= src || (char *)dest >= ((char *)src + n)) {
    while (n--) {
      *(char *)dest = *(char *)src;
      dest = (char *)dest + 1;
      src = (char *)src + 1;
    }
  } else {
    dest = (char *)dest + n - 1;
    src = (char *)src + n - 1;
    while (n--) {
      *(char *)dest = *(char *)src;
      dest = (char *)dest - 1;
      src = (char *)src - 1;
    }
  }

  return ret;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *dest = str;

  while (n > 0) {
    *dest = (unsigned char)c;
    dest++;
    n--;
  }

  *dest = '\0';

  return str;
}

char *s21_strcat(char *dest, const char *src) {
  char *ptr = dest;

  while (*dest != '\0') {
    dest++;
  }

  while (*src != '\0') {
    *dest++ = *src++;
  }

  *dest = '\0';

  return ptr;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *ptr = dest;

  while (*dest != '\0') {
    dest++;
  }

  while (n > 0) {
    *dest++ = *src++;
    n--;
  }

  *dest = '\0';

  return ptr;
}

char *s21_strchr(const char *str, int c) {
  char *ptr = s21_NULL;
  int check = 1;

  while (*str && check) {
    if (*str == c) {
      ptr = (char *)str;
      check = 0;
    }
    str++;
  }

  if (c == '\0') {
    ptr = "";
  }

  return ptr;
}

int s21_strcmp(const char *str1, const char *str2) {
  int res = 0;

  if (str1 && str2) {
    int i = 0;

    while (str1[i] && str1[i] == str2[i]) {
      i++;
    }

    res = str1[i] - str2[i];
  }

  return res;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int res = 0;

  if (str1 && str2 && n > 0) {
    for (s21_size_t i = 0; i < n; i++) {
      if (str1[i] == '\0' || str1[i] != str2[i]) {
        res = str1[i] - str2[i];
        break;
      }
    }
  }

  return res;
}

char *s21_strcpy(char *dest, const char *src) {
  char *ptr = dest;

  while (*src != '\0') {
    *dest++ = *src++;
  }

  *dest = '\0';

  return ptr;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *ptr = dest;

  while (*src && n-- && (dest != s21_NULL)) {
    *dest++ = *src++;
  }

  *dest = '\0';

  return ptr;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t result = 0;
  s21_bool flag = false;

  for (; *str1; result++, str1++) {
    for (const char *dest = str2; *dest; dest++) {
      if (*str1 == *dest) {
        flag = true;
        break;
      }
    }
    if (flag == true) {
      break;
    }
  }

  return result;
}

char *s21_strerror(int errnum) {
  static char buff[BUFF_SIZE] = {'\0'};

  if (errnum >= 0 && errnum < ERROR_ARRAY_SIZE) {
    s21_strcpy(buff, errorArray[errnum]);
  } else {
#ifdef __APPLE__
    s21_sprintf(buff, "Unknown error: %d", errnum);
#endif
#ifdef __linux__
    s21_sprintf(buff, "Unknown error %d", errnum);
#endif
  }

  return buff;
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t count = 0;

  while (*str != '\0') {
    str++;
    count++;
  }

  return count;
}

const char *s21_strpbrk(const char *str1, const char *str2) {
  char *ptr = s21_NULL;

  for (const char *i = str1; *i; i++) {
    for (const char *j = str2; *j; j++) {
      if (*i == *j) {
        ptr = (char *)i;
        break;
      }
    }

    if (ptr != s21_NULL) {
      break;
    }
  }

  return ptr;
}

char *s21_strrchr(const char *str, int c) {
  char *ptr = (char *)str;

  for (; *ptr != '\0'; ptr++) {
  }
  s21_size_t i;
  for (i = s21_strlen(str) + 1; (*ptr != (unsigned char)c) && (i > 0);
       i--, ptr--) {
  }
  if (i == 0) {
    ptr = s21_NULL;
  }

  return ptr;
}

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t i;
  s21_bool flag = false;

  for (i = 0; str1[i] != '\0'; i++) {
    for (s21_size_t j = 0; str2[j] != str1[i]; j++) {
      if (str2[j] == '\0') {
        flag = true;
        break;
      }
    }
    if (flag == true) {
      break;
    }
  }

  return i;
}

const char *s21_strstr(const char *haystack, const char *needle) {
  char *hst = (char *)haystack;
  char *ndl = (char *)needle;
  char *res = s21_NULL;

  if (*ndl == '\0') {
    res = hst;
  }

  for (s21_size_t i = 0; i < s21_strlen(hst); i++) {
    if (hst[i] == *ndl) {
      char *tmp = &hst[i];
      int tmp_res = s21_strncmp(tmp, ndl, s21_strlen(ndl));
      if (tmp_res == 0) {
        res = &hst[i];
        break;
      }
    }
  }

  return res;
}

char *s21_strtok(char *str, const char *delim) {
  static char *s = s21_NULL;
  char *ret = s21_NULL;

  if (str != s21_NULL) {
    s = str;
  }

  if (s != s21_NULL && s21_strlen(s)) {
    const s21_size_t dlen = s21_strlen(delim);
    while (*s && s21_memchr(delim, *s, dlen) != s21_NULL) {
      ++s;
    }
    if (*s) {
      ret = s;
      while (*s) {
        if (s21_memchr(delim, *s, dlen) != s21_NULL) {
          break;
        } else {
          ++s;
        }
      }
      if (*s) {
        s[0] = 0;
        ++s;
      }
    }
  }

  return ret;
}

void *s21_to_upper(const char *str) {
  char *temp = s21_NULL;

  if (str != s21_NULL) {
    temp = calloc(s21_strlen(str) + 1, sizeof(char));
    s21_size_t i = 0;

    for (i = 0; i < s21_strlen(str); i++) {
      if (str[i] >= 'a' && str[i] <= 'z') {
        temp[i] = str[i] - 32;
      } else {
        temp[i] = str[i];
      }
    }

    temp[i] = '\0';
  }
  return temp;
}

void *s21_to_lower(const char *str) {
  char *temp = s21_NULL;

  if (str != s21_NULL) {
    temp = calloc(s21_strlen(str) + 1, sizeof(char));
    s21_size_t i = 0;

    for (i = 0; i < s21_strlen(str); i++) {
      if (str[i] >= 'A' && str[i] <= 'Z') {
        temp[i] = str[i] + 32;
      } else {
        temp[i] = str[i];
      }
    }

    temp[i] = '\0';
  }

  return temp;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *temp = s21_NULL;

  if (src != s21_NULL && str != s21_NULL) {
    if (start_index <= s21_strlen(src)) {
      temp =
          (char *)calloc((s21_strlen(str) + s21_strlen(src)), sizeof(char *));
      s21_strcpy(temp, src);
      s21_memmove(temp + start_index + s21_strlen(str), temp + start_index,
                  s21_strlen(src) - start_index + 1);
      s21_memcpy(temp + start_index, str, s21_strlen(str));
    }
  }

  return temp;
}

void *s21_trim(const char *src, const char *trim_chars) {
  char *res = s21_NULL;

  if (src) {
    if (trim_chars && *trim_chars) {
      s21_size_t len = s21_strlen(src);
      s21_size_t chars_len = s21_strlen(trim_chars);

      s21_trimLeft(&src, trim_chars, &len, chars_len);
      if (len) {
        s21_trimRight(&src, trim_chars, &len, chars_len);
      }

      res = (char *)calloc(sizeof(char) * (len + 1), sizeof(char *));

      for (s21_size_t i = 0; i < len + 1; i++) {
        if (i < len) {
          res[i] = src[i];
        } else {
          res[i] = '\0';
        }
      }
    } else {
      res = s21_trim(src, " \t\n");
    }
  }

  return res;
}

void s21_trimLeft(const char **src, const char *trim_chars, s21_size_t *src_len,
                  const s21_size_t trim_chars_len) {
  s21_size_t m = 0;

  while (src && m != trim_chars_len) {
    if ((**src) == trim_chars[m]) {
      (*src)++;
      (*src_len) -= 1;
      m = 0;
      continue;
    }
    m++;
  }
}

void s21_trimRight(const char **src, const char *trim_chars,
                   s21_size_t *src_len, const s21_size_t trim_chars_len) {
  s21_size_t m = 0;
  s21_size_t i = (*src_len) - 1;

  while (src && m != trim_chars_len) {
    if ((*src)[i] == trim_chars[m]) {
      i--;
      (*src_len)--;
      m = 0;
      continue;
    }

    m++;
  }
}
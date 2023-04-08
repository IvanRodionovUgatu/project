#include "cstring.h"
#include <cstddef>

size_t Strlen(const char* str) {
  size_t len = 0;
  while (*str++) {
    ++len;
  }
  return len;
}

int Strcmp(const char* first, const char* second) {
  while (*first && (*first == *second)) {
    ++first;
    ++second;
  }
  return *first - *second;
}

int Strncmp(const char* first, const char* second, size_t count) {
  if (count == 0) {
    return 0;
  }

  while (--count && *first && (*first == *second)) {
    ++first;
    ++second;
  }
  return *first - *second;
}

char* Strcpy(char* dest, const char* src) {
  char* result = dest;
  while (*src) {
    *dest++ = *src++;
  }
  *dest = '\0';
  return result;
}

char* Strncpy(char* dest, const char* src, size_t count) {
  char* result = dest;
  while (count && (*dest++ = *src++)) {
    --count;
  }
  if (count) {
    *dest = '\0';
  }
  return result;
}

char* Strcat(char* dest, const char* src) {
  char* result = dest;
  while (*dest) {
    ++dest;
  }
  while ((*dest++ = *src++)) {
    ;
  }
  return result;
}

char* Strncat(char* dest, const char* src, size_t count) {
  char* result = dest;
  while (*dest) {
    ++dest;
  }
  while (count-- && (*dest++ = *src++)) {
    ;
  }
  *dest = '\0';
  return result;
}

const char* Strchr(const char* str, char symbol) {
  while (*str) {
    if (*str == symbol) {
      return str;
    }
    ++str;
  }
  if (symbol == '\0') {
    return str;
  }
  return nullptr;
}

const char* Strrchr(const char* str, char symbol) {
  const char* last_occurrence = nullptr;
  while (*str) {
    if (*str == symbol) {
      last_occurrence = str;
    }
    ++str;
  }
  if (symbol == '\0') {
    return str;
  }
  return last_occurrence;
}

size_t Strspn(const char* dest, const char* src) {
  size_t count = 0;
  while (*dest && Strchr(src, *dest)) {
    ++count;
    ++dest;
  }
  return count;
}

size_t Strcspn(const char* dest, const char* src) {
  size_t count = 0;
  while (*dest && !Strchr(src, *dest)) {
    ++count;
    ++dest;
  }
  return count;
}

const char* Strpbrk(const char* dest, const char* breakset) {
  while (*dest) {
    if (Strchr(breakset, *dest)) {
      return dest;
    }
    ++dest;
  }
  return nullptr;
}

const char* Strstr(const char* str, const char* pattern) {
  size_t str_len = Strlen(str);
  size_t pattern_len = Strlen(pattern);

  if (pattern_len == 0) {
    return str;
  }

  for (size_t i = 0; i + pattern_len <= str_len; i++) {
    if (Strncmp(str + i, pattern, pattern_len) == 0) {
      return str + i;
    }
  }
  return nullptr;
}
#include <stdbool.h>

bool isInteger(char* str) {
  if (str == NULL || *str == '\0') {
    return false;
  }

  if (*str == '-' || *str == '+') {
    str++;
  }

  if (*str == '\0') {
    return false;
  }

  while (*str != '\0') {
    if (*str < '0' || *str > '9') {
      return false;
    }
    str++;
  }

  return true;
}
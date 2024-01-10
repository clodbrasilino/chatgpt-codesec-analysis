#include <stdbool.h>
 /* Possible weaknesses found:
  *  'NULL' is defined in header '<stddef.h>'; did you forget to '#include <stddef.h>'?
  */

bool isInteger(char* str) {
  /* Possible weaknesses found:
   *  each undeclared identifier is reported only once for each function it appears in
   *  'NULL' undeclared (first use in this function)
   */
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
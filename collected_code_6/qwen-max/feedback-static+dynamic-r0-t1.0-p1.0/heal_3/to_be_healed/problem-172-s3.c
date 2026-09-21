#include <stdio.h>
#include <stddef.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strstr'
  */

int count_occurrences(const char *str, const char *pattern) {
    int count = 0;
    size_t pattern_len = 0;
    const char *p = str;

    while (*pattern) {
        pattern_len++;
        pattern++;
    }

    if (pattern_len == 0) return 0;

    /* Possible weaknesses found:
     *  include the header <string.h> or explicitly provide a declaration for 'strstr'
     *  implicit declaration of function 'strstr' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strstr' with type 'char *(const char *, const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    while ((p = strstr(p, pattern - pattern_len)) != NULL) {
        count++;
        p += pattern_len;
    }
    return count;
}

int main() {
    const char *str = "1. list item 1. list item 1. list item 2. list item 2. list item 2. list item";
    const char *pattern = "std";
    int occurrences = count_occurrences(str, pattern);
    printf("The pattern '%s' occurs %d times.\n", pattern, occurrences);
    return 0;
}
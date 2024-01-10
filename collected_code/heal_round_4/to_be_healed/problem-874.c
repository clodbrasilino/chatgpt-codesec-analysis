#include <stdio.h>
#include <stdbool.h>
#include <string.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; did you forget to '#include <limits.h>'?
  */

bool checkConcatenation(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return false;
    }
    
    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  'INT_MAX' undeclared (first use in this function)
     */
    size_t len1 = strnlen(str1, INT_MAX);
    size_t len2 = strnlen(str2, INT_MAX);
    
    if (len1 % len2 != 0) {
        return false;
    }

    for (size_t i = 0; i < len1; i += len2) {
        if (strncmp(str1 + i, str2, len2) != 0) {
            return false;
        }
    }

    return true;
}

int main() {
    char str1[] = "abcabcabc";
    char str2[] = "abc";

    if (checkConcatenation(str1, str2)) {
        printf("String is a concatenation of another string\n");
    } else {
        printf("String is not a concatenation of another string\n");
    }

    return 0;
}
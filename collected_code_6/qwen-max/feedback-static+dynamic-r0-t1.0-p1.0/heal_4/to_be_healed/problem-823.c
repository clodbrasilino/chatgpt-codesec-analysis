#include <stdio.h>
#include <regex.h>
#include <stdbool.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  */

bool starts_with(const char *str, const char *prefix) {
    int ret;
    regex_t regex;

    /* Possible weaknesses found:
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     *  include the header <string.h> or explicitly provide a declaration for 'strlen'
     *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    size_t prefix_len = strlen(prefix);
    if (prefix_len >= 128) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char pattern[128];
    snprintf(pattern, sizeof(pattern), "^%.*s", (int)prefix_len, prefix);

    ret = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (ret) {
        return false;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);
    return !ret;
}

int main() {
    if (starts_with("hello world", "hello")) {
        printf("The string starts with the given substring.\n");
    } else {
        printf("The string does not start with the given substring.\n");
    }

    if (starts_with("hello world", "world")) {
        printf("The string starts with the given substring.\n");
    } else {
        printf("The string does not start with the given substring.\n");
    }

    return 0;
}
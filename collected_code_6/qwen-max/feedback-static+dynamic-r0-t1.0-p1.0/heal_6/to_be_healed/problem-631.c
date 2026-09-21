#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

void swap_whitespace_underscore(char *str, size_t len) {
    regex_t re;
    regmatch_t match;

    if (regcomp(&re, " ", REG_EXTENDED) != 0) return;

    char *new_str = (char *)malloc(len + 1);
    if (new_str == NULL) return;

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(new_str, str, len + 1);

    while (regexec(&re, new_str, 1, &match, 0) == 0) {
        memmove(new_str + match.rm_so + 1, new_str + match.rm_so, len - match.rm_so);
        new_str[match.rm_so] = '_';
        len++;
        new_str[len] = '\0';
    }
    regfree(&re);

    if (regcomp(&re, "_", REG_EXTENDED) != 0) return;
    while (regexec(&re, new_str, 1, &match, 0) == 0) {
        memmove(new_str + match.rm_so + 1, new_str + match.rm_so, len - match.rm_so);
        new_str[match.rm_so] = ' ';
        len++;
        new_str[len] = '\0';
    }
    regfree(&re);

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(str, new_str, len + 1);
    free(new_str);
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    ssize_t read_len;

    /* Possible weaknesses found:
     *  cannot take the address of an rvalue of type 'unsigned long'
     *  lvalue required as unary '&' operand
     *  passing argument 1 of 'getline' from incompatible pointer type [-Wincompatible-pointer-types]
     *  Variable 'read_len' is assigned a value that is never used. [unreadVariable]
     */
    if ((read_len = getline(&input, &sizeof(input), stdin)) != -1) {
        input[strcspn(input, "\n")] = 0;
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(input);
        if (len > 0 && len < sizeof(input) - 1) {
            swap_whitespace_underscore(input, len);
            printf("%s\n", input);
        }
    }
    return 0;
}
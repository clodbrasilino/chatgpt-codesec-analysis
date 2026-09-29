#include <stdio.h>
#include <string.h>
#include <regex.h>

void swap_whitespace_underscore(char *str) {
    regex_t re;
    if (regcomp(&re, " ", REG_EXTENDED) != 0) return;
    regmatch_t match;
    while (regexec(&re, str, 1, &match, 0) == 0) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        memmove(str + match.rm_so + 1, str + match.rm_so, strlen(str + match.rm_so) + 1);
        str[match.rm_so] = '_';
    }
    regfree(&re);

    if (regcomp(&re, "_", REG_EXTENDED) != 0) return;
    while (regexec(&re, str, 1, &match, 0) == 0) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        memmove(str + match.rm_so + 1, str + match.rm_so, strlen(str + match.rm_so) + 1);
        str[match.rm_so] = ' ';
    }
    regfree(&re);
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    if (fgets(input, 1024, stdin) != NULL) {
        input[strcspn(input, "\n")] = 0;
        swap_whitespace_underscore(input);
        printf("%s\n", input);
    }
    return 0;
}
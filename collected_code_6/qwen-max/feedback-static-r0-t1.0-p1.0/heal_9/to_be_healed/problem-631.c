#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>

void swap_whitespace_underscore(char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    regex_t re;
    if (regcomp(&re, " ", REG_EXTENDED) != 0) return;
    regmatch_t match;
    char *new_str = malloc(len + 1);
    if (new_str == NULL) return;
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(new_str, str);
    while (regexec(&re, new_str, 1, &match, 0) == 0 && match.rm_so < len) {
        memmove(new_str + match.rm_so + 1, new_str + match.rm_so, len - match.rm_so);
        new_str[match.rm_so] = '_';
        len++;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(str, new_str);
    free(new_str);
    regfree(&re);

    if (regcomp(&re, "_", REG_EXTENDED) != 0) return;
    new_str = malloc(len + 1);
    if (new_str == NULL) return;
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(new_str, str);
    while (regexec(&re, new_str, 1, &match, 0) == 0 && match.rm_so < len) {
        memmove(new_str + match.rm_so + 1, new_str + match.rm_so, len - match.rm_so);
        new_str[match.rm_so] = ' ';
        len++;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(str, new_str);
    free(new_str);
    regfree(&re);
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    if (fgets(input, sizeof(input), stdin) != NULL) {
        size_t len = strcspn(input, "\n");
        if (len >= 1023) {
            input[1023] = '\0';
            /* Possible weaknesses found:
             *  Value stored to 'len' is never read [deadcode.DeadStores]
             *  Variable 'len' is assigned a value that is never used. [unreadVariable]
             */
            len = 1023;
        } else {
            input[len] = '\0';
        }
        swap_whitespace_underscore(input);
        printf("%s\n", input);
    }
    return 0;
}
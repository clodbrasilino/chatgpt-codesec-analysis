#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>

void swap_whitespace_underscore(char *str) {
    size_t len = strnlen(str, 1024);
    regex_t re;
    if (regcomp(&re, " ", REG_EXTENDED) != 0) return;
    regmatch_t match;
    char *new_str = malloc(len + 1);
    if (new_str == NULL) return;
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(new_str, str, len + 1);

    while (regexec(&re, new_str, 1, &match, 0) == 0 && match.rm_so < len) {
        memmove(new_str + match.rm_so + 1, new_str + match.rm_so, len - match.rm_so);
        new_str[match.rm_so] = '_';
        len++;
    }
    snprintf(str, 1024, "%s", new_str);
    free(new_str);
    regfree(&re);

    if (regcomp(&re, "_", REG_EXTENDED) != 0) return;
    new_str = malloc(len + 1);
    if (new_str == NULL) return;
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(new_str, str, len + 1);

    while (regexec(&re, new_str, 1, &match, 0) == 0 && match.rm_so < len) {
        memmove(new_str + match.rm_so + 1, new_str + match.rm_so, len - match.rm_so);
        new_str[match.rm_so] = ' ';
        len++;
    }
    snprintf(str, 1024, "%s", new_str);
    free(new_str);
    regfree(&re);
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = '\0';
        swap_whitespace_underscore(input);
        printf("%s\n", input);
    }
    return 0;
}
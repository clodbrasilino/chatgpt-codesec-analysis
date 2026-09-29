#include <stdio.h>
#include <string.h>
#include <regex.h>

void swap_whitespace_underscore(char *str, size_t len) {
    regex_t re;
    if (regcomp(&re, " ", REG_EXTENDED) != 0) return;
    regmatch_t match;
    while (regexec(&re, str, 1, &match, 0) == 0 && match.rm_so < len) {
        memmove(str + match.rm_so + 1, str + match.rm_so, len - match.rm_so);
        str[match.rm_so] = '_';
        len += 1; // Adjust length after insertion
    }
    regfree(&re);

    if (regcomp(&re, "_", REG_EXTENDED) != 0) return;
    while (regexec(&re, str, 1, &match, 0) == 0 && match.rm_so < len) {
        memmove(str + match.rm_so + 1, str + match.rm_so, len - match.rm_so);
        str[match.rm_so] = ' ';
        len += 1; // Adjust length after insertion
    }
    regfree(&re);
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    if (fgets(input, sizeof(input), stdin) != NULL) {
        size_t len = strcspn(input, "\n");
        input[len] = 0;
        swap_whitespace_underscore(input, len);
        printf("%s\n", input);
    }
    return 0;
}
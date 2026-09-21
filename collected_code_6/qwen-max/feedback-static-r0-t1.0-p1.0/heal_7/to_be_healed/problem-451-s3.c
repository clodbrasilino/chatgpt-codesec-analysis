#include <stdio.h>
#include <string.h>
#include <regex.h>

void remove_whitespace(const char *input, char *output, size_t output_size) {
    regex_t regex;
    regmatch_t match;

    if (regcomp(&regex, "\\s", REG_EXTENDED|REG_NEWLINE)) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    const char *p = input;
    size_t len = 0;

    while (regexec(&regex, p, 1, &match, 0) == 0) {
        size_t copy_len = match.rm_so - (p - input);
        if (len + copy_len >= output_size - 1) {
            break;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(output + len, p, copy_len);
        len += copy_len;
        p += match.rm_eo;
    }

    size_t remaining = output_size - len - 1;
    if (remaining > 0) {
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(output + len, p, remaining);
        output[output_size - 1] = '\0';
    } else {
        output[output_size - 1] = '\0';
    }

    regfree(&regex);
}

int main() {
    const char *input = " This is a test string with  spaces. ";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[50];

    remove_whitespace(input, output, sizeof(output));
    printf("Result: '%s'\n", output);

    return 0;
}
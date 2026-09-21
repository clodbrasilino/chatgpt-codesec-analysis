#include <stdio.h>
#include <string.h>
#include <regex.h>

void remove_whitespace(const char *input, char *output, size_t output_size) {
    regex_t regex;
    regmatch_t match;
    int ret;

    if (regcomp(&regex, "\\s", REG_EXTENDED|REG_NEWLINE)) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    const char *p = input;
    size_t len = 0;

    /* Possible weaknesses found:
     *  Although the value stored to 'ret' is used in the enclosing expression, the value is never actually read from 'ret' [deadcode.DeadStores]
     */
    while ((ret = regexec(&regex, p, 1, &match, 0)) == 0) {
        size_t copy_len = match.rm_so - (p - input);
        if (len + copy_len >= output_size - 1) {
            break;
        }
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(output + len, p, copy_len);
        len += copy_len;
        p += match.rm_eo;
    }

    size_t remaining = output_size - 1 - len;
    if (remaining > 0) {
        /* Possible weaknesses found:
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
         */
        strncat(output + len, p, remaining - 1);
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
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

    while ((ret = regexec(&regex, input, 1, &match, 0)) == 0) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(input + match.rm_eo);
        memmove(input + match.rm_so, input + match.rm_eo, len + 1);
        input = input + match.rm_so;
    }

    if (ret != REG_NOMATCH) {
        regfree(&regex);
        fprintf(stderr, "Regex match failed\n");
        return;
    }

    snprintf(output, output_size, "%s", input);
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
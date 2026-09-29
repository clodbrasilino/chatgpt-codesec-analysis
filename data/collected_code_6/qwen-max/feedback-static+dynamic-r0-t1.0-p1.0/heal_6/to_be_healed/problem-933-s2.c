#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

void camel_to_snake(const char *input, char *output, size_t output_size) {
    regex_t regex;
    regmatch_t matches[2];
    if (regcomp(&regex, "([a-z])([A-Z])", REG_EXTENDED) != 0) {
        fprintf(stderr, "Failed to compile regex\n");
        exit(1);
    }

    size_t input_len = strnlen(input, output_size - 1);
    if (input_len + 1 > output_size) {
        snprintf(output, output_size, "%.*s", (int)(output_size - 1), input);
        output[output_size - 1] = '\0';
        goto cleanup;
    }
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(output, input, input_len);
    output[input_len] = '\0';

    int nmatches = 2;
    while (regexec(&regex, output, 2, matches, 0) == 0 && nmatches > 0) {
        size_t start = matches[1].rm_so;
        size_t end = strnlen((const char *)&output[start], output_size - start);
        memmove(&output[start + 2], &output[start + 1], end + 1);
        output[start + 1] = '_';
        nmatches = 2;
    }

    for (size_t i = 0; i < strnlen(output, output_size); ++i) {
        output[i] = tolower((unsigned char)output[i]);
    }

cleanup:
    regfree(&regex);
}

int main() {
    const char *input = "camelCaseExample";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[1024];

    camel_to_snake(input, output, sizeof(output));
    printf("%s\n", output);

    return 0;
}
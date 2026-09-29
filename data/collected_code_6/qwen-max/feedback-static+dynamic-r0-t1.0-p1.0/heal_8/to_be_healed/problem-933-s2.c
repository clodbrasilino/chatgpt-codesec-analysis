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
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(output, input, input_len + 1);

    int nmatches = 2;
    while (regexec(&regex, output, 2, matches, 0) == 0 && nmatches > 0) {
        size_t start = matches[1].rm_so;
        size_t end = strnlen(&output[start], output_size - start);
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
    size_t input_len = strnlen(input, 64);
    if (input_len == 64) {
        fprintf(stderr, "Input too long\n");
        return 1;
    }
    char *output = malloc(input_len + 1);
    if (!output) {
        fprintf(stderr, "Failed to allocate memory\n");
        return 1;
    }

    camel_to_snake(input, output, input_len + 1);
    printf("%s\n", output);

    free(output);
    return 0;
}
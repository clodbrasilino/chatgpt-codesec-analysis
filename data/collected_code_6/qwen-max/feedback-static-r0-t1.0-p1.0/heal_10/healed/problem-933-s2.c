#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

void camel_to_snake(const char *input, char *output, size_t output_size) {
    regex_t regex;
    regmatch_t matches[2];
    if (regcomp(&regex, "([a-z])([A-Z])", REG_EXTENDED) != 0) {
        fprintf(stderr, "Failed to compile regex\n");
        exit(1);
    }

    size_t input_len = strnlen(input, 1023);
    if (input_len == 0 || input_len >= 1023) {
        fprintf(stderr, "Input string is too long or empty\n");
        exit(1);
    }

    if (input_len + 1 > output_size) {
        fprintf(stderr, "Output buffer is too small\n");
        exit(1);
    }

    size_t copy_len = input_len < output_size - 1 ? input_len : output_size - 1;
    memmove(output, input, copy_len);
    output[copy_len] = '\0';

    int nmatches = 1;
    while (nmatches > 0) {
        nmatches = regexec(&regex, output, 2, matches, 0);
        if (nmatches > 0) {
            size_t insert_pos = matches[1].rm_so + 1;
            if (insert_pos < output_size - 1) {
                memmove(&output[insert_pos + 1], &output[insert_pos], output_size - insert_pos - 1);
                output[insert_pos] = '_';
                if (matches[1].rm_eo + 1 < output_size - 1 && output[matches[1].rm_eo + 1] != '\0') {
                    output[matches[1].rm_eo + 1] = tolower(output[matches[1].rm_eo + 1]);
                }
            }
        }
    }

    for (size_t i = 0; i < strnlen(output, 1023); ++i) {
        output[i] = tolower(output[i]);
    }

    regfree(&regex);
}

int main() {
    const char *input = "camelCaseExample";
    char output[1024];
    camel_to_snake(input, output, sizeof(output));
    printf("%s\n", output);
    return 0;
}
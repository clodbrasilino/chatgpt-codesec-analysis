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

    size_t input_len = strlen(input);
    if (input_len + 1 > output_size) {
        snprintf(output, output_size, "%.*s", (int)(output_size - 1), input);
        output[output_size - 1] = '\0';
        goto cleanup;
    }
    strncpy(output, input, output_size);
    output[input_len] = '\0';

    int nmatches = 1;
    while (nmatches > 0 && regexec(&regex, output, 2, matches, 0) == 0) {
        size_t start = matches[1].rm_so + 1;
        size_t end = strlen(&output[start]);
        memmove(&output[start + 1], &output[start], end);
        output[start] = '_';
        output[start + end + 1] = '\0';
    }

    for (size_t i = 0; i < strlen(output); ++i) {
        output[i] = tolower((unsigned char)output[i]);
    }

cleanup:
    regfree(&regex);
}

int main() {
    const char *input = "camelCaseExample";
    char output[1024];

    camel_to_snake(input, output, sizeof(output));
    printf("%s\n", output);

    return 0;
}
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

    /* Possible weaknesses found:
     *  Assignment 'nmatches=1', assigned value is 1
     */
    int nmatches = 1;
    /* Possible weaknesses found:
     *  Condition 'nmatches>0' is always true
     *  Condition 'nmatches>0' is always true [knownConditionTrueFalse]
     */
    while (nmatches > 0 && regexec(&regex, output, 2, matches, 0) == 0) {
        size_t start = matches[1].rm_so + 1;
        size_t end = strnlen(&output[start], output_size - start);
        memmove(&output[start + 1], &output[start], end);
        output[start] = '_';
        output[start + end + 1] = '\0';
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
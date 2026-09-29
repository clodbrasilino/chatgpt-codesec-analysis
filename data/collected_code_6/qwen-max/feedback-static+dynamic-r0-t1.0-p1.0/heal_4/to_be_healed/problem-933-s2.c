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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    if (input_len + 1 > output_size) {
        snprintf(output, output_size, "%.*s", (int)(output_size - 1), input);
        output[output_size - 1] = '\0';
        goto cleanup;
    }
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(output, input, output_size);
    output[input_len] = '\0';

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
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t end = strlen(&output[start]);
        memmove(&output[start + 1], &output[start], end);
        output[start] = '_';
        output[start + end + 1] = '\0';
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    for (size_t i = 0; i < strlen(output); ++i) {
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
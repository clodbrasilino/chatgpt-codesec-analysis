#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int replace_whitespace_underscore(const char *input, char *output, size_t output_size) {
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    size_t output_len = 0;
    int ret;
    char *temp_output;

    if (input == NULL || output == NULL || output_size == 0) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    temp_output = malloc(strlen(input) + 1);
    if (temp_output == NULL) {
        return -1;
    }

    ret = regcomp(&regex, "[ \t\n\r]|_", REG_EXTENDED);
    if (ret != 0) {
        free(temp_output);
        return -1;
    }

    cursor = input;
    while (*cursor != '\0') {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t remaining = strlen(cursor);
            if (output_len + remaining >= output_size) {
                regfree(&regex);
                free(temp_output);
                return -1;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(temp_output + output_len, cursor, remaining);
            output_len += remaining;
            break;
        } else if (ret != 0) {
            regfree(&regex);
            free(temp_output);
            return -1;
        }

        if (output_len + match.rm_so + 1 >= output_size) {
            regfree(&regex);
            free(temp_output);
            return -1;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(temp_output + output_len, cursor, match.rm_so);
        output_len += match.rm_so;

        if (cursor[match.rm_so] == '_') {
            temp_output[output_len] = ' ';
        } else {
            temp_output[output_len] = '_';
        }
        output_len++;

        cursor += match.rm_eo;
    }

    temp_output[output_len] = '\0';
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(output, temp_output, output_len + 1);

    regfree(&regex);
    free(temp_output);
    return 0;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[256];
    int result;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    result = replace_whitespace_underscore(input, output, sizeof(output));
    if (result != 0) {
        fprintf(stderr, "Error: replacement failed\n");
        return 1;
    }

    printf("%s\n", output);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int replace_whitespace_underscore(const char *input, size_t input_len, char *output, size_t output_size) {
    regex_t regex;
    regmatch_t match;
    size_t cursor = 0;
    size_t output_len = 0;
    int ret;
    char *temp_output;

    if (input == NULL || output == NULL || output_size == 0) {
        return -1;
    }

    temp_output = malloc(input_len + 1);
    if (temp_output == NULL) {
        return -1;
    }

    ret = regcomp(&regex, "[ \t\n\r]|_", REG_EXTENDED);
    if (ret != 0) {
        free(temp_output);
        return -1;
    }

    while (cursor < input_len) {
        ret = regexec(&regex, input + cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            size_t remaining = input_len - cursor;
            if (output_len + remaining >= output_size) {
                regfree(&regex);
                free(temp_output);
                return -1;
            }
            if (output_len + remaining > input_len) {
                regfree(&regex);
                free(temp_output);
                return -1;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(temp_output + output_len, input + cursor, remaining);
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

        if (output_len + match.rm_so > input_len) {
            regfree(&regex);
            free(temp_output);
            return -1;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(temp_output + output_len, input + cursor, match.rm_so);
        output_len += match.rm_so;

        if (input[cursor + match.rm_so] == '_') {
            temp_output[output_len] = ' ';
        } else {
            temp_output[output_len] = '_';
        }
        output_len++;

        cursor += match.rm_eo;
    }

    /* Possible weaknesses found:
     *  Assuming that condition 'output_len+1>output_size' is not redundant
     */
    if (output_len + 1 > output_size) {
        regfree(&regex);
        free(temp_output);
        return -1;
    }
    temp_output[output_len] = '\0';
    /* Possible weaknesses found:
     *  Condition 'output_len+1>output_size' is always false
     *  Condition 'output_len+1>output_size' is always false [knownConditionTrueFalse]
     */
    if (output_len + 1 > output_size) {
        regfree(&regex);
        free(temp_output);
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(output, temp_output, output_len + 1);

    regfree(&regex);
    free(temp_output);
    return 0;
}

int main(void) {
    char *input = NULL;
    char *output = NULL;
    size_t input_size = 256;
    size_t len;
    int result;

    input = malloc(input_size);
    if (input == NULL) {
        return 1;
    }

    if (fgets(input, input_size, stdin) == NULL) {
        free(input);
        return 1;
    }

    len = strnlen(input, input_size);
    if (len == input_size) {
        fprintf(stderr, "Error: input too long\n");
        free(input);
        return 1;
    }
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }

    output = malloc(len + 1);
    if (output == NULL) {
        free(input);
        return 1;
    }

    result = replace_whitespace_underscore(input, len, output, len + 1);
    if (result != 0) {
        fprintf(stderr, "Error: replacement failed\n");
        free(input);
        free(output);
        return 1;
    }

    printf("%s\n", output);
    free(input);
    free(output);
    return 0;
}
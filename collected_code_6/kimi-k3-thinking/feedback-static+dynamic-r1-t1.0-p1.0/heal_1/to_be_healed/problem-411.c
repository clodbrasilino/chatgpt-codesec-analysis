#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'GooglePixel', got <no output>
  *  test case 0 failed: expected 'AndroidTv', got <no output>
  *  test case 2 failed: expected 'AppleWatch', got <no output>
  */

char *snake_to_camel(const char *input)
{
    regex_t regex;
    regmatch_t match[2];
    char *result;
    size_t input_len;
    size_t result_idx = 0;
    size_t pos = 0;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_len = strlen(input);

    result = malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "_([a-zA-Z0-9])", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return NULL;
    }

    while (pos < input_len) {
        ret = regexec(&regex, input + pos, 2, match, 0);
        if (ret == REG_NOMATCH) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_idx, input + pos, input_len - pos);
            result_idx += input_len - pos;
            pos = input_len;
        } else if (ret != 0) {
            regfree(&regex);
            free(result);
            return NULL;
        } else {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_idx, input + pos, (size_t)match[0].rm_so);
            result_idx += (size_t)match[0].rm_so;
            result[result_idx] = (char)toupper((unsigned char)input[pos + (size_t)match[1].rm_so]);
            result_idx++;
            pos += (size_t)match[0].rm_eo;
        }
    }

    result[result_idx] = '\0';
    regfree(&regex);
    return result;
}

int main(void)
{
    const char *input = "convert_snake_case_to_camel_case";
    char *output;

    output = snake_to_camel(input);
    if (output == NULL) {
        fprintf(stderr, "Error: conversion failed\n");
        return EXIT_FAILURE;
    }

    printf("Snake case: %s\n", input);
    printf("Camel case: %s\n", output);

    free(output);
    return EXIT_SUCCESS;
}
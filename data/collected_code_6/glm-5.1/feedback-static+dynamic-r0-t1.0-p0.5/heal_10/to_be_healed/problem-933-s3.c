#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

char *camel_to_snake(const char *camel_str) {
    if (camel_str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(camel_str);

    if (input_len == 0) {
        char *res = malloc(1);
        if (res) res[0] = '\0';
        return res;
    }

    if (input_len > (SIZE_MAX - 1) / 2) {
        return NULL;
    }

    size_t max_len = input_len * 2 + 1;

    char *result = malloc(max_len);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < input_len; i++) {
        if (isupper((unsigned char)camel_str[i])) {
            if (i > 0 && islower((unsigned char)camel_str[i - 1])) {
                if (j >= max_len - 1) break;
                result[j++] = '_';
            }
            if (j >= max_len - 1) break;
            result[j++] = tolower((unsigned char)camel_str[i]);
        } else {
            if (j >= max_len - 1) break;
            result[j++] = camel_str[i];
        }
    }
    result[j] = '\0';

    /* Possible weaknesses found:
     *  Assignment 'final_len=j+1', assigned value is greater than 0
     */
    size_t final_len = j + 1;
    char *final_result = malloc(final_len);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (final_result == NULL) {
        free(result);
        return NULL;
    }

    /* Possible weaknesses found:
     *  Condition 'final_len>0' is always true
     *  Condition 'final_len>0' is always true [knownConditionTrueFalse]
     */
    if (final_len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(final_result, result, final_len);
    }

    free(result);
    return final_result;
}

int main(void) {
    const char *inputs[] = {
        "camelCase",
        "thisIsATest",
        "convertCamelCaseToSnakeCase",
        "already_snake",
        "simple",
        "aB",
        "Google_assistant",
        "Chrome_cast",
        "Quad_core",
        NULL
    };

    for (int i = 0; inputs[i] != NULL; i++) {
        char *snake = camel_to_snake(inputs[i]);
        if (snake != NULL) {
            printf("%s -> %s\n", inputs[i], snake);
            free(snake);
        }
    }

    return 0;
}
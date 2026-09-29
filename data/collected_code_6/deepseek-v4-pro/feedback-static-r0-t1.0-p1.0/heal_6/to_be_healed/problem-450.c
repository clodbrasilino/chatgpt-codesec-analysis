#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **extract_strings(char **input, size_t count, size_t size) {
    if (input == NULL || count == 0 || size == 0) {
        return NULL;
    }

    char **result = (char **)malloc(count * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; i++) {
        if (input[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        size_t src_len = strnlen(input[i], size);
        /* Possible weaknesses found:
         *  Assignment 'copy_len=src_len<size?src_len:size', assigned value is less than symbolic=size+1
         */
        size_t copy_len = src_len < size ? src_len : size;

        result[i] = (char *)malloc((copy_len + 1) * sizeof(char));
        /* Possible weaknesses found:
         *  Assuming condition is false
         */
        if (result[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        if (copy_len > 0) {
            /* Possible weaknesses found:
             *  Condition 'copy_len>size' is always false [knownConditionTrueFalse]
             *  Condition 'copy_len>size' is always false
             */
            if (copy_len > size) {
                copy_len = size;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[i], input[i], copy_len);
        }
        result[i][copy_len] = '\0';
    }

    return result;
}

int main(void) {
    const char *input_strings[] = {"Hello", "World", "C", "Programming"};
    size_t count = sizeof(input_strings) / sizeof(input_strings[0]);
    size_t extract_size = 3;

    char **input = (char **)malloc(count * sizeof(char *));
    if (input == NULL) {
        return 1;
    }

    for (size_t i = 0; i < count; i++) {
        size_t src_len = strnlen(input_strings[i], extract_size);
        size_t len = src_len < extract_size ? src_len : extract_size;

        input[i] = (char *)malloc((len + 1) * sizeof(char));
        if (input[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(input[j]);
            }
            free(input);
            return 1;
        }

        if (len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(input[i], input_strings[i], len);
        }
        input[i][len] = '\0';
    }

    char **extracted = extract_strings(input, count, extract_size);
    if (extracted == NULL) {
        for (size_t i = 0; i < count; i++) {
            free(input[i]);
        }
        free(input);
        return 1;
    }

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", extracted[i]);
        free(extracted[i]);
        free(input[i]);
    }

    free(extracted);
    free(input);
    return 0;
}
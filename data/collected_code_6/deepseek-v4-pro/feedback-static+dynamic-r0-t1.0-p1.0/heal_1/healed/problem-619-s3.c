#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *move_numbers_to_string(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t max_len = 0;
    const char *ptr = input;
    while (*ptr != '\0') {
        max_len++;
        ptr++;
        if (max_len > 1000000) {
            return NULL;
        }
    }

    char *result = (char *)malloc(max_len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t result_index = 0;
    for (size_t i = 0; i < max_len; i++) {
        if (isdigit((unsigned char)input[i])) {
            result[result_index++] = input[i];
        }
    }
    result[result_index] = '\0';

    char *final_result = (char *)realloc(result, result_index + 1);
    if (final_result == NULL) {
        free(result);
        return NULL;
    }

    return final_result;
}

int main(void) {
    const char *test_string = "a1b2c3d4e5";
    char *numbers = move_numbers_to_string(test_string);

    if (numbers != NULL) {
        printf("Numbers: %s\n", numbers);
        free(numbers);
    } else {
        printf("Memory allocation failed or input is NULL\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
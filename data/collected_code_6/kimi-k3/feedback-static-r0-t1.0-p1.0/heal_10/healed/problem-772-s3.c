#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdint.h>

char *remove_k_length_words(const char *str, size_t k) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (len < SIZE_MAX - 1 && str[len] != '\0') {
        len++;
    }

    if (len == SIZE_MAX - 1 && str[len] != '\0') {
        return NULL;
    }

    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;

    while (i < len) {
        while (i < len && isspace((unsigned char)str[i])) {
            i++;
        }

        if (i >= len) {
            break;
        }

        size_t word_start = i;
        while (i < len && !isspace((unsigned char)str[i])) {
            i++;
        }

        size_t word_len = i - word_start;

        if (word_len != k) {
            if (j > 0) {
                if (j >= len) {
                    free(result);
                    return NULL;
                }
                result[j++] = ' ';
            }

            if (word_len > len - j) {
                free(result);
                return NULL;
            }

            if (word_len > 0) {
                if (j + word_len > len) {
                    free(result);
                    return NULL;
                }
                if (word_len <= len - j) {
                    memcpy(result + j, str + word_start, word_len);
                    j += word_len;
                }
            }
        }
    }

    result[j] = '\0';

    char *final_result = (char *)realloc(result, j + 1);
    if (final_result == NULL) {
        return result;
    }

    return final_result;
}

int main(void) {
    char *input = NULL;
    size_t input_capacity = 0;
    size_t input_len = 0;
    size_t k;

    printf("Enter a string: ");

    input_capacity = 128;
    input = (char *)malloc(input_capacity);
    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    int c;
    while ((c = getchar()) != EOF && c != '\n') {
        if (input_len >= input_capacity - 1) {
            size_t new_capacity = input_capacity * 2;
            if (new_capacity < input_capacity || new_capacity > SIZE_MAX / 2) {
                free(input);
                fprintf(stderr, "Input too long\n");
                return EXIT_FAILURE;
            }
            char *new_input = (char *)realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                fprintf(stderr, "Memory allocation failed\n");
                return EXIT_FAILURE;
            }
            input = new_input;
            input_capacity = new_capacity;
        }
        input[input_len++] = (char)c;
    }
    input[input_len] = '\0';

    printf("Enter the word length to remove: ");
    if (scanf("%zu", &k) != 1) {
        fprintf(stderr, "Invalid input for k\n");
        free(input);
        return EXIT_FAILURE;
    }

    char *result = remove_k_length_words(input, k);
    free(input);

    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Result: \"%s\"\n", result);

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}
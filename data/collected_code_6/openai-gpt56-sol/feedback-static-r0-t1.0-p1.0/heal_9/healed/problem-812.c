#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *abbreviate_road(const char *input, size_t input_len)
{
    static const char target[] = "road";
    static const char replacement[] = "rd.";
    const size_t target_len = sizeof target - 1;
    const size_t replacement_len = sizeof replacement - 1;
    const size_t reduction = target_len - replacement_len;
    size_t occurrences = 0;
    size_t output_len;
    size_t i = 0;
    size_t j = 0;
    char *output;

    if (input == NULL) {
        return NULL;
    }

    while (i < input_len) {
        if (input_len - i >= target_len &&
            memcmp(input + i, target, target_len) == 0) {
            occurrences++;
            i += target_len;
        } else {
            i++;
        }
    }

    if (occurrences > input_len / reduction) {
        return NULL;
    }

    output_len = input_len - occurrences * reduction;

    if (output_len == SIZE_MAX) {
        return NULL;
    }

    output = malloc(output_len + 1);
    if (output == NULL) {
        return NULL;
    }

    i = 0;

    while (i < input_len) {
        if (input_len - i >= target_len &&
            memcmp(input + i, target, target_len) == 0) {
            if (j > output_len || replacement_len > output_len - j) {
                free(output);
                return NULL;
            }

            memcpy(output + j, replacement, replacement_len);
            i += target_len;
            j += replacement_len;
        } else {
            if (j >= output_len) {
                free(output);
                return NULL;
            }

            output[j++] = input[i++];
        }
    }

    if (j != output_len) {
        free(output);
        return NULL;
    }

    output[j] = '\0';
    return output;
}

int main(void)
{
    char *input = NULL;
    char *result;
    size_t capacity = 0;
    size_t length = 0;
    int ch = EOF;

    for (;;) {
        ch = getchar();

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (length > SIZE_MAX - 2) {
            free(input);
            return EXIT_FAILURE;
        }

        if (capacity - length < 2) {
            size_t required = length + 2;
            size_t new_capacity;
            char *temporary;

            if (capacity == 0) {
                new_capacity = 128;
            } else if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            temporary = realloc(input, new_capacity);
            if (temporary == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = temporary;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (ch == EOF && length == 0) {
        free(input);
        return EXIT_SUCCESS;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            return EXIT_FAILURE;
        }
        capacity = 1;
    }

    if (length >= capacity) {
        free(input);
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    result = abbreviate_road(input, length);
    free(input);

    if (result == NULL) {
        return EXIT_FAILURE;
    }

    if (fputs(result, stdout) == EOF || fputc('\n', stdout) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
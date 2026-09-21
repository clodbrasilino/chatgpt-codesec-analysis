#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *abbreviate_road(const char *input, size_t input_len, size_t *result_len)
{
    static const char target[] = "road";
    static const char replacement[] = "rd.";
    const size_t target_len = sizeof(target) - 1;
    const size_t replacement_len = sizeof(replacement) - 1;
    const size_t decrease = target_len - replacement_len;
    size_t occurrences = 0;
    size_t output_len;
    size_t source_index = 0;
    size_t destination_index = 0;
    char *output;

    if (result_len == NULL || (input == NULL && input_len != 0)) {
        return NULL;
    }

    *result_len = 0;

    for (size_t i = 0; i < input_len;) {
        if (input_len - i >= target_len &&
            memcmp(input + i, target, target_len) == 0) {
            occurrences++;
            i += target_len;
        } else {
            i++;
        }
    }

    if (occurrences > input_len / target_len ||
        occurrences > input_len / decrease) {
        return NULL;
    }

    output_len = input_len - occurrences * decrease;

    if (output_len == SIZE_MAX) {
        return NULL;
    }

    output = malloc(output_len + 1);
    if (output == NULL) {
        return NULL;
    }

    while (source_index < input_len) {
        if (input_len - source_index >= target_len &&
            memcmp(input + source_index, target, target_len) == 0) {
            if (destination_index > output_len ||
                replacement_len > output_len - destination_index) {
                free(output);
                return NULL;
            }

            memcpy(output + destination_index, replacement, replacement_len);
            source_index += target_len;
            destination_index += replacement_len;
        } else {
            if (destination_index >= output_len) {
                free(output);
                return NULL;
            }

            output[destination_index++] = input[source_index++];
        }
    }

    if (destination_index != output_len) {
        free(output);
        return NULL;
    }

    output[output_len] = '\0';
    *result_len = output_len;
    return output;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    size_t result_len = 0;
    char *result;
    int ch;

    while ((ch = getchar()) != EOF && ch != '\n') {
        if (length == capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            if (new_capacity <= length) {
                free(input);
                return EXIT_FAILURE;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length == 0 && ch == EOF) {
        free(input);
        return EXIT_SUCCESS;
    }

    result = abbreviate_road(input, length, &result_len);
    free(input);

    if (result == NULL) {
        return EXIT_FAILURE;
    }

    if ((result_len > 0 &&
         fwrite(result, 1, result_len, stdout) != result_len) ||
        fputc('\n', stdout) == EOF ||
        fflush(stdout) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}
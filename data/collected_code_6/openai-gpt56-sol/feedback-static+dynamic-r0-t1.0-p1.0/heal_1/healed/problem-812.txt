#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *abbreviate_road(const char *input, size_t input_len)
{
    static const char target[] = "road";
    static const char replacement[] = "rd.";
    const size_t target_len = sizeof(target) - 1;
    const size_t replacement_len = sizeof(replacement) - 1;
    size_t occurrences = 0;
    size_t output_len;
    size_t source_index = 0;
    size_t destination_index = 0;
    char *output;

    if (input == NULL) {
        return NULL;
    }

    for (size_t i = 0; i + target_len <= input_len;) {
        if (memcmp(input + i, target, target_len) == 0) {
            ++occurrences;
            i += target_len;
        } else {
            ++i;
        }
    }

    if (occurrences > input_len / (target_len - replacement_len)) {
        return NULL;
    }

    output_len = input_len -
                 occurrences * (target_len - replacement_len);

    if (output_len == SIZE_MAX) {
        return NULL;
    }

    output = malloc(output_len + 1);
    if (output == NULL) {
        return NULL;
    }

    while (source_index < input_len) {
        if (source_index + target_len <= input_len &&
            memcmp(input + source_index, target, target_len) == 0) {
            memcpy(output + destination_index,
                   replacement,
                   replacement_len);
            source_index += target_len;
            destination_index += replacement_len;
        } else {
            output[destination_index++] = input[source_index++];
        }
    }

    output[destination_index] = '\0';
    return output;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    char *result;
    int ch;

    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
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

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length == 0 && ch == EOF) {
        free(input);
        return EXIT_SUCCESS;
    }

    result = abbreviate_road(input, length);
    free(input);

    if (result == NULL) {
        return EXIT_FAILURE;
    }

    if (fwrite(result, 1, strlen(result), stdout) != strlen(result) ||
        fputc('\n', stdout) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_multiple_spaces(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = strlen(input);
    char* result = malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t read_pos = 0;
    size_t write_pos = 0;
    int prev_was_space = 0;

    while (read_pos < input_len) {
        if (input[read_pos] == ' ') {
            if (!prev_was_space) {
                result[write_pos++] = ' ';
                prev_was_space = 1;
            }
        } else {
            result[write_pos++] = input[read_pos];
            prev_was_space = 0;
        }
        read_pos++;
    }
    result[write_pos] = '\0';

    char* temp = realloc(result, write_pos + 1);
    if (temp != NULL) {
        result = temp;
    }

    return result;
}

int main(void) {
    const char* test_strings[] = {
        "Google Assistant",
        "Quad Core",
        "ChromeCast Built-in",
        "This   is    a     test    string   with    multiple     spaces."
    };
    int num_tests = 4;

    for (int i = 0; i < num_tests; i++) {
        char* cleaned_string = remove_multiple_spaces(test_strings[i]);

        if (cleaned_string == NULL) {
            fprintf(stderr, "Error: Failed to process string\n");
            return EXIT_FAILURE;
        }

        printf("%s\n", cleaned_string);

        free(cleaned_string);
    }

    return EXIT_SUCCESS;
}
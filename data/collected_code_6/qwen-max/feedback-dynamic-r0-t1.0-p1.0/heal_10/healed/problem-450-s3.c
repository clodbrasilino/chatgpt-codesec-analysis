#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** extract_strings(const char* const strings[], size_t num_strings, size_t max_size, size_t* out_num_strings) {
    if (strings == NULL || num_strings == 0 || max_size == 0) {
        *out_num_strings = 0;
        return NULL;
    }

    char** result = (char**)malloc(num_strings * sizeof(char*));
    if (result == NULL) {
        *out_num_strings = 0;
        return NULL;
    }

    *out_num_strings = 0;

    for (size_t i = 0; i < num_strings; ++i) {
        if (strings[i] != NULL) {
            size_t str_len = strlen(strings[i]);
            if (str_len > 0 && str_len <= max_size) {
                result[*out_num_strings] = (char*)malloc((str_len + 1) * sizeof(char));
                if (result[*out_num_strings] == NULL) {
                    for (size_t j = 0; j < *out_num_strings; ++j) {
                        free(result[j]);
                    }
                    free(result);
                    *out_num_strings = 0;
                    return NULL;
                }
                strncpy(result[*out_num_strings], strings[i], str_len + 1);
                (*out_num_strings)++;
            }
        }
    }

    return result;
}

int main() {
    const char* const input_strings[] = {"practice", "solution", "Python", "exercises"};
    size_t num_input_strings = sizeof(input_strings) / sizeof(input_strings[0]);
    size_t max_size = 5;
    size_t num_output_strings;

    char** output_strings = extract_strings(input_strings, num_input_strings, max_size, &num_output_strings);

    if (output_strings != NULL) {
        for (size_t i = 0; i < num_output_strings; ++i) {
            printf("%s\n", output_strings[i]);
            free(output_strings[i]);
        }
        free(output_strings);
    }

    return 0;
}
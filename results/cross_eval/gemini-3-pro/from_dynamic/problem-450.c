#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *copy_string(const char *src) {
    size_t len;
    char *dest;

    if (src == NULL) {
        return NULL;
    }

    len = strlen(src);
    dest = (char *)malloc(len + 1);
    if (dest != NULL) {
        memcpy(dest, src, len + 1);
    }

    return dest;
}

char **extract_strings_by_length(const char **input_list, size_t input_count, size_t target_length, size_t *output_count) {
    size_t match_count = 0;
    char **extracted_list = NULL;
    size_t current_index = 0;

    if (input_list == NULL || output_count == NULL) {
        if (output_count != NULL) {
            *output_count = 0;
        }
        return NULL;
    }

    *output_count = 0;

    for (size_t i = 0; i < input_count; i++) {
        if (input_list[i] != NULL && strlen(input_list[i]) == target_length) {
            match_count++;
        }
    }

    if (match_count == 0) {
        return NULL;
    }

    extracted_list = (char **)malloc(match_count * sizeof(char *));
    if (extracted_list == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < input_count; i++) {
        if (input_list[i] != NULL && strlen(input_list[i]) == target_length) {
            extracted_list[current_index] = copy_string(input_list[i]);
            if (extracted_list[current_index] == NULL) {
                for (size_t j = 0; j < current_index; j++) {
                    free(extracted_list[j]);
                }
                free(extracted_list);
                return NULL;
            }
            current_index++;
        }
    }

    *output_count = match_count;
    return extracted_list;
}

void free_string_list(char **list, size_t count) {
    if (list == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(list[i]);
    }
    free(list);
}

int main(void) {
    const char *input_strings[] = {
        "apple",
        "cat",
        "banana",
        "dog",
        "elephant",
        "bat",
        NULL
    };
    
    size_t input_count = 6;
    size_t target_length = 3;
    size_t output_count = 0;

    char **result = extract_strings_by_length(input_strings, input_count, target_length, &output_count);

    if (result != NULL) {
        for (size_t i = 0; i < output_count; i++) {
            printf("%s\n", result[i]);
        }
        free_string_list(result, output_count);
    }

    return 0;
}
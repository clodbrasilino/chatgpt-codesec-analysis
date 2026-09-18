#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void free_extracted_strings(char **array, size_t size) {
    if (!array) {
        return;
    }
    for (size_t i = 0; i < size; i++) {
        free(array[i]);
    }
    free(array);
}

char **extract_strings_by_length(const char * const *list, size_t list_size, size_t target_len, size_t *out_size) {
    if (!list || !out_size) {
        return NULL;
    }

    size_t match_count = 0;
    for (size_t i = 0; i < list_size; i++) {
        if (list[i] != NULL && strlen(list[i]) == target_len) {
            match_count++;
        }
    }

    *out_size = match_count;
    if (match_count == 0) {
        return NULL;
    }

    char **result = (char **)malloc(match_count * sizeof(char *));
    if (!result) {
        *out_size = 0;
        return NULL;
    }

    size_t result_idx = 0;
    for (size_t i = 0; i < list_size; i++) {
        if (list[i] != NULL && strlen(list[i]) == target_len) {
            result[result_idx] = (char *)malloc((target_len + 1) * sizeof(char));
            if (!result[result_idx]) {
                free_extracted_strings(result, result_idx);
                *out_size = 0;
                return NULL;
            }
            memcpy(result[result_idx], list[i], target_len + 1);
            result_idx++;
        }
    }

    return result;
}

int main(void) {
    const char * const input_list[] = {
        "apple",
        "cat",
        "banana",
        "dog",
        "elephant",
        "fox"
    };
    
    size_t input_size = sizeof(input_list) / sizeof(input_list[0]);
    size_t target_length = 3;
    size_t extracted_size = 0;

    char **extracted_list = extract_strings_by_length(input_list, input_size, target_length, &extracted_size);

    if (extracted_list != NULL) {
        for (size_t i = 0; i < extracted_size; i++) {
            printf("%s\n", extracted_list[i]);
        }
        free_extracted_strings(extracted_list, extracted_size);
    }

    return 0;
}
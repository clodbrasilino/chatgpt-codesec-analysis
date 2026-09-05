#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** extract_substrings(char** strings, int count, int size) {
    if (strings == NULL || count <= 0 || size < 0) {
        return NULL;
    }

    int result_count = 0;
    int* valid_lengths = (int*)malloc(count * sizeof(int));
    if (valid_lengths == NULL) {
        return NULL;
    }

    for (int i = 0; i < count; i++) {
        if (strings[i] != NULL) {
            int len = strlen(strings[i]);
            if (len < size) {
                valid_lengths[result_count] = len;
                result_count++;
            }
        }
    }

    if (result_count == 0) {
        free(valid_lengths);
        char** empty_result = (char**)malloc(sizeof(char*));
        if (empty_result) {
            empty_result[0] = NULL;
        }
        return empty_result;
    }

    char** result = (char**)malloc((result_count + 1) * sizeof(char*));
    if (result == NULL) {
        free(valid_lengths);
        return NULL;
    }

    int res_idx = 0;
    for (int i = 0; i < count; i++) {
        if (strings[i] != NULL) {
            int len = strlen(strings[i]);
            if (len < size) {
                result[res_idx] = (char*)malloc(len + 1);
                if (result[res_idx] == NULL) {
                    for (int j = 0; j < res_idx; j++) {
                        free(result[j]);
                    }
                    free(result);
                    free(valid_lengths);
                    return NULL;
                }
                strcpy(result[res_idx], strings[i]);
                res_idx++;
            }
        }
    }

    result[res_idx] = NULL;
    free(valid_lengths);
    return result;
}

void free_extracted_strings(char** strings) {
    if (strings == NULL) {
        return;
    }
    for (int i = 0; strings[i] != NULL; i++) {
        free(strings[i]);
    }
    free(strings);
}

int main() {
    char* input_strings[] = {
        "Python",
        "list",
        "exercises",
        "practice",
        "solution",
        NULL
    };

    int count = 0;
    while (input_strings[count] != NULL) {
        count++;
    }

    int extract_size = 8;

    char** extracted = extract_substrings(input_strings, count, extract_size);
    if (extracted == NULL) {
        return EXIT_FAILURE;
    }

    for (int i = 0; extracted[i] != NULL; i++) {
        printf("%s\n", extracted[i]);
    }

    free_extracted_strings(extracted);

    return EXIT_SUCCESS;
}
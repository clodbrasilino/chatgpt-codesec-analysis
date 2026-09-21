#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** extract_strings(char** input_list, int list_size, size_t target_length, int* out_count) {
    if (input_list == NULL || out_count == NULL || list_size <= 0) {
        if (out_count != NULL) {
            *out_count = 0;
        }
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < list_size; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (input_list[i] != NULL && strlen(input_list[i]) == target_length) {
            count++;
        }
    }

    *out_count = count;
    if (count == 0) {
        return NULL;
    }

    char** result = (char**)malloc(count * sizeof(char*));
    if (result == NULL) {
        *out_count = 0;
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < list_size; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (input_list[i] != NULL && strlen(input_list[i]) == target_length) {
            result[index] = strdup(input_list[i]);
            if (result[index] == NULL) {
                for (int j = 0; j < index; j++) {
                    free(result[j]);
                }
                free(result);
                *out_count = 0;
                return NULL;
            }
            index++;
        }
    }

    return result;
}

int main(void) {
    char* input_strings[] = {
        "apple",
        "cat",
        "banana",
        "dog",
        "elephant",
        "bat"
    };
    int list_size = sizeof(input_strings) / sizeof(input_strings[0]);
    size_t target_length = 3;
    int extracted_count = 0;

    char** extracted = extract_strings(input_strings, list_size, target_length, &extracted_count);

    if (extracted != NULL) {
        for (int i = 0; i < extracted_count; i++) {
            printf("%s\n", extracted[i]);
            free(extracted[i]);
        }
        free(extracted);
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** extract_strings(char** list, int num_strings, size_t target_size, int* out_count) {
    if (list == NULL || num_strings <= 0 || out_count == NULL) {
        return NULL;
    }

    char** result = NULL;
    int count = 0;

    for (int i = 0; i < num_strings; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (list[i] != NULL && strlen(list[i]) == target_size) {
            count++;
        }
    }

    if (count == 0) {
        *out_count = 0;
        return NULL;
    }

    result = (char**)malloc(count * sizeof(char*));
    if (result == NULL) {
        *out_count = 0;
        return NULL;
    }

    int idx = 0;
    for (int i = 0; i < num_strings; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (list[i] != NULL && strlen(list[i]) == target_size) {
            result[idx] = (char*)malloc((target_size + 1) * sizeof(char));
            if (result[idx] == NULL) {
                for (int j = 0; j < idx; j++) {
                    free(result[j]);
                }
                free(result);
                *out_count = 0;
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(result[idx], list[i], target_size + 1);
            idx++;
        }
    }

    *out_count = count;
    return result;
}

int main(void) {
    char* strings[] = {
        "apple",
        "cat",
        "banana",
        "dog",
        "elephant",
        "bat"
    };
    int num_strings = sizeof(strings) / sizeof(strings[0]);
    size_t target_size = 3;
    int out_count = 0;

    char** extracted = extract_strings(strings, num_strings, target_size, &out_count);

    if (extracted != NULL) {
        for (int i = 0; i < out_count; i++) {
            printf("%s\n", extracted[i]);
            free(extracted[i]);
        }
        free(extracted);
    }

    return 0;
}